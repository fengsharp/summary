## 1. plan
1. man 
2. action
3. read code

## 2. list
1. base
2. type+oprator+expression
3. io
4. control
5. array and pointer
6. function
7. malloc
8. gdb
9. lib

## 3. 注意事项
1. 越界
2. 内存泄露
3. 资源管理（谁打开，谁关闭；谁申请，谁释放）

## 4. linux kernel source 
2.6.32

/usr/src/kernels/2.6.32.../include/linux/


## 5. 基本数据类型
1. 数值
    - 整型
        short 2
        int   4
        long long 8
    - 浮点
        float 4
        double 8
2. 字符
    char 1

## 6. input/output
scanf printf getchar putchar puts

%[修饰符]格式字符

m    m宽
.n   n个小数  如果是字符串，限制多少个字符个数
- 左对齐 
+ 有符号的前面显示+

## 8. struct
1. link
2. tree

## 9. project
1. client 端
    - fork + child(exec -> mpg123)
    - 多进程的实现及关系
    - 进程间通信
2. server 端  
    - send list(多线程)
    - send data(多线程)
    - lib(file system)
    - schedule-main
    - 流量控制
    - socket
    - 守护进程（脱离中断）
    - 系统日志
## 10. list
### 1. io
#### 标准IO
- fopen
- fclose
- fread
- fwrite
- fgets
- fputs
- fgetc
- fputc
- printf | scanf
- fseek ftell rewind

```c
#include <error.h>
errno

#include <stdio.h>
perror("...");

#include <string.h>
char *strerror(int errno);

max file-number 1021 + 0 1 2 = 1024   
ulimit -a


0666 & ~mask(0002)  文件权限


```

#### 系统IO
### 2. file system
### 3. 并发
### 4. IPC











