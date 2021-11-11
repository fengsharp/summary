1. install gcc g++
2. sudo yum install -y glibc-headers libXrandr-devel
3. download bochs-2.6.11.tar.gz
4. 解压后配置
```sh
./configure --with-x11 --with-wx --enable-debugger --enable-disasm --enable-all-optimizations --enable-readline --enable-long-phy-address --enable-ltdl-install --enable-idle-hack --enable-plugins --enable-a20-pin --enable-x86-64 --enable-smp --enable-cpu-level=6 --enable-large-ramfile --enable-repeat-speedups --enable-fast-function-calls --enable-handlers-chaining --enable-trace-linking --enable-configurable-msrs --enable-show-ips --enable-cpp --enable-debugger-gui --enable-iodebug --enable-logging --enable-assert-checks --enable-fpu --enable-vmx=2 --enable-svm --enable-3dnow --enable-alignment-check --enable-monitor-mwait --enable-avx --enable-evex --enable-x86-debugger --enable-pci --enable-usb --enable-voodoo
```

5. 此时make会报错
bx_debug/dbg_main.ccp 中
```c++
--- bochs/bx_debug/dbg_main.cc	(revision 13777)
+++ bochs/bx_debug/dbg_main.cc	(working copy)
@@ -1494,11 +1494,11 @@
 {
   char cpu_param_name[16];
 
-  Bit32u index = BX_ITLB_INDEX_OF(laddr);		//这一行改成下面一行
+  Bit32u index = BX_CPU(dbg_cpu)->ITLB.get_index_of(laddr);
   sprintf(cpu_param_name, "ITLB.entry%d", index);
   bx_dbg_show_param_command(cpu_param_name, 0);
 
-  index = BX_DTLB_INDEX_OF(laddr, 0);		//同理
+  index = BX_CPU(dbg_cpu)->DTLB.get_index_of(laddr);
   sprintf(cpu_param_name, "DTLB.entry%d", index);
   bx_dbg_show_param_command(cpu_param_name, 0);
 }
```

6. 再次make还是报错
make: *** No rule to make target ‘misc/bximage.cc’
```sh
  cp misc/bximage.cpp misc/bximage.cc
  cp iodev/hdimage/hdimage.cpp iodev/hdimage/hdimage.cc
  cp iodev/hdimage/vmware3.cpp iodev/hdimage/vmware3.cc
  cp iodev/hdimage/vmware4.cpp iodev/hdimage/vmware4.cc
  cp iodev/hdimage/vpc-img.cpp iodev/hdimage/vpc-img.cc
  cp iodev/hdimage/vbox.cpp iodev/hdimage/vbox.cc
```

7. 重新make并make install


https://blog.csdn.net/weixin_42417376/article/details/107570475


8. sudo yum install nasm
9. nasm boot.asm -o boot.bin
```sh
bximage
1
fd

dd if=boot.bin of=a.img bs=512 count=1 conv=notrunc
```


10. 加入配置
```properties
# filename of ROM images
romimage: file=$BXSHARE/BIOS-bochs-latest, options=fastboot
vgaromimage: file=$BXSHARE/VGABIOS-lgpl-latest

# what disk images will be used
floppya: image=./a.img, status=inserted

# choose the boot disk.
boot: floppy
floppy_bootsig_check: disabled=0

# where do we send log messages?
log: bochsout.txt

# disable the mouse
mouse: enabled=0

#keyboard: type=mf, serial_delay=250
keyboard: keymap=$BXSHARE/keymaps/x11-pc-de.map

speaker: enabled=1, mode=sound
# how much memory the emulated machine will have
megs: 32
```

11. 执行命令  
bochs -f bochsrc  
或者 bochs  
选择6进行模拟  
输入c 继续运行  














