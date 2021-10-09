#ifndef NON_COPYABLE_H_
#define NON_COPYABLE_H_

class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    void operator=(const noncopyable &) = delete;

    noncopyable(const noncopyable &&) = delete;
    void operator=(const noncopyable &&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif