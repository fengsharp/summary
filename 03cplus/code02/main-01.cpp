#include <iostream>
#include <thread>
#include <chrono>

class ThreadGuard
{
public:
    ThreadGuard(std::thread &t_)
        : t(t_)
    {
    }

    ~ThreadGuard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    ThreadGuard(const ThreadGuard &rhs) = delete;
    ThreadGuard &operator=(const ThreadGuard &rhs) = delete;

private:
    std::thread &t;
};

void task()
{
    using namespace std::chrono_literals;
    // while (1)
    {
        std::this_thread::sleep_for(5s);
        std::cout << "task ..." << std::endl;
    }
}

int main()
{
    using namespace std::chrono_literals;

    std::thread t(task);
    ThreadGuard guard(t);
    // t.join();
    // t.detach();

    std::this_thread::sleep_for(3s);
    std::cout << "main end." << std::endl;

    return 0;
}