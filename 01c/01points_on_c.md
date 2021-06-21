1. 打开文件
2. 处理数据
    1. 记录第一行内容, 区分出列范围
    2. 逐行读取，每行内容先保存，然后按照列范围，输出结果
3. 关闭文件

FILE *fopen(const char *path, const char *mode);
int fclose(FILE *fp);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    1. return the number of items read or written
    2. the return value is a short item count (or zero)
int fscanf(FILE *stream, const char *format, ...);

#include <errno.h>
void perror(const char *s);





