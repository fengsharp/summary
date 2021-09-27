#ifndef DYN_BASE_H_
#define DYN_BASE_H_

#include <map>
#include <string>
#include <functional>

class DynObjectFactory
{
public:
    static void* createObject(const std::string& name)
    {
        std::map<std::string, std::function<void*()>>::const_iterator item = mapCreateFunctions.find(name);
        if (item == mapCreateFunctions.end())
        {
            return nullptr;
        }
        else
        {
            return item->second();
        }
    }

    static void registerFunc(const std::string &name, std::function<void*()> func)
    {
        mapCreateFunctions[name] = func;
    }
private:
    static std::map<std::string, std::function<void*()>> mapCreateFunctions;
};

std::map<std::string, std::function<void*()>> DynObjectFactory::mapCreateFunctions;

class Register
{
public:
    Register(const std::string &name, std::function<void*()> func)
    {
        DynObjectFactory::registerFunc(name, func);
    }
};

#define REGISTER_CLASS(class_name) \
class class_name##Register { \
public: \
    static void* newInstance() \
    { \
        return new class_name; \
    } \
private: \
    static Register reg_; \
}; \
Register class_name##Register::reg_(#class_name, class_name##Register::newInstance);


#endif