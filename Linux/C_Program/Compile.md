# 编译时出现的问题
## gcc编译
```shell
#-o用于规定可执行文件的名字
gcc -o demo demo.c
```
### gcc编译时的搜寻路径
**头文件**  
* 所有header file的搜寻会从-I开始  
* 找gcc的环境变量：C_INCLUDE_PATH，CPLUS_INCLUDE_PATH，OBJC_INCLUDE_PATH  
* 找内定目录  

/usr/include  
/usr/local/include  
/usr/lib/gcc-lib/i386-linux/2.95.2/include  
/usr/lib/gcc-lib/i386-linux/2.95.2/../../../../include/g -3  
/usr/lib/gcc-lib/i386-linux/2.95.2/../../../../i386-linux/include  

库文件但是假如装gcc的时候，是有给定的prefix的话，那么就是  

/usr/include  
prefix/include  
prefix/xxx-xxx-xxx-gnulibc/include  
prefix/lib/gcc-lib/xxxx-xxx-xxx-gnulibc/2.8.1/include  

**库文件**  
* gcc会去找-L  
* 找gcc的环境变量LIBRARY_PATH  
* 找内定目录 /lib /usr/lib /usr/local/lib 这是当初compile gcc时写在程序内的  
注意：  
编译时查找的路径可以通过gcc -L参数或者LIBRARY_PATH来指定，但是这对运行时的查找路径是不起作用的！-L只是指定了程序编译连接时库的路径，并不影响程序执行时搜索库的路径。  

### 运行时库文件的搜寻路径
* 在配置文件/etc/ld.so.conf中指定动态库搜索路径  
* 通过环境变量LD_LIBRARY_PATH指定动态库搜索路径(当通过该环境变量指定多个动态库搜索路径时，路径之间用冒号"："分隔)  
* 在编译目标代码时指定该程序的动态库搜索路径(还可以在编译目标代码时指定程序的动态库搜索路径。  
这是通过gcc 的参数"-Wl,-rpath,"指定(如例3所示)。当指定多个动态库搜索路径时，路径之间用冒号"："分隔)  
* 默认的动态库搜索路径/lib  
* 默认的动态库搜索路径/usr/lib  
