#ifndef LOGIN_QUEUE_H
#define LOGIN_QUEUE_H

#include <mutex>
#include <queue>

#include "login.h"

class LoginQueue {
   private:
    std::mutex mutex;
    std::queue<Login> queue;

   public:
    LoginQueue();
    ~LoginQueue();

    void push(Login& login);
    Login pop();
};

#endif
