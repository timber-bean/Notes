#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility> //pair的头文件

using namespace std;

/*--------------输入的是字符串---------------*/
/*---------------------
形式为：123, 23, 41, 11
要求：把数字取出来
---------------------*/
vector<int> inputStringToArray(){
    vector<int> arr;
    string s;
    while(cin >> s){ //赛码网可以这么操作
        int num = stoi(s); //不要用atoi，atoi是处理char数组的
        arr.push_back(num);
    }
    return arr;
}

int main(){
    vector<int> a = inputStringToArray();
    int i = 0;
    while(i<a.size()) cout<<a[i++];
    return 0;
}