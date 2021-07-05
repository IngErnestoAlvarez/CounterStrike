#ifndef __QUEUE_MONITOR_H__
#define __QUEUE_MONITOR_H__

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

/**
 * @brief Cola bloqueante
 *
 * @tparam T El tipo tiene que tener constructor y asignacion por copia
 * implementado al igual que por movimiento.
 */
template <typename T>
class QueueMonitor {
   private:
    std::queue<T> *q;
    std::mutex m;
    std::condition_variable cv;
    std::atomic_bool done;

   public:
    explicit QueueMonitor(std::queue<T> *q);

    QueueMonitor() = delete;

    QueueMonitor(QueueMonitor const &other);

    // Chequea si la cola está vacia, y quita el primer elemento
    // y lo almacena en result, le brinda el ownership a result.
    // Es atomica.
    // Devuelve false si la queue esta muerta (kill()).
    bool pop(T &result);

    // Encola el elemento, avisando que se ha encolado un elemento.
    // No se pierde el ownership, se utiliza constructor por copia
    void push(T &element);

    // La queue deja de trabajar y pop devuelve false todo el tiempo.
    void kill();
};

#endif
