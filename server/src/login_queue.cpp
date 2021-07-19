#include "login_queue.h"

#include "protocolo.h"

LoginQueue::LoginQueue() {}

LoginQueue::~LoginQueue() {}

void LoginQueue::push(Login& login) {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->queue.push(std::move(login));
}

Login LoginQueue::pop() {
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->queue.empty()) return Login();
    Login login(std::move(this->queue.front()));
    this->queue.pop();
    return login;
}
