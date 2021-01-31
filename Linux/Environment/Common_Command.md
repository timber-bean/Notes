# 基本命令
```shell
#新建文件夹、文件
mkdir /usr/asdf
touch /usr/test.txt

#查看文件内容
cat /etc/apt/sources.list

#编辑文件
vim /etc/apt/sources.list
gedit /etc/apt/sources.list

#移动文件、文件重命名
mv /etc/apt/sources.list /etc/sources.list
mv /etc/apt/ /etc/bpt/

#删除文件、文件夹
rm /etc/apt/sources.list
rm -rf /etc/apt/
```
# 远程命令
## screen
主要是为了关闭ssh后，服务器的程序依然运行。
```shell
sudo apt-get install screen
screen -S sessionName #sessionName是要删除的session名字
正常执行程序
ctrl+a提起，按d键退出返回主界面
进行其他操作即可
```
screen的其他命令。
```shell
#列出现有子界面的session_name
screen -ls
#进入子界面
screen -r 子界面的session_name
#删除指定子界面
screen -S session_name -X quit
```
# 其他常用命令
## 压缩、解压
```shell
```
