#include <iostream>
#include <thread>

class ThreadGurd
{
public:
    explicit ThreadGurd(std::thread &t)
        : thread(t)
    {
    }

    ThreadGurd(ThreadGurd &rhs) = delete;
    ThreadGurd& operator=(ThreadGurd &rhs) = delete;

    ~ThreadGurd()
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
private:
    std::thread &thread;
};


void task()
{
    std::cout << "task " << std::endl;
}

int main()
{
    std::thread t(task);
    // ThreadGurd gurd(t);
    t.join();

    std::cout << " === over. === " << std::endl;
    return 0;
}