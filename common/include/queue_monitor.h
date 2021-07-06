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

    ~QueueMonitor();

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

typedef std::unique_lock<std::mutex> guard;

template <typename T>
QueueMonitor<T>::QueueMonitor(std::queue<T> *q) : m(), cv(), done(false) {
    this->q = q;
}

template <typename T>
QueueMonitor<T>::QueueMonitor(QueueMonitor const &other) : m() {
    this->q = other.q;
}

template <typename T>
bool QueueMonitor<T>::pop(T &result) {
    if (this->done.load()) return false;
    guard lock(this->m);
    while (this->q->empty()) {
        this->cv.wait(lock);
        if (this->done.load()) return false;
    }
    result = std::move(this->q->front());
    this->q->pop();
    return true;
}

template <typename T>
void QueueMonitor<T>::push(T &element) {
    guard lock(this->m);
    this->q->push(element);
    lock.unlock();
    this->cv.notify_all();
}

template <typename T>
void QueueMonitor<T>::kill() {
    this->done = true;
    this->cv.notify_all();
}

template <typename T>
inline QueueMonitor<T>::~QueueMonitor() {
    while (!this->q->empty()) {
        q->pop();
    }
}

#endif
