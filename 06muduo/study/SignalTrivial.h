#ifndef SIGNALSLOTTRIVIAL_H_
#define SIGNALSLOTTRIVIAL_H_

#include <memory>
#include <vector>

template <typename Signature>
class SignalTrivial;

template <typename RET, typename... ARGS>
class SignalTrivial<RET(ARGS...)>
{
public:
    typedef std::function<void(ARGS...)> Functor;

    void connect(Functor &&func)
    {
        functors_.push_back(std::forward<Functor>(func));
    }

    void call(ARGS &&...args)
    {
        for (const Functor& f: functors_)
        {
            f(args...);
        }
    }

private:
    std::vector<Functor> functors_;
};

#endif