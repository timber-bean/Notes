# 查看硬盘
```shell
df
```
# 查看cpu信息
```shell
cat /proc/cpuinfo
```
# 查看显卡信息
```shell
lspci | grep VGA
```

# 查看内存

```shell
free -m
```

# 查看进程、线程

```shell
ps aux #显示所有运行中的进程
ps -u test #查看用户test运行的进程

ps -eLf #显示线程信息
ps axms #显示线程信息

pstree #显示进程的树状图
ps axjf #显示进程树状图

pgrep firefox #显示firefox的进程ID
pgrep -u root sshd #显示进程名为sshd、所有者为root的进程
```

```shell
top #查看进程的动态信息
```

