#ifndef __MY_THREAD_H__
#define __MY_THREAD_H__

#include <thread>

class Thread {
   private:
    std::thread thread;

   public:
    Thread();

    Thread(const Thread &) = delete;

    Thread(Thread &&other);

    void start();

    void join();

    virtual void run() = 0;

    virtual ~Thread();

    Thread &operator=(const Thread &) = delete;

    Thread &operator=(Thread &&other);
};

#endif
