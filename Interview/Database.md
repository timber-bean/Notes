[TOC]

# 数据库的事务及四个特性

* 事务：由一系列对系统中数据进行访问与更新的操作所组成的一个**程序执行逻辑单元**。事务是DBMS中最基础的单位，事务不可分割。
* 四大特性（ACID）
  * 原子性：事务所包含的所有操作要么全部成功，要么全部回滚
  * 一致性：事务必须使数据库从一个一致性状态变换到另一个一致性状态。例如A与B之间转账，要保证总金额不变
  * 隔离性：多用户并发访问数据库时，一个事务不能被其他事务的操作所干扰
  * 持久性：一旦一个事务被提交，那么对数据库中的数据的改变就是永久性的

# 数据库三大范式

* 第一范式：当关系模式R的所有属性都不能再分解为更基本的数据单位时，称R满足第一范式，即**属性不可分**
* 第二范式：如果关系模式R满足第一范式，且R的所有非主属性都完全依赖于R的每一个候选关键属性，称R满足第二范式，即**非主属性完全传递依赖于键**
* 第三范式：若R时满足第一范式的关系模式，X是R的任意属性集，若X非传递依赖于R的任意一个候选关键字，称R满足第三范式，即**非主属性不传递依赖于键**

# 数据库索引

* 索引是对数据库表中一列或多列的值进行排序的一种结构，使用索引可快速访问数据库表中的特定信息。
* 目的是，**加快检索**表中数据的方法，即能协助信息搜索者尽快找到符合限制条件的记录ID的辅助数据结构
* 对数据频繁查询，适合建立索引；若频繁更改数据，则不适合用索引

# 为什么MySQL数据库索引使用B+树？

MySQL中的MylsAM和InnoDB引擎，都是采用B+树结构。前者是非聚集索引（B+数的数据域存储的是数据地址），后者主键是聚集索引（B+数的数据域存储的就是真实数据）。

* **B+树的磁盘读写代价更低**。内部节点**只有关键字（key）**，使得每次从文件中读取的索引更多，减少IO读写次数。
* **B+树的查询效率更稳定**。因为只有叶子节点存储记录信息，因此所有关键字查询的路径长度一样，必须查询到叶子节点。
* **B+树的数据都存储在叶子节点中，方便扫库**。因为只有叶子节点存储记录信息，因此更适合区间查询。

# 关系型数据库和非关系型数据库的区别

* 非关系型的优势
  * 非关系型无需SQL层解析，**读写性能好**
  * 非关系型数据库由于基于键值对，数据之间没有耦合，**易水平扩展**
* 关系型数据库的优势
  * 关系型数据库**容易理解**，是二维表结构
  * 关系型数据库适合**复杂查询**，可在一表或多表间做复杂查询
  * 关系型数据库支持**事务**，对安全性能很高的数据访问适合用关系型
  * 关系型数据库**易维护**，丰富的完整性降低了数据冗余和数据不一致的概率
* 关系型数据库的劣势
  * 关系型数据库**性能差**
  * 关系型数据库**可扩展性差**

# MySQL的连接

* INNER JOIN（内连接）：获取两个表中字段匹配关系的记录
* LEFT JOIN（左连接）：获取左表所有记录和右表中连接字段相等的记录，右表对应属性值如果不存在，以NULL值显示在结果中
* RIGHT JOIN（右连接）：获取右表所有记录和左表中连接字段相等的记录，左表对应属性值如果不存在，以NULL值显示在结果中

```mysql
SELECT a.id, a.author, b.count FROM runoob_tbl a INNER JOIN tcount_tbl b ON a.author = b.author;
#等价于
SELECT a.id, a.author, b.count FROM runoob_tbl a, tcount_tbl b WHERE a.author = b.author;

#左连接
SELECT a.id, a.author, b.count FROM runoob_tbl a LEFT JOIN tcount_tbl b ON a.author = b.author;

#右连接
SELECT a.id, a.author, b.count FROM runoob_tbl a RIGHT JOIN tcount_tbl b ON a.author = b.author;
```

# MySQL排序

* ORDER BY：用于排序，需要放到**语句末尾**。
* ASC表示升序排列，DESC表示降序排列，默认是ASC。

```mysql
SELECT name from student WHERE subject="语文" ORDER BY score DESC;
```

# MySQL选前X个数据

* 使用limit加以限制，需放在order by之后
* 请选择语文成绩前20名的学生姓名

```mysql
SELECT name from student WHERE subject="语文" ORDER BY score DESC limit 0,20;
```

# MySQL分组

* 使用GROUP BY

```mysql
#按名字分组，并统计有每个人有多少条记录
SELECT name, COUNT(*) FROM student GROUP BY name;
```

* 使用WITH ROLLUP可以实现在分组统计数据基础上再进行相同的统计

```mysql
#按名字分组，再统计每个人的登录次数
SELECT name, SUM(signin) as signin_count FROM student GROUP BY name WITH ROLLUP;
```

# MySQL ALTER

* 用于修改**数据表名**或者**数据表字段**

```mysql
#修改表名
ALTER TABLE testalter_tbl RENAME TO alter_tbl;
#删除字段
ALTER TABLE testalter_tbl DROP i;
#添加字段，并定义数据类型
ALTER TABLE testalter_tbl ADD i INT;
```

