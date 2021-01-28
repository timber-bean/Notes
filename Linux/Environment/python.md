# python的一些环境问题
## pip更换国内镜像
一些国内的镜像源
>阿里云 http://mirrors.aliyun.com/pypi/simple/  
中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/  
豆瓣(douban) http://pypi.douban.com/simple/  
清华大学 https://pypi.tuna.tsinghua.edu.cn/simple/  
中国科学技术大学 http://pypi.mirrors.ustc.edu.cn/simple/  

### 修改源方法
#### 临时使用
可以在使用pip的时候在后面加上-i参数，指定pip源，例如：  
```shell
pip install scrapy -i https://pypi.tuna.tsinghua.edu.cn/simple
```
#### 永久修改
linux:   
修改 ~/.pip/pip.conf (没有就创建一个)， 内容如下：  
```shell
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
```

windows:   
直接在user目录中创建一个pip目录，如：C:\Users\xx\pip，在pip 目录下新建文件pip.ini，内容如下：  
```shell
[global]
timeout = 6000
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
trusted-host = pypi.tuna.tsinghua.edu.cn
```
