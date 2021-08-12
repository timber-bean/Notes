# 容器

# vector

```C++
#include <vector>
vector<int> test;

test.push_back(XX);
test.emplace_back(XX);
```

### push_back()与emplace_back()

都是在容器尾部添加一个元素。

emplace_back()直接在容器尾部创建这个元素，不需要调用拷贝构造函数和转移构造函数。**效率更高**

push_back()需要调用拷贝构造函数和转移构造函数。它先创建一个新元素，再把该元素移动（优选）或者拷贝到容器中。

