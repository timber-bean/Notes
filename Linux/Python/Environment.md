# python的一些环境问题
主要是pip的问题及其他相关问题。
## pip的相关问题
### 更换国内镜像
一些国内的镜像源
>阿里云 http://mirrors.aliyun.com/pypi/simple/  
中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/  
豆瓣(douban) http://pypi.douban.com/simple/  
清华大学 https://pypi.tuna.tsinghua.edu.cn/simple/  
中国科学技术大学 http://pypi.mirrors.ustc.edu.cn/simple/  

#### 临时更改
可以在使用pip的时候在后面加上-i参数，指定pip源，例如：  
```shell
pip install scrapy -i https://pypi.tuna.tsinghua.edu.cn/simple
```
#### 永久更改
**linux**   
修改 ~/.pip/pip.conf (没有就创建一个)， 内容如下：  
```shell
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
```
**windows**   
直接在user目录中创建一个pip目录，如：C:\Users\xx\pip，在pip 目录下新建文件pip.ini，内容如下：  
```shell
[global]
timeout = 6000
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
trusted-host = pypi.tuna.tsinghua.edu.cn
```
### 更新pip
```shell
python -m pip install --upgrade pip
pip show pip #查看pip版本
```
### pip安装三方库
```shell
pip install [包名称，例如numpy]
```
### pip更新三方库
```shell
pip list #查看已安装的三方库
pip list --outdated #查看已安装的三方库有哪些可以更新
pip install --upgrade [包名称，例如numpy] #更新对应包
```
### pip卸载三方库
```shell
pip uninstall [包名称，例如numpy]
```
