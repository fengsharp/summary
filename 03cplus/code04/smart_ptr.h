#ifndef SMART_PTR_H_
#define SMART_PTR_H_

#include <utility>

class shared_count
{
public:
    shared_count() noexcept
        : count(1)
    {
    }

    void add_count() noexcept
    {
        ++count;
    }
    long reduce_count() noexcept
    {
        --count;
    }
    long get_count() noexcept
    {
        return count;
    }

private:
    long count;
};

template <typename T>
class smart_ptr
{
public:
    template <typename U>
    friend class smart_ptr;

    explicit smart_ptr(T *p = nullptr)
        : ptr(p)
    {
        if (ptr)
        {
            count = new shared_count();
        }
    }

    ~smart_ptr()
    {
        if (ptr && count->get_count() == 0)
        {
            delete ptr;
            delete count;
        }
    }

    template <typename U>
    smart_ptr(const smart_ptr<U> &other) noexcept
    {
        ptr = other.ptr;
        if (ptr)
        {
            other.count->add_count();
            count = other.count;
        }
    }

    template <typename U>
    smart_ptr(const smart_ptr<U> &&other) noexcept
    {
        ptr = other.ptr;
        if (ptr)
        {
            other.count->add_count();
            count = other.count;
            other.ptr = nullptr;
        }
    }

    template <typename U>
    smart_ptr(const smart_ptr<U> &other, T *p) noexcept
    {
        ptr = p;
        if (ptr)
        {
            other.count->add_count();
            count = other.count;
        }
    }

    smart_ptr &operator=(smart_ptr rhs) noexcept
    {
        rhs.swap(*this);
        return *this;
    }

    T *get() const noexcept
    {
        return ptr;
    }

    long user_count() const noexcept
    {
        if (ptr)
        {
            return count->get_count();
        }
        else
        {
            return 0;
        }
    }

    void swap(smart_ptr &rhs) noexcept
    {
        std::swap(ptr, rhs.ptr);
        std::swap(count, rhs.count);
    }

    T& operator*() const noexcept
    {
        return *ptr;
    }

    T* operator->() const noexcept
    {
        return ptr;
    }

    operator bool() const noexcept
    {
        return ptr;
    }

private:
    T *ptr;
    shared_count *count;
};

#endif