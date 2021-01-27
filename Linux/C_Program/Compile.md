# 编译时的注意事项
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

    * /usr/include  
    * /usr/local/include  
    * /usr/lib/gcc-lib/i386-linux/2.95.2/include  
    * /usr/lib/gcc-lib/i386-linux/2.95.2/../../../../include/g -3  
    * /usr/lib/gcc-lib/i386-linux/2.95.2/../../../../i386-linux/include  

* 假如装gcc的时候，是有给定的prefix的话，那么内定目录就是  

    * /usr/include  
    * prefix/include  
    * prefix/xxx-xxx-xxx-gnulibc/include  
    * prefix/lib/gcc-lib/xxxx-xxx-xxx-gnulibc/2.8.1/include  

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

### gcc编译、运行时找不到文件怎么办
自己写的头文件、库有时候需要给其他的代码用，就需要其他代码能找得到它，接下来阐述能让其他程序找到它的方法。  
#### 编译找不到头文件
* 如果权限足够大  
    * 可以把自己的头文件放到/usr/include/或者/usr/local/include/下。  
    * 可以修改/etc/profile文件，添加如下内容：
    ```shell
    #gcc找到头文件的路径
    C_INCLUDE_PATH=$C_INCLUDE_PATH:/MyInclude
    export C_INCLUDE_PATH

    #g++找到头文件的路径
    CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/MyInclude
    export CPLUS_INCLUDE_PATH
    ```
* 如果权限仅限于当前用户  
    * 修改~/.bashrc文件，添加和/etc/profile文件一样的内容。  
#### 编译找不到静态库、动态库
* 如果权限足够大  
    * 可以把自己的库文件放到/usr/lib/或者/usr/local/lib/下。  
    * 可以修改/etc/profile文件，添加如下内容：
    ```shell
    #找到库的路径
    LIBRARY_PATH=$LIBRARY_PATH:/MyLib
    export LIBRARY_PATH
    ```
* 如果权限仅限于当前用户  
    * 修改~/.bashrc文件，添加和/etc/profile文件一样的内容。  
#### 运行时找不到静态库、动态库
* 如果权限足够大  
    * 可以修改/etc/profile文件，添加如下内容：
    ```shell
    #找到库的路径
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/MyLib
    export LD_LIBRARY_PATH
    ```
* 如果权限仅限于当前用户  
    * 修改~/.bashrc文件，添加和/etc/profile文件一样的内容。
## makefile
### makefile是什么
> 一个工程中的源文件不计其数，其按类型、功能、模块分别放在若干个目录中，makefile定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为makefile就像一个Shell脚本一样，也可以执行操作系统的命令。——百度百科  
makefile文件描述了整个工程的编译、连接等规则。其中包括：工程中的哪些源文件需要编译以及如何编译、需要创建哪些库文件以及如何创建这些库文件、如何最后产生我们想要的可执行文件。尽管看起来可能是很复杂的事情，但是为工程编写makefile的好处是能够使用一行命令来完成“自动化编译”，一旦提供一个（通常对于一个工程来说会是多个）正确的 Makefile。编译整个工程你所要做的事就是在shell提示符下输入make命令。整个工程完全自动编译，极大提高了效率。——百度百科  

总之，makefile是一个为了使工程编译、链接等工作自动化完成的规则文件。
### makefile的编写规则
