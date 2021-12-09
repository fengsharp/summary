## 1. version
```c
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 15

const char* get_version()
{
    static char version[15];
    sprintf(version, "%d.%d.%d", CJSON_VERSION_MAJOR, CJSON_VERSION_MINOR, CJSON_VERSION_PATCH);
    return version;
}
```
1. XXXX.XXXX.XXXX 4*3 + 2 + '\0' -> 15
2. sprintf 确定在14个字符范围内，所以不考虑其返回值
