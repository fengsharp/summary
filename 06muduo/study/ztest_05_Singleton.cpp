#include "Singleton.h"
#include "Thread.h"
#include "noncopyable.h"

#include <stdio.h>
#include <unistd.h>

class Test : private noncopyable
{
public:
    Test()
    {
        printf("tid=%d, constructing %p\n", CurrentThread::tid(), this);
    }

    ~Test()
    {
        printf("tid=%d, destructing %p %s\n", CurrentThread::tid(), this, name_.c_str());
    }

    const std::string &name() const { return name_; }
    void setName(const std::string &n) { name_ = n; }

private:
    std::string name_;
};

void threadFunc()
{
    printf("tid=%d, %p name=%s\n", CurrentThread::tid(), &Singleton<Test>::instance(), Singleton<Test>::instance().name().c_str());
    Singleton<Test>::instance().setName("only one, changed");
}

template <unsigned N>
class Destruct
{
public:
    Destruct()
    {
        printf("construct %d\n", N);
        more();
    }

    ~Destruct()
    {
        printf("destruct %d\n", N);
    }

    void more()
    {
        Singleton<Destruct<N - 1>>::instance();
    }
};

template <>
void Destruct<0>::more()
{
}

int main()
{
    Singleton<Test>::instance().setName("only one");
    Thread t1(threadFunc);
    t1.start();
    t1.join();
    printf("tid=%d, %p name=%s\n", CurrentThread::tid(), &Singleton<Test>::instance(), Singleton<Test>::instance().name().c_str());

    Singleton<Destruct<100>>::instance();
    printf("ATEXIT_MAX = %ld\n", sysconf(_SC_ATEXIT_MAX));

    return 0;
}
