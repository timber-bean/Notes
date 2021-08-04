/* 目录 */
/*=========================================
题目1：合并排序数组
题目2：腐烂的橘子
题目3：和为S的连续正数序列
题目4：队列的最大值
题目5：买卖股票的最佳时机
题目6：将数组分成和相等的三个部分
题目7：字符串的最大公因子
题目8：字符串压缩
题目9：矩形重叠
题目10：链表的中间结点
题目11：三维形体的表面积
题目12：卡牌分组
题目13：旋转矩阵
题目14：两数之和（hash表）
题目15：二叉树的层序遍历（队列）
题目16：只出现一次的数字（位运算——异或）
题目17：和为K的子数组（前缀和+hash表/映射表）
题目18：反转链表II
题目19：逆波兰表达式求值
题目20：黑板异或游戏（数学推理）
=========================================*/


/*-------------------------------
| 题目1：合并排序数组
| 给定两个排序后的数组 A 和 B，其中 A 的末端有足够的缓冲空间容纳 B。 
| 编写一个方法，将 B 合并入 A 并排序。
| 初始化 A 和 B 的元素数量分别为 m 和 n。
-------------------------------*/
/* 题解——比较A与B中的元素，将最大的元素插入A的最后，以此类推 */
class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        //pa为A中最大元素的位置，pb为B中最大元素的位置
        int pa = m - 1, pb = n - 1;
        int tail = m + n - 1;//A与B合并后的最大元素应当在的位置
        int cur;//临时存放最大值
        while (pa >= 0 || pb >= 0) {
            if (pa == -1)
                cur = B[pb--];
            else if (pb == -1)
                cur = A[pa--];
            else if (A[pa] > B[pb])
                cur = A[pa--];
            else
                cur = B[pb--];
            A[tail--] = cur;
        }
    }
};


/*-------------------------------
| 题目2：腐烂的橘子
| 在给定的网格中，每个单元格可以有以下三个值之一：
| 值 0 代表空单元格；
| 值 1 代表新鲜橘子；
| 值 2 代表腐烂的橘子。
| 每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。
| 返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。
-------------------------------*/
/* 题解——使用辅助数组定位即将被腐烂的橘子的坐标 */
class Solution {
public:
   int orangesRotting(vector<vector<int>>& grid) {
        int row=grid.size();
        int col=grid[0].size();
        int res=0;
        vector<int> dx={-1,0,0,1};//辅助定位即将被腐烂的橘子的横坐标
        vector<int> dy={0,1,-1,0};//辅助定位即将被腐烂的橘子的纵坐标，对应构成腐烂橘子的四个污染方向
        queue<pair<int,int>> rot;
        for(int i=0;i<row;++i)
            for(int j=0;j<col;++j)
                if(grid[i][j]==2)
                    rot.push({i,j});//将腐烂橘子一一压入队列
        while(!rot.empty()){
            int vol=rot.size();//标记队列内腐烂橘子个数
            for(int i=0;i<vol;++i){
                pair<int,int> fir=rot.front();//取出首个腐烂橘子
                rot.pop();
                for(int j=0;j<4;++j){//进行四个方向污染
                    int x=fir.first+dx[j], y=fir.second+dy[j];
                    if(x>=0&&x<row&&y>=0&&y<col&&grid[x][y]==1){//判断是否存在新鲜橘子
                        grid[x][y]=2;
                        rot.push({x,y});
                    }
                }
            }
            if(!rot.empty())//如果为空表示一开始就没有腐烂橘子，返回0分钟
                res++;//每次取出队列所有橘子时间加1，同时压入被污染的新一批橘子
        }
        for(int i=0;i<row;++i)//检查是否还有新鲜橘子
            for(int j=0;j<col;++j)
                if(grid[i][j]==1)
                    return -1;
        return res;
    }
};


/*-------------------------------
| 题目3：和为S的连续正数序列
| 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
| 序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。
-------------------------------*/
/* 通过规律暴力解决 */
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int target_temp = target / 2;//所有序列中的最大数
        int i,j;//用于循环
        int result_temp_quotient;//记录商
        int result_temp_remainder;//记录余数
        vector<vector<int>> S;//存放结果
        vector<int> res;//存放每一组序列
        for(i=target_temp;i>=2;i--){//某序列中共有i个数
            result_temp_quotient = target / i;
            result_temp_remainder = target % i;
            //若有偶数个正整数，其连续的序列必须为偶数个，因此，只有 target / i 为 x.5 时，才能存在相应序列
            if(i%2 == 0){//序列中有偶数个正整数
                if(result_temp_remainder == i/2){//target与i的商为x.5
                    res.clear();
                    j=target / i + 1 - i / 2;
                    if(j>0){//必须保证j>0，否则对于 target = 15，有可能出现 [0,1,2,3,4,5] 这种序列
                        for(j;j<=target / i + i / 2;j++){
                            res.emplace_back(j);
                        }
                        S.emplace_back(res);
                    }
                }
            }else{//i是奇数
                if(result_temp_remainder == 0){//target必须整除i
                    res.clear();
                    j=target / i - i / 2;
                    if(j>0){//同样必须保证j>0
                        for(j=target / i - i / 2;j<=target / i + i / 2;j++){
                            res.emplace_back(j);
                        }
                        S.emplace_back(res);
                    }
                }
            }
        }
        return S;//返回结果
    }
};


/*-------------------------------
| 题目4：队列的最大值
| 请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。
| 若队列为空，pop_front 和 max_value 需要返回 -1
-------------------------------*/
/* 题解——双端队列 */
class MaxQueue {
    queue<int> q;
    deque<int> d;//用于记录最大元素
public:
    MaxQueue() {
    }
    
    int max_value() {
        if (d.empty())
            return -1;
        return d.front();
    }
    
    void push_back(int value) {
        // 储存最大元素
        while (!d.empty() && d.back() < value) {
            d.pop_back();
        }
        d.push_back(value);
        q.push(value);
    }
    
    int pop_front() {
        if (q.empty())
            return -1;
        int ans = q.front();
        if (ans == d.front()) {
            d.pop_front();
        }
        q.pop();
        return ans;
    }
};


/*-------------------------------
| 题目5：买卖股票的最佳时机
| 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
| 如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。
| 注意你不能在买入股票前卖出股票。
-------------------------------*/
/* 题解——一次遍历 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit=0;
        int miniprice=INT_MAX;//初始值为整型最大值
        for(int price:prices){//遍历所有价格
            profit = max(profit,price-miniprice);//先计算利润
            miniprice = min(miniprice, price);//再更改最小值
        }
        return profit;
    }
};


/*-------------------------------
| 题目6：将数组分成和相等的三个部分
| 给你一个整数数组 A，只有可以将其划分为三个和相等的非空部分时才返回 true，否则返回 false。
| 形式上，如果可以找出索引 i+1 < j 且满足
| (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1])
| 就可以将数组三等分。
-------------------------------*/

/* 我的方法——三分之一和 */
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int i,j=A.size();
        int sum_i=0,sum_middle=0,sum_j=0,sum=0;
        for(i=0;i<A.size();i++){
            sum = sum + A[i]; //求数组和
        }
        if(sum%3 != 0) return false; //不能整除直接false
        i=-1;
        while(sum_i != sum/3 || i==-1){
            i++;
            sum_i = A[i] + sum_i;
            if(i==A.size()-2) return false;
        }
        while(sum_j != sum/3 || j==A.size()){
            j--;
            sum_j = A[j] + sum_j;
            if(j==i+1) return false;
        }
        for(i=i+1;i<j;i++){
            sum_middle = A[i] + sum_middle;
        }
        if(sum_middle != sum/3) return false;
        return true;
    }
};
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int s = accumulate(A.begin(), A.end(), 0);
        if (s % 3 != 0) {
            return false;
        }
        int target = s / 3;
        int n = A.size(), i = 0, cur = 0;
        while (i < n) {
            cur += A[i];
            if (cur == target) {
                break;
            }
            ++i;
        }
        if (cur != target) {
            return false;
        }
        int j = i + 1;
        while (j + 1 < n) { // 需要满足最后一个数组非空
            cur += A[j];
            if (cur == target * 2) { //第一组和第二组的和为 2*target
                return true;
            }
            ++j;
        }
        return false;
    }
};


/*-------------------------------
| 题目7：字符串的最大公因子
| 对于字符串 S 和 T，只有在 S = T + ... + T（T 与自身连接 1 次或多次）时，我们才认定 “T 能除尽 S”。 
| 返回最长字符串 X，要求满足 X 能除尽 str1 且 X 能除尽 str2。
|-注意区分最大公因子和最长相同字符串-|
-------------------------------*/
/* 高效方法 */
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        if (str1 + str2 != str2 + str1) return "";
        return str1.substr(0, __gcd((int)str1.length(), (int)str2.length())); // __gcd() 为c++自带的求最大公约数的函数
    }
};


/*-------------------------------
| 题目8：字符串压缩
| 字符串压缩。利用字符重复出现的次数，编写一种方法，实现基本的字符串压缩功能。
| 比如，字符串aabcccccaaa会变为a2b1c5a3。若“压缩”后的字符串没有变短，则返回原先的字符串。
| 你可以假设字符串中只包含大小写英文字母（a至z）。
-------------------------------*/
/* 我的方法——穷举，string 计算 */
class Solution {
public:
    string compressString(string S) {
        if(S=="") return S;//处理空字符串
        string ans;//储存结果
        string temp=S.substr(0,1);//string 类型才能 append
        int count=1;
        for(int i=1;i<S.size();i++){
            if(temp[0]!=S[i]){
                ans=ans.append(temp);
                temp.erase(0); // 删除 temp 中的首个元素（唯一元素）
                temp=S.substr(i,1); // 将 S 中的元素复制到 temp 中
                ans=ans.append(to_string(count));
                count=1;
            }else{
                count++;
            }
        }
        ans=ans.append(temp);
        ans=ans.append(to_string(count));
        if(ans.size()>=S.size()) return S;
        else return ans;
    }
};

/* 题解——穷举，string 加减计算 */
class Solution {
public:
    string compressString(string S) {
        if ((int)S.length() == 0) return S; // 空串处理
        string ans = "";
        int count = 1;
        char temp = S[0];
        for (int i = 1; i < (int)S.length(); ++i){
            if (temp == S[i]) count++;
            else{
                ans += temp + to_string(count); // 注意 count 要转为字符串
                temp = S[i];
                count = 1;
            }
        }
        ans += temp + to_string(count);
        return ans.length() >= S.length() ? S : ans;
    }
};


/*-------------------------------
| 题目9：矩形重叠
| 矩形以列表 [x1, y1, x2, y2] 的形式表示，其中 (x1, y1) 为左下角的坐标，(x2, y2) 是右上角的坐标。
| 如果相交的面积为正，则称两矩形重叠。需要明确的是，只在角或边接触的两个矩形不构成重叠。
| 给出两个矩形，判断它们是否重叠并返回结果。
-------------------------------*/
/* 我的方法——检查边界 */
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        //矩阵1的左边界要小于矩阵2的右边界，且矩阵1的右边界要大于矩阵2的左边界
        if(rec1[0]<rec2[2] && rec1[2]>rec2[0]){
            //矩阵1的下边界要小于矩阵2的上边界，且矩阵1的上边界要大于矩阵2的下边界
            if(rec1[1]<rec2[3] && rec1[3]>rec2[1]) return true;
        }
        return false;
    }
};

/* 题解——检查区域 */
/*=================================================
| 思路：
| 如果两个矩形重叠，那么它们重叠的区域一定也是一个矩形。
| 那么这两个矩形与 xx 轴平行的边（水平边）投影到 xx 轴上时会有交集，与 yy 轴平行的边（竖直边）投影到 yy 轴上时也会有交集。
| 因此，我们可以将问题看作一维线段是否有交集的问题。
=================================================*/
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        //最小的右边界大于最大的左边界，且最小的上边界大于最大的下边界
        return (min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) &&
                min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]));
    }
};


/*-------------------------------
| 题目10：链表的中间结点
| 给定一个带有头结点 head 的非空单链表，返回链表的中间结点。
| 如果有两个中间结点，则返回第二个中间结点。
-------------------------------*/
/*
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/* 我的方法——遍历链表，找到中间位置*/
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* end=head;
        ListNode* ans=head;
        int count=0;
        while(end != NULL){ //遍历链表
            end=end->next;
            count++; //链表长度
        }
        count=count/2; //中间位置
        for(int i=0;i<count;i++){
            ans=ans->next; //找到中间结点
        }
        return ans;
    }
};

/* 题解 1 ——将链表转化为数组 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        vector<ListNode*> A = {head}; //将链表转化为数组
        while (A.back()->next != NULL)
            A.push_back(A.back()->next); //将下一个结点压入数组
        return A[A.size() / 2];
    }
};

/* 题解 2 ——快慢指针法 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next; //慢指针一次移动一个位置
            fast = fast->next->next; //快指针一次移动两个位置
        }
        return slow; //慢指针最后的位置即为答案位置
    }
};


/*-------------------------------
| 题目11：三维形体的表面积
| 在 N * N 的网格上，我们放置一些 1 * 1 * 1  的立方体。
| 每个值 v = grid[i][j] 表示 v 个正方体叠放在对应单元格 (i, j) 上。
| 请你返回最终形体的表面积。
-------------------------------*/
/* 我的方法——遍历 */
class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int area=0; //存储表面积
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j] != 0) area = area + 4 * grid[i][j] + 2; // 先把总的表面积加起来
                if(j-1>=0 && grid[i][j-1] != 0){ // 有互相覆盖的再删减
                    int diff = grid[i][j] < grid[i][j-1] ? grid[i][j]:grid[i][j-1];
                    area = area - 2 * diff;
                }
                if(i-1>=0 && grid[i-1][j] != 0){ // 有互相覆盖的再删减
                    int diff = grid[i][j] < grid[i-1][j] ? grid[i][j]:grid[i-1][j];
                    area = area - 2 * diff;
                }
            }
        }
        return area;
    }
};


/*-------------------------------
| 题目12：卡牌分组
| 给定一副牌，每张牌上都写着一个整数。
| 此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：
|   每组都有 X 张牌。
|   组内所有的牌上都写着相同的整数。
| 仅当你可选的 X >= 2 时返回 true。
-------------------------------*/
/* 我的方法——暴力求解+剪枝 */
class Solution {
    int count[10000];
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        int N = deck.size();
        if(N<2) return false;
        for (int c: deck) count[c]++;
        vector<int> values; // 存储有效 count
        for (int i = 0; i < 10000; ++i) {
            if (count[i] > 0) {
                // emplace_back 可以更高效的插入元素
                values.emplace_back(count[i]);
            }
        }
        for (int X = 2; X <= N; ++X) {
            if (N % X == 0) { // 元素个数必须能整除 X
                bool flag = 1; // 用于标记结果
                for (int v: values) {
                    if (v % X != 0) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) return true;
            }
        }
        return false;
    }
};


/* 题解——最大公约数 */
class Solution {
    int cnt[10000];
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        // auto 可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型
        // 此处的 auto 的作用与 int 类似
        for (auto x: deck) cnt[x]++;
        int g = -1;
        for (int i = 0; i < 10000; ++i) if(cnt[i]) {
            if (~g) g = gcd(g, cnt[i]); // 求最大公约数
            else g = cnt[i];
        }
        return g >= 2 ? true : false;
    }
};


/*-------------------------------
| 题目13：旋转矩阵
| 给你一幅由 N × N 矩阵表示的图像，其中每个像素的大小为 4 字节。
| 请你设计一种算法，将图像旋转 90 度。
| 不占用额外内存空间能否做到？
-------------------------------*/
/* 我的——使用辅助数组 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // C++ 这里的 = 拷贝是值拷贝，会得到一个新的数组
        auto matrix_new = matrix;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix_new[j][n - i - 1] = matrix[i][j]; // 旋转数组内元素
            }
        }
        // 这里也是值拷贝
        matrix = matrix_new;
    }
};

/* 我的——原地旋转 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // 重要的是 i 和 j 的取值
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {
                int temp = matrix[i][j]; // 临时变量存储会被覆盖的元素
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = temp;
            }
        }
    }
};

/* 题解——用翻转代替旋转 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // 水平翻转
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(matrix[i][j], matrix[n - i - 1][j]);
            }
        }
        // 主对角线翻转
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};


/*-------------------------------
| 题目14：两数之和
| 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。
| 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
-------------------------------*/
/* hash表 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> m;
        for(int i=0;i<nums.size();i++) {
            if(m.find(target-nums[i]) != m.end()) // m中存在对应的键值
                // m[target-nums[i]]为已经加入map的元素的索引，所以小于本轮循环中的i，放在前面
                return {m[target-nums[i]], i};

            m[nums[i]]=i; // 向map中添加元素
        }
        return {}; // 找不到就返回空
    }
};


/*-------------------------------
| 题目15：二叉树的层序遍历
| 给你一个二叉树，请你返回其按层序遍历得到的节点值。（即逐层地，从左到右访问所有节点）。
-------------------------------*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/* 队列 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans; // 储存最后结果
        if(root == NULL) return ans;
        
        queue<TreeNode *> q; // 储存节点
        q.push(root); // 先让根节点进
        while(!q.empty()){
            int CurrentLevelSize = q.size(); // 当前层次元素的个数
            ans.push_back(vector<int> ());
            for(int i=1;i<=CurrentLevelSize;++i){
                auto node = q.front();
                q.pop(); // 已有 node 承接，便可弹出该节点
                ans.back().push_back(node->val); // ans 数组的最后一个一维数组承接新点
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return ans;
    }
};


/*-------------------------------
| 题目16：只出现一次的数字
| 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。
| 找出那个只出现了一次的元素。
| 你的算法应该具有线性时间复杂度，且不使用额外空间。 
-------------------------------*/
/* 位运算——高效 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0; // 记录结果
        for (auto e: nums) ret ^= e; // 进行异或运算
        return ret;
    }
};


/*-------------------------------
| 题目17：和为K的子数组
| 给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
| 例如：
| 输入:nums = [1,1,1], k = 2
| 输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
-------------------------------*/
/* 前缀和+hash表 */
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp; // 
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x:nums) {
            pre += x; // 前缀在递增
            // 从hash表中找目标元素，即前缀和 - 目标值 k
            // 如果已有这个值了，说明找到了
            if (mp.find(pre - k) != mp.end()) count += mp[pre - k];
            mp[pre]++; // 把新前缀和存入hash表
        }
        return count;
    }
};


/*-------------------------------
| 题目18：反转链表II
| 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
| 提示：
| 链表中节点数目为 n
| 1 <= n <= 500
| -500 <= Node.val <= 500
| 1 <= left <= right <= n
-------------------------------*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *reverseBetween(struct ListNode *head, int left, int right) {
    // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
    struct ListNode *dummyNode = malloc(sizeof(struct ListNode));
    dummyNode->val = -1;
    dummyNode->next = head;

    struct ListNode *pre = dummyNode;
    for (int i = 0; i < left - 1; i++) {
        pre = pre->next;
    }
    struct ListNode *cur = pre->next;
    struct ListNode *next;
    for (int i = 0; i < right - left; i++) {
        next = cur->next;
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
    }
    return dummyNode->next;
}


/*-------------------------------
| 题目19：逆波兰表达式求值
| 有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。
| 说明：
| 整数除法只保留整数部分。
| 给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
-------------------------------*/
bool isNumber(char* token){
    return strlen(token) > 1 || ('0' <= token[0] && token[0] <= '9');
}
int evalRPN(char ** tokens, int tokensSize){
    int array[tokensSize];
    int i,tail=0;
    for(i=0;i<tokensSize;i++){
        char* token = tokens[i];
        if(isNumber(token)){
            array[tail++] = atoi(token);
            continue;
        }else{
            int num1 = array[--tail];
            int num2 = array[--tail];
            switch(token[0]){
                case '+':
                    array[tail++] = num2 + num1;
                    break;
                case '-':
                    array[tail++] = num2 - num1;
                    break;
                case '*':
                    array[tail++] = num2 * num1;
                    break;
                case '/':
                    array[tail++] = num2 / num1;
                    break;
            }
        }
    }
    return array[tail-1];
}

/*-------------------------------
| 题目20：黑板异或游戏(数学推理)
| 黑板上写着一个非负整数数组 nums[i] 。Alice 和 Bob 轮流从黑板上擦掉一个数字，Alice 先手。如果擦除一个数字后，剩余的所有数字按位异或运算得出的结果等于 0 的话，当前玩家游戏失败。 (另外，如果只剩一个数字，按位异或运算得到它本身；如果无数字剩余，按位异或运算结果为 0。）
| 换种说法就是，轮到某个玩家时，如果当前黑板上所有数字按位异或运算结果等于 0，这个玩家获胜。
| 假设两个玩家每步都使用最优解，当且仅当 Alice 获胜时返回 true。
-------------------------------*/
class Solution {
public:
    bool xorGame(vector<int>& nums) {
        //数组大小为偶数时，先手一定赢
        if(nums.size()%2 == 0){
            return true;
        }

        //否则，要看全部数组元素的异或值，为0则先手一开始就赢了，不为0，则后手一定赢（等同于第一种情况，即数组大小为偶数时的先手）
        int sum = 0;
        for(auto num:nums){
            sum = sum ^ num;
        }
        return sum == 0;
    }
};