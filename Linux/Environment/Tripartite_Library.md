# PBC库的安装
## GMP库及其依赖
### GMP库的依赖
```shell
sudo apt-get install m4
sudo apt-get install flex
sudo apt-get install bison
```
### GMP库
1. 前往 https://gmplib.org/ 下载源码  
2. 将压缩包移至 /usr/ 文件夹  
```shell
sudo mv gmp-xxx.tar.lz /usr/
```
3. 进入 /usr/ 文件夹解压  
```shell
sudo apt-get install lzip
lzip -d gmp-xxx.tar.lz
tar -xvf gmp-xxx.tar
sudo chmod 777 -R ./gmp-xxx/
```
4. 进入 /usr/gmp-xxx/ 文件夹进行编译安装
```shell
./configure
make
make check
sudo make install
```
## PBC库
1. 前往 https://crypto.stanford.edu/pbc/download.html 下载源码  
2. 将压缩包移至 /usr/ 文件夹  
```shell
sudo mv pbc-xxx.tar.gz /usr/
```
3. 进入 /usr/ 文件夹解压  
```shell
tar -zxvf pbc-xxx.tar.gz
sudo chmod 777 -R ./pbc-xxx/
```
4. 进入 /usr/pbc-xxx/ 文件夹进行编译安装
```shell
./configure
make
sudo make install
```
