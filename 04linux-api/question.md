# 1. stand io
1. 系统最大打开文件数 ulimit -a  
    vscode远程连接执行代码时，vscode自己会占用一个
2. 文件的权限是如何定义的  
    - 文件最大权限 & ~umask  
      默认 0666 & ~(0002) 第一个数字是特殊权限（SetUID、SetGID、Sticky BIT）剩下的是 ower group other
      4-r 2-w 1-x
      (rw rw rw) & ~(0 0 w)
      (rw rw rw) & (rwx, rwx, rx) -> (rw, rw, r)

      所以默认创建的文件权限是
      -rw-rw-r--
    - 目录最大权限 & ~umask  drwxrwxr-x
      0777 & ~(0002)
      (rwx rwx rwx) & ~(0 0 w)
      (rwx rwx rwx) & ~(rwx, rwx, rx) -> (rwx, rwx, rx)
      所以默认的创建的目录权限是
      drwxrwxr-x

# 2. system io