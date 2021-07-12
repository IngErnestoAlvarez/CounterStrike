#ifndef __PROXY_SENDER_H__
#define __PROXY_SENDER_H__

#include <atomic>

#include "game_io/modelo_io.h"
#include "my_thread.h"

class ProxySender : public Thread {
   private:
    ModeloIO *modelo;
    std::atomic_bool *playing;

   public:
    ProxySender(ModeloIO *modelo, std::atomic_bool *playing);

    ~ProxySender();

    void run() override;
};

#endif  // __PROXY_SENDER_H__
