/* 目录 */
/*=========================================
题目1：零钱兑换（动态规划、剪枝+dfs）
题目2：二叉树的直径（dfs）
题目3：多数元素（hash表、分治）
题目4：岛屿的最大面积（dfs、bfs）
题目5：反转链表（递归）
题目6：K 个一组翻转链表（与题5对比，暴力法）
题目7：构造最长回文串（贪心）
题目8：验证回文字符串 Ⅱ（贪心）
题目9：最小的k个数（大根堆）
题目10：水壶问题（dfs、贝祖定理）
题目11：使数组唯一的最小增量（线性探测）
题目12：按摩师（动态规划）
题目13：单词的压缩编码（字典树）
题目14：地图分析（BFS、多源最短路径、动态规划）
题目15：圆圈中最后剩下的数字（数学+递归/迭代）
题目16：字符串转换整数 (自动机)
题目17：接雨水（动态编程+栈+双指针+找规律）
题目18：编辑距离(动态规划)
题目19：机器人的运动范围（bfs+递推）
题目20：括号生成（回溯、递归）
题目21：乘积最大子数组（动态规划）
题目22：x 的平方根（袖珍计算器算法、二分查找、牛顿迭代）
题目23：找出第 K 大的异或坐标值（前缀和+STL内置快排）
题目24：前K个高频单词（哈希表+优先队列）
题目25：奇怪的打印机（动态规划）
=========================================*/


/*-------------------------------
| 题目1：零钱兑换
| 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
| 如果没有任何一种硬币组合能组成总金额，返回 -1。
-------------------------------*/

/* 我的方法——动态规划，在子集合中找最优解 */
class Solution {
    vector<int> count;//用于计数，
    int dp(vector<int>& coins, int total) {
        if (total < 0) return -1;
        if (total == 0) return 0;
        if (count[total - 1] != 0) return count[total - 1];
        int Min = INT_MAX;//INT_MAX是整型最大值
        for (int coin:coins) {//对每种面额做计算
            //在 total-coin 中再找最优解，依次类推，找完 coins 中的所有面额
            int res = dp(coins, total - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[total - 1] = Min == INT_MAX ? -1 : Min;
        return count[total - 1];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1) return 0;

        //重设计数容器的大小，且其中的元素默认为0
        count.resize(amount);
        return dp(coins, amount);
    }
};

/* 题解——DFS+剪枝 贪心算法 */
class Solution {
    int ans=INT_MAX;//整型最大值
public:
    //c_index用于记录coins的元素下标；&ans为引用，实际取参数的地址。
    void coinChange(vector<int>& coins, int amount, int c_index, int count, int& ans){
        if (amount == 0){//结束条件
            ans = min(ans, count);
            return;
        }
        if (c_index == coins.size()) return;//此时coins[c_index]为null
        
        //k是coins[c_index]的个数
        for (int k = amount / coins[c_index]; k >= 0 && k + count < ans; k--){
            //amount - k * coins[c_index]是需要凑的剩余金额
            coinChange(coins, amount - k * coins[c_index], c_index + 1, count + k, ans);
        }
    }

    int coinChange(vector<int>& coins, int amount){
        if (amount == 0) return 0;
        sort(coins.rbegin(), coins.rend());//对coins逆向排序（从大到小）
        coinChange(coins, amount, 0, 0, ans);
        return ans == INT_MAX ? -1 : ans;
    }
};


/*-------------------------------
| 题目2：二叉树的直径
| 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。
| 这条路径可能穿过根结点。
-------------------------------*/
/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*我的方法——递归求深度，也是深度优先搜索（dfs） */
class Solution {
    int count = 0;//记录直径
public:
    int dp(TreeNode* root, int& count){
        if(root == NULL) return 0;
        int left_depth = dp(root->left, count);
        int right_depth = dp(root->right, count);
        int count_temp = left_depth + right_depth;
        count = (count_temp > count) ? count_temp : count;//记录直径最大值
        return (left_depth >= right_depth ? left_depth  : right_depth) + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        dp(root, count);
        return count;
    }
};


/*-------------------------------
| 题目3：多数元素
| 给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
| 假设数组是非空的，并且给定的数组总是存在多数元素。
-------------------------------*/

/* 暴力求解——hash表 */
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counts;//映射
        int majority = 0, cnt = 0;
        for (int num: nums) {
            ++counts[num];
            if (counts[num] > cnt) {
                majority = num;
                cnt = counts[num];
            }
        }
        return majority;
    }
};

/* 题解——排序 */
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //因为必定存在
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

/* 题解——分治（递归） */
class Solution {
    int count_in_range(vector<int>& nums, int target, int begin, int end) {
        int count = 0;
        for (int i = begin; i <= end; ++i)
            if (nums[i] == target)
                ++count;
        return count;
    }
    int majority_element_rec(vector<int>& nums, int begin, int end) {
        if (begin == end)
            return nums[begin];
        int mid = (begin + end) / 2;
        int left_majority = majority_element_rec(nums, begin, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, begin, end) > (end - begin + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, begin, end) > (end - begin + 1) / 2)
            return right_majority;
        return -1;
    }
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }
};


/*-------------------------------
| 题目4：岛屿的最大面积
| 给定一个包含了一些 0 和 1的非空二维数组 grid , 一个岛屿是由四个方向 (水平或垂直) 的 1 (代表土地) 构成的组合。
| 你可以假设二维矩阵的四个边缘都被水包围着。
| 找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为0。)
-------------------------------*/
/* 题解——深度优先搜索 */
class Solution {
    int dfs(vector<vector<int>>& grid, int cur_i, int cur_j) {
        if (cur_i < 0 || cur_j < 0 || cur_i == grid.size() || cur_j == grid[0].size() || grid[cur_i][cur_j] != 1)
            return 0;
        int ans = 1;
        grid[cur_i][cur_j] = 0;//因为 ans 是从 1 算起
        int di[4] = {0, 0, 1, -1};
        int dj[4] = {1, -1, 0, 0};
        for (int index = 0; index != 4; ++index) {
            int next_i = cur_i + di[index], next_j = cur_j + dj[index];
            ans += dfs(grid, next_i, next_j);
        }
        return ans;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i = 0; i != grid.size(); ++i)
            for (int j = 0; j != grid[0].size(); ++j)
                ans = max(ans, dfs(grid, i, j));//取最大值
        return ans;
    }
};

/* 题解——广度优先搜索 */
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i = 0; i != grid.size(); ++i)
            for (int j = 0; j != grid[0].size(); ++j) {
                int cur = 0;
                queue<int> queuei;
                queue<int> queuej;
                queuei.push(i);
                queuej.push(j);
                while (!queuei.empty()) {
                    int cur_i = queuei.front(), cur_j = queuej.front();
                    queuei.pop();
                    queuej.pop();
                    if (cur_i < 0 || cur_j < 0 || cur_i == grid.size() || cur_j == grid[0].size() || grid[cur_i][cur_j] != 1)
                        continue;
                    ++cur;
                    grid[cur_i][cur_j] = 0;
                    int di[4] = {0, 0, 1, -1};
                    int dj[4] = {1, -1, 0, 0};
                    for (int index = 0; index != 4; ++index) {
                        int next_i = cur_i + di[index], next_j = cur_j + dj[index];
                        queuei.push(next_i);
                        queuej.push(next_j);
                    }
                }
                ans = max(ans, cur);
            }
        return ans;
    }
};


/*-------------------------------
| 题目5：反转链表
| 反转一个单链表。
| 输入: 1->2->3->4->5->NULL
| 输出: 5->4->3->2->1->NULL
-------------------------------*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
**/

/* 题解——递归 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==NULL || head->next==NULL) return head;
        ListNode* ansList;
        ansList = reverseList(head->next);
        head->next->next = head;//很重要
        head->next=NULL;
        return ansList;
    }
};


/*-------------------------------
| 题目6：K 个一组翻转链表
| 给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
| k 是一个正整数，它的值小于或等于链表的长度。
| 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
| 你的算法只能使用常数的额外空间。
| 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
-------------------------------*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/* 暴力 */
class Solution {
public:
    // 反转链表，返回新的头和尾
    pair<ListNode*, ListNode*> reverse(ListNode* head, ListNode* end){
        ListNode* pre = end->next;
        ListNode* p = head;
        while(pre != end){ // 反转链表
            ListNode* nex = p->next;
            p->next = pre;
            pre = p;
            p = nex;
        }
        return {end, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* hair = new ListNode(0);
        hair->next = head;
        ListNode* pre = hair;

        while(head){
            ListNode* end = pre;
            // 查看剩余部分是否大于等于 k
            for(int i=0;i<k;++i){
                end = end->next;
                if(!end){
                    return hair->next;
                }
            }
            ListNode* nex = end->next;
            tie(head, end) = reverse(head, end);

            // 把头和尾重新链上
            pre->next = head;
            end->next = nex;
            pre = end;
            head = end->next;
        }
        return hair->next;
    }
};


/*-------------------------------
| 题目7：构造最长回文串
| 给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。
| 在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。
| 注意：假设字符串的长度不会超过 1010。
-------------------------------*/
/* 题解——贪心算法 */
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> count; // 映射
        int ans = 0;
        for (char c : s) // 遍历每一个字符
            ++count[c];
        for (auto p : count) {
            int v = p.second; // 每个字符的个数
            ans += v / 2 * 2;
            if (v % 2 == 1 and ans % 2 == 0)
                ++ans;
        }
        return ans;
    }
};


/*-------------------------------
| 题目8：验证回文字符串 Ⅱ
| 给定一个非空字符串 s，最多删除一个字符。
| 判断是否能成为回文字符串。
-------------------------------*/
/* 题解——贪心 */
class Solution {
public:
    bool check(string& s, int low, int high){ // 检查是否是回文串
        for(int i=low, j=high;i<j;i++,j--){
            if(s[i] != s[j]) return false;
        }
        return true;
    }
    bool validPalindrome(string s) {
        bool ans;
        int low=0, high=s.size()-1;
        
        while(low<high){
            char c1=s[low], c2=s[high];
            if(c1==c2){
                // 一切正常的做法
                low++;
                high--;
            }else{
                // 删除一个字符
                return check(s, low, high-1) || check(s, low+1, high);
            }
        }
        return true;
    }
};


/*-------------------------------
| 题目9：最长回文子串
| 给定一个字符串 s，找到 s 中最长的回文子串。
| 你可以假设 s 的最大长度为 1000。
-------------------------------*/
/* 中心扩展——O(n^2) 和 O(1) */
class Solution {
public:
    // 中心扩展
    pair<int,int> centerexpend(string& s, int left, int right){
        while(left>=0 && right<s.size() && s[left]==s[right]){
            left--;
            right++;
        }
        return {left+1, right-1};
    }
    string longestPalindrome(string s) {
        int start=0, end=0; // 记录最长回文串的首尾位置
        for(int i=0;i<s.size();i++){
            // 分别计算，因为有可能涉及到字符长度奇偶数的问题
            auto [left1, right1] = centerexpend(s,i,i); // 奇数时
            auto [left2, right2] = centerexpend(s,i,i+1); // 偶数时
            if(right1 - left1 > end - start){
                start = left1;
                end = right1;
            }
            if(right2 - left2 > end - start){
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end-start+1);
    }
};

/* Manacher 算法——O(n) 和 O(n) */
class Solution {
public:
    int expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }

        // 返回中心位置
        return (right - left - 2) / 2;
    }

    string longestPalindrome(string s) {
        int start = 0, end = -1;
        string t = "#";
        for (char c: s) {
            t += c;
            t += '#';
        }
        t += '#';
        s = t;

        vector<int> arm_len; // 臂长，中心向外扩展的长度
        int right = -1, j = -1;
        for (int i = 0; i < s.size(); ++i) {
            int cur_arm_len;
            if (right >= i) {
                int i_sym = j * 2 - i;
                int min_arm_len = min(arm_len[i_sym], right - i);
                cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
            }
            else {
                cur_arm_len = expand(s, i, i);
            }
            arm_len.push_back(cur_arm_len);
            if (i + cur_arm_len > right) {
                j = i;
                right = i + cur_arm_len;
            }
            if (cur_arm_len * 2 + 1 > end - start) {
                start = i - cur_arm_len;
                end = i + cur_arm_len;
            }
        }

        string ans;
        for (int i = start; i <= end; ++i) {
            if (s[i] != '#') {
                ans += s[i];
            }
        }
        return ans;
    }
};


/*-------------------------------
| 题目9：最小的k个数
| 输入整数数组 arr ，找出其中最小的 k 个数。
| 例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
-------------------------------*/
/* 我的方法——调用库函数 sort() */
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());//先排序
        vector<int> ans(k);
        for(int i=0;i<k;i++){
            ans[i] = arr[i];
        }
        return ans;
    }
};

/* 题解——大根堆 */
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> vec(k, 0);
        if (k == 0) return vec; // 排除 0 的情况
        priority_queue <int>Q; // 大根堆
        for (int i = 0; i < k; ++i) Q.push(arr[i]); //将前k个元素压入堆
        for (int i = k; i < (int)arr.size(); ++i) { //后面的元素与堆中的元素作比较
            if (Q.top() > arr[i]) { //堆顶元素大，则弹出
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i) {
            vec[i] = Q.top();
            Q.pop();
        }
        return vec;
    }
};


/*-------------------------------
| 题目10：水壶问题
| 有两个容量分别为 x 升和 y 升的水壶以及无限多的水。
| 请判断能否通过使用这两个水壶，从而可以得到恰好 z 升的水？
| 如果可以，最后请用以上水壶中的一或两个来盛放取得的 z 升水。
| 你可以进行以下操作：
| 装满任意一个水壶
| 清空任意一个水壶
| 从一个水壶向另外一个水壶倒水，直到装满或者倒空。
-------------------------------*/
/* 计算机方法——DFS（用栈模拟递归） */
using PII = pair<int, int>;
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        stack<PII> stk; //用于模拟递归
        stk.emplace(0, 0);
        auto hash_function = [](const PII& o) {return hash<int>()(o.first) ^ hash<int>()(o.second);};
        unordered_set<PII, decltype(hash_function)> seen(0, hash_function);
        while (!stk.empty()) {
            if (seen.count(stk.top())) {
                stk.pop();
                continue;
            }
            seen.emplace(stk.top());
            //remain_x, remain_y 分别保存 x 和 y 的剩余的水量
            auto [remain_x, remain_y] = stk.top();
            stk.pop();
            if (remain_x == z || remain_y == z || remain_x + remain_y == z) {
                return true;
            }
            // 把 X 壶灌满。
            stk.emplace(x, remain_y);
            // 把 Y 壶灌满。
            stk.emplace(remain_x, y);
            // 把 X 壶倒空。
            stk.emplace(0, remain_y);
            // 把 Y 壶倒空。
            stk.emplace(remain_x, 0);
            // 把 X 壶的水灌进 Y 壶，直至灌满或倒空。
            stk.emplace(remain_x - min(remain_x, y - remain_y), remain_y + min(remain_x, y - remain_y));
            // 把 Y 壶的水灌进 X 壶，直至灌满或倒空。
            stk.emplace(remain_x + min(remain_y, x - remain_x), remain_y - min(remain_y, x - remain_x));
        }
        return false;
    }
};

/* 数学方法——贝祖定理（具体看有道云笔记） */
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        if (x + y < z) return false;
        if (x == 0 || y == 0) return z == 0 || x + y == z;
        return z % gcd(x, y) == 0;
    }
};


/*-------------------------------
| 题目11：使数组唯一的最小增量
| 给定整数数组 A，每次 move 操作将会选择任意 A[i]，并将其递增 1。
| 返回使 A 中的每个值都是唯一的最少操作次数。
-------------------------------*/
/* 我的方法——排序+加差值 */
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        int count=0, temp;
        sort(A.begin(), A.end());
        for(int i=1;i<A.size();i++){
            if(A[i-1] >= A[i]){
                temp=A[i];//保存 老A[i] 的值
                A[i] = A[i-1]+1;//更新 A[i] 的值
                count = count+A[i]-temp;//需要 move 的次数是 新A[i] 与 老A[i] 间的差值
            }
        }
        return count;
    }
};

/* 题解——线性探测（类似hash探测） */
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        if (A.empty()) return 0;
        int res = 0;
        vector<int> pos(80000, -1); // -1表示空位
        // 遍历每个数字a对其寻地址得到位置b, b比a的增量就是操作数。
        for (int a: A){
            int b = findPos(a, pos);// 进行线性探测
            res += b-a;
        }
        return res;
    }
    // 线性探测寻址(状态压缩)
    int findPos(int a, vector<int> &pos){
        int b = pos[a];
        // a对应的位置pos[a]是空位，直接放入
        if (b==-1){
            pos[a] = a;
            return a;
        }
        b = findPos(b+1, pos);// 向后寻址
        pos[a] = b;
        return b;
    }
};


/*-------------------------------
| 题目12：按摩师
| 一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。
| 在每次预约服务之间要有休息时间，因此她不能接受相邻的预约。
| 给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。
-------------------------------*/
/* 题解——动态规划 */
class Solution {
public:
    int massage(vector<int>& nums) {
        int n = (int)nums.size();
        if (!n) return 0;
        int dp0 = 0, dp1 = nums[0];

        for (int i = 1; i < n; ++i){
            int tdp0 = max(dp0, dp1); // 计算 dp[i][0]
            int tdp1 = dp0 + nums[i]; // 计算 dp[i][1]

            dp0 = tdp0; // 用 dp[i][0] 更新 dp_0
            dp1 = tdp1; // 用 dp[i][1] 更新 dp_1
        }
        return max(dp0, dp1);
    }
};


/*-------------------------------
| 题目13：单词的压缩编码
| 给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A。
| 例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示为 S = "time#bell#" 和 indexes = [0, 2, 5]。
| 对于每一个索引，我们可以通过从字符串 S 中索引的位置开始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。
| 那么成功对给定单词列表进行编码的最小字符串长度是多少呢？
-------------------------------*/
/* 我的方法——枚举 */
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        unordered_set<string> good(words.begin(), words.end());
        for (const string& word: words) {
            for (int k = 1; k < word.size(); ++k) {
                good.erase(word.substr(k)); // 删除后缀单词
            }
        }

        int ans = 0;
        for (const string& word: good) {
            ans += word.size() + 1; // 总长度为删减剩下的每个单词长度加 1 之和（需要算 # ）
        }
        return ans;
    }
};

/* 题解——字典树 */
// 树的类
class TrieNode{
    TrieNode* children[26]; // 26 个英文字母
public:
    int count;
    TrieNode() {
        for (int i = 0; i < 26; ++i) children[i] = NULL;
        count = 0;
    }
    TrieNode* get(char c) {
        if (children[c - 'a'] == NULL) {
            children[c - 'a'] = new TrieNode();
            count++;
        }
        return children[c - 'a'];
    }
};
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        TrieNode* trie = new TrieNode();
        unordered_map<TrieNode*, int> nodes;

        for (int i = 0; i < (int)words.size(); ++i) {
            string word = words[i];
            TrieNode* cur = trie;
            for (int j = word.length() - 1; j >= 0; --j)
                cur = cur->get(word[j]);
            nodes[cur] = i;
        }

        int ans = 0;
        for (auto& [node, idx] : nodes) {
            if (node->count == 0) {
                ans += words[idx].length() + 1;
            }
        }
        return ans;
    }
};


/*-------------------------------
| 题目14：地图分析
| 你现在手里有一份大小为 N x N 的『地图』（网格） grid，上面的每个『区域』（单元格）都用 0 和 1 标记好了。
| 其中 0 代表海洋，1 代表陆地，你知道距离陆地区域最远的海洋区域是是哪一个吗？
| 请返回该海洋区域到离它最远的陆地区域的距离。
| 我们这里说的距离是『曼哈顿距离』（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个区域之间的距离是 |x0 - x1| + |y0 - y1| 。
| 如果我们的地图上只有陆地或者海洋，请返回 -1。
-------------------------------*/
/* 题解——广度优先算法 */
class Solution {
public:
    static constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; // 常量增量数组
    static constexpr int MAX_N = 100 + 5;

    // 坐标结构
    struct Coordinate {
        int x, y, step;
    };

    int n, m;
    vector<vector<int>> a;

    bool vis[MAX_N][MAX_N];

    int findNearestLand(int x, int y) {
        memset(vis, 0, sizeof vis); // 初始化 vis 数组
        queue <Coordinate> q; // 坐标队列
        q.push({x, y, 0}); // 将初试坐标压入队列
        vis[x][y] = 1; // 做遍历标记
        while (!q.empty()) {
            auto f = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) { // 向上下左右 4 个方向搜索
                int nx = f.x + dx[i], ny = f.y + dy[i];
                // 到边界了就结束本次循环
                if (!(nx >= 0 && nx <= n - 1 && ny >= 0 && ny <= m - 1)) continue;
                if (!vis[nx][ny]) { // 未遍历过
                    q.push({nx, ny, f.step + 1}); // 压入队列
                    vis[nx][ny] = 1;
                    if (a[nx][ny]) return f.step + 1;
                }
            }
        }
        return -1; // 找不到陆地，返回-1
    }
    
    int maxDistance(vector<vector<int>>& grid) {
        this->n = grid.size();
        this->m = grid.at(0).size();
        a = grid;
        int ans = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!a[i][j]) { // 非 0 ，不是海洋
                    ans = max(ans, findNearestLand(i, j));
                }
            }
        }
        return ans;
    }
};

/* 题解——多源最短路（Dijkstra） */
class Solution {
public:
    static constexpr int MAX_N = 100 + 5;
    static constexpr int INF = int(1E6);
    static constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    int n;
    int d[MAX_N][MAX_N];

    struct Status {
        int v, x, y;
        bool operator < (const Status &rhs) const {
            return v > rhs.v;
        }
    };

    priority_queue <Status> q;

    int maxDistance(vector<vector<int>>& grid) {
        this->n = grid.size();
        auto &a = grid;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = INF;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i][j]) {
                    d[i][j] = 0;
                    q.push({0, i, j});
                }
            }
        }

        while (!q.empty()) {
            auto f = q.top(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = f.x + dx[i], ny = f.y + dy[i];
                if (!(nx >= 0 && nx <= n - 1 && ny >= 0 && ny <= n - 1)) continue;
                if (f.v + 1 < d[nx][ny]) {
                    d[nx][ny] = f.v + 1;
                    q.push({d[nx][ny], nx, ny});
                }
            }
        }

        int ans = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!a[i][j]) ans = max(ans, d[i][j]);
            }
        }

        return (ans == INF) ? -1 : ans;
    }
};

/* 题解——动态规划 */
class Solution {
public:
    static constexpr int MAX_N = 100 + 5;
    static constexpr int INF = int(1E6);
    
    int f[MAX_N][MAX_N];
    int n;

    int maxDistance(vector<vector<int>>& grid) {
        this->n = grid.size();
        vector<vector<int>>& a = grid;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                f[i][j] = (a[i][j] ? 0 : INF);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i][j]) continue;
                if (i - 1 >= 0) f[i][j] = min(f[i][j], f[i - 1][j] + 1);
                if (j - 1 >= 0) f[i][j] = min(f[i][j], f[i][j - 1] + 1);
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (a[i][j]) continue;
                if (i + 1 < n) f[i][j] = min(f[i][j], f[i + 1][j] + 1);
                if (j + 1 < n) f[i][j] = min(f[i][j], f[i][j + 1] + 1);
            }
        }

        int ans = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!a[i][j]) {
                    ans = max(ans, f[i][j]);
                }
            }
        }

        if (ans == INF) return -1;
        else return ans;
    }
};


/*-------------------------------
| 题目15：圆圈中最后剩下的数字
| 0,1,...,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。
| 求出这个圆圈里剩下的最后一个数字。
| 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
-------------------------------*/
/* 题解——数学+递归 */
class Solution {
    int f(int n, int m) {
        if (n == 1)
            return 0;
        int x = f(n - 1, m);
        return (m + x) % n;
    }
public:
    int lastRemaining(int n, int m) {
        return f(n, m);
    }
};

/* 题解——数学+迭代 */
class Solution {
public:
    int lastRemaining(int n, int m) {
        int f = 0;
        for (int i = 2; i != n + 1; ++i)
            f = (m + f) % i;
        return f;
    }
};


/*-------------------------------
| 题目16：字符串转换整数 (atoi)
| 请你来实现一个 atoi 函数，使其能将字符串转换成整数。
| 首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。接下来的转化规则如下：
| 如果第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字字符组合起来，形成一个有符号整数。
| 假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成一个整数。
| 该字符串在有效的整数部分之后也可能会存在多余的字符，那么这些字符可以被忽略，它们对函数不应该造成影响。
| 注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换，即无法进行有效转换。
| 在任何情况下，若函数不能进行有效的转换时，请返回 0 。
| 提示：
| 本题中的空白字符只包括空格字符 ' ' 。
| 假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 − 1]。
| 如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。
-------------------------------*/
/* 题解——自动机 */
class Automaton {
    string state = "start";
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };

    int get_col(char c) { // 判断字符是啥
        if (isspace(c)) return 0; // 是空格
        if (c == '+' or c == '-') return 1; // 是正负号
        if (isdigit(c)) return 2; // 是数字
        return 3;
    }
public:
    int sign = 1;
    long long ans = 0; // 先把 ans 存储为最大范围的整形

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }else if (state == "signed") sign = c == '+' ? 1 : -1;
    }
};

class Solution {
public:
    int myAtoi(string str) {
        Automaton automaton;
        for (char c : str) // 遍历字符串中的每个字符
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};


/*-------------------------------
| 题目17：接雨水
| 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
| 示例:
| 输入: [0,1,0,2,1,0,1,3,2,1,2,1]
| 输出: 6
-------------------------------*/
/* 题解——暴力求解（中间向两边找） */
int trap(vector<int>& height){
    int ans = 0;
    int size = height.size();
    for (int i = 1; i < size - 1; i++) {
        int max_left = 0, max_right = 0;
        for (int j = i; j >= 0; j--) { // 左边的最大高度
            max_left = max(max_left, height[j]);
        }
        for (int j = i; j < size; j++) { // 右边的最大高度
            max_right = max(max_right, height[j]);
        }
        ans += min(max_left, max_right) - height[i]; // 最大高度的较小值减当前高度
    }
    return ans;
}

/* 题解——动态编程 */
int trap(vector<int>& height){
	if(height == null)
		return 0;
    int ans = 0;
    int size = height.size();
    vector<int> left_max(size), right_max(size);
    left_max[0] = height[0];
    for (int i = 1; i < size; i++) {
        left_max[i] = max(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = max(height[i], right_max[i + 1]);
    }
    for (int i = 1; i < size - 1; i++) {
        ans += min(left_max[i], right_max[i]) - height[i];
    }
    return ans;
}

/* 题解——栈 */
int trap(vector<int>& height){
    int ans = 0, current = 0;
    stack<int> st;
    while (current < height.size()) {
        while (!st.empty() && height[current] > height[st.top()]) {
            int top = st.top();
            st.pop();
            if (st.empty())
                break;
            int distance = current - st.top() - 1;
            int bounded_height = min(height[current], height[st.top()]) - height[top];
            ans += distance * bounded_height;
        }
        st.push(current++);
    }
    return ans;
}

/* 题解——双指针 */
int trap(vector<int>& height)
{
    int left = 0, right = height.size() - 1;
    int ans = 0;
    int left_max = 0, right_max = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
            ++left;
        }
        else {
            height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
            --right;
        }
    }
    return ans;
}

/* 题解——找规律 */
class Solution {
public:
    //以最大值分界，左边非减，右边非增
    int trap(vector<int>& height) {
        int n=height.size();
        if(n==0) return 0;
        int m=max_element(height.begin(),height.end())-height.begin();
        //遍历最大值左边
        int res=0,cur=height[0];
        for(int i=1;i<m;i++) {
            if(height[i]<cur)
                res+=cur-height[i];
            else
                cur=height[i];
        }
        //遍历最大值右边
        cur=height[n-1];
        for(int i=n-2;i>m;i--) {
            if(height[i]<cur)
                res+=cur-height[i];
            else
                cur=height[i];
        }
        return res;
    }
};


/*-------------------------------
| 题目18：编辑距离
| 给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。
| 你可以对一个单词进行如下三种操作：
| 插入一个字符
| 删除一个字符
| 替换一个字符
-------------------------------*/
/* 题解——动态规划 */
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(); // 字符串求长度用 length()
        int m = word2.length();

        // 有一个字符串为空串
        if (n * m == 0) return n + m;

        // DP 数组
        int D[n + 1][m + 1];

        // 边界状态初始化
        for (int i = 0; i < n + 1; i++) {
            D[i][0] = i;
        }
        for (int j = 0; j < m + 1; j++) {
            D[0][j] = j;
        }

        // 计算所有 DP 值
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                int left = D[i - 1][j] + 1; // 转化为子问题
                int down = D[i][j - 1] + 1;
                int left_down = D[i - 1][j - 1];
                if (word1[i - 1] != word2[j - 1]) left_down += 1;
                D[i][j] = min(left, min(down, left_down));

            }
        }
        return D[n][m];
    }
};


/*-------------------------------
| 题目19：机器人的运动范围
| 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
| 一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。
| 例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
-------------------------------*/
/* 题解——广度优先 */
class Solution {
    // 计算 x 的数位之和
    int get(int x) {
        int res=0;
        for (; x; x /= 10) {
            res += x % 10;
        }
        return res;
    }
public:
    int movingCount(int m, int n, int k) {
        if (!k) return 1;
        queue<pair<int,int> > Q;
        // 向右和向下的方向数组
        int dx[2] = {0, 1};
        int dy[2] = {1, 0};
        vector<vector<int> > vis(m, vector<int>(n, 0)); // 用于做标记
        Q.push(make_pair(0, 0)); // 把可以到达的点压入队列
        vis[0][0] = 1;
        int ans = 1;
        while (!Q.empty()) {
            auto [x, y] = Q.front(); // 弹出最前面的点
            Q.pop();
            for (int i = 0; i < 2; ++i) {
                int tx = dx[i] + x;
                int ty = dy[i] + y;
                // 保证条件
                if (tx < 0 || tx >= m || ty < 0 || ty >= n || vis[tx][ty] || get(tx) + get(ty) > k) continue;
                Q.push(make_pair(tx, ty)); // 将可以到达的点压入队列
                vis[tx][ty] = 1; // 做标记
                ans++;
            }
        }
        return ans;
    }
};

/* 题解——递推 */
class Solution {
    int get(int x) {
        int res=0;
        for (; x; x /= 10){
            res += x % 10;
        }
        return res;
    }
public:
    int movingCount(int m, int n, int k) {
        if (!k) return 1;
        vector<vector<int> > vis(m, vector<int>(n, 0)); // 用于做标记
        int ans = 1;
        vis[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 条件判断
                if ((i == 0 && j == 0) || get(i) + get(j) > k) continue;
                // 边界判断
                if (i - 1 >= 0) vis[i][j] = vis[i - 1][j];
                if (j - 1 >= 0) vis[i][j] = vis[i][j - 1];
                ans += vis[i][j];
            }
        }
        return ans;
    }
};


/*-------------------------------
| 题目20：括号生成
| 数字 n 代表生成括号的对数。
| 请你设计一个函数，用于能够生成所有可能的并且有效的括号组合。
-------------------------------*/
/* 题解——暴力求解 */
class Solution {
    bool valid(const string& str) { // 用于判断括号的有效性
        int balance = 0;
        for (char c : str)
            if (c == '(') // 有一个左括号，后面就可以出现一个右括号
                ++balance;
            else {
                --balance;
                if (balance < 0)
                    return false;
            }
        return balance == 0;
    }
    void generate_all(string& current, int n, vector<string>& result) {
        if (n == current.size()) {
            if (valid(current))
                // 生成的括号有效，则压入结果容器中
                result.push_back(current);
            return;
        }
        current += '(';
        generate_all(current, n, result);
        current.pop_back();
        current += ')';
        generate_all(current, n, result);
        current.pop_back();
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result; // 记录结果
        string current; // 记录字符串数组中的每个字符串
        generate_all(current, n * 2, result);
        return result;
    }
};

/* 题解——回溯法 */
class Solution {
    // open 代表左括号，close 代表右括号
    void backtrack(vector<string>& ans, string& cur, int open, int close, int n) {
        if (cur.size() == n * 2) {
            ans.push_back(cur);
            return;
        }
        if (open < n) {
            cur.push_back('(');
            backtrack(ans, cur, open + 1, close, n);
            cur.pop_back();
        }
        if (close < open) {
            cur.push_back(')');
            backtrack(ans, cur, open, close + 1, n);
            cur.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result; // 记录结果
        string current; // 记录字符串数组中的每个字符串
        backtrack(result, current, 0, 0, n);
        return result;
    }
};

/* 题解——按括号序列的长度递归 */
class Solution {
    shared_ptr<vector<string>> cache[100] = {nullptr};
public:
    shared_ptr<vector<string>> generate(int n) {
        if (cache[n] != nullptr)
            return cache[n];
        if (n == 0) {
            cache[0] = shared_ptr<vector<string>>(new vector<string>{""});
        } else {
            auto result = shared_ptr<vector<string>>(new vector<string>);
            for (int i = 0; i != n; ++i) {
                auto lefts = generate(i);
                auto rights = generate(n - i - 1);
                for (const string& left : *lefts)
                    for (const string& right : *rights)
                        result -> push_back("(" + left + ")" + right);
            }
            cache[n] = result;
        }
        return cache[n];
    }
    vector<string> generateParenthesis(int n) {
        return *generate(n);
    }
};


/*-------------------------------
| 题目21：乘积最大子数组
| 给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
-------------------------------*/
/* 动态规划 */
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxF = nums[0], minF = nums[0], ans = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            int mx = maxF, mn = minF; // mx 记录正的最大值，mn 记录负的最小值
            maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
            minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
            ans = max(maxF, ans);
        }
        return ans;
    }
};


/*-------------------------------
| 题目22：x 的平方根
| 在不使用 math 库中的 sqrt() 函数的情况下，实现 int sqrt(int x) 函数。
| 计算并返回 x 的平方根，其中 x 是非负整数。
| 由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。
-------------------------------*/
/* 袖珍计算器算法 */
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;

        // 把 √x 转化为 x 的 1/2 次方的表现形式，再用换底公式换为以 e 为底的对数即可
        int ans = exp(0.5 * log(x));

        // 由于计算机计算浮点数不精确，因此需要判断哪个才是正确的
        return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
    }
};

/* 二分查找 */
class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x, ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if ((long long)mid * mid < x) {
                ans = mid;
                l = mid + 1; // 小了左边 +1
            } else if((long long)mid * mid > x) {
                r = mid - 1; // 小了右边 -1
            } else {
                ans = mid;
                break; // 恰好相等的时候就不用再算了
            }
        }
        return ans;
    }
};

/* 牛顿迭代 */
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;

        // 从 x 开始，是为了防止迭代到 -√x
        double C = x, x0 = x;
        while (true) {
            double xi = 0.5 * (x0 + C / x0);
            if (fabs(x0 - xi) < 1e-7) break;
            x0 = xi;
        }
        return int(x0);
    }
};

/*-------------------------------
| 题目23：找出第 K 大的异或坐标值
| 给你一个二维矩阵 matrix 和一个整数 k ，矩阵大小为 m x n 由非负整数组成。
| 矩阵中坐标 (a, b) 的值可由对所有满足 0 <= i <= a < m 且 0 <= j <= b < n 的元素 matrix[i][j]（下标从 0 开始计数）执行异或运算得到。
| 请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。
-------------------------------*/
/* 前缀和+快排 */
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> s(m+1, vector<int>(n+1));
        vector<int> ans;//用于存放结果，动态初始化
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                s[i+1][j+1] = s[i][j]^s[i][j+1]^s[i+1][j]^matrix[i][j];
                ans.push_back(s[i+1][j+1]);//直接往里压就行
            }
        }
        //STL内置的快速排序
        nth_element(ans.begin(), ans.begin() + k - 1, ans.end(), greater<int>());
        return ans[k-1];
    }
};

/*-------------------------------
| 题目24：前K个高频单词
| 给一非空的单词列表，返回前 k 个出现次数最多的单词。
| 返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率，按字母顺序排序。
-------------------------------*/
/* 哈希表+优先队列 */
class Solution {
    struct cmp{
        //重载运算符，从小到大排序
        bool operator()(pair<string,int> a,pair<string,int> b){
            return a.second == b.second ? a.first > b.first : a.second < b.second;
        }
    };
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> cnt;//哈希表
        for (auto word : words) {
            cnt[word]++;//从字符数组中读取字符串进哈希表中
        }

        //优先队列，构建大根堆
        priority_queue<pair<string, int>, vector<pair<string, int>>, cmp> que;
        for (auto it : cnt) {
            //原地构造一个元素并插入序列
            que.emplace(it);
        }

        //结果向量
        vector<string> ret(k);
        for (int i = 0; i < k; i++) {
            ret[i] = que.top().first;
            que.pop();
        }
        return ret;
    }
};

/*-------------------------------
| 题目25：奇怪的打印机
| 有台奇怪的打印机有以下两个特殊要求：
|   ·打印机每次只能打印由 同一个字符 组成的序列。
|   ·每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。
| 给你一个字符串 s ，你的任务是计算这个打印机打印它需要的最少打印次数。
-------------------------------*/
/* 动态规划 */
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.length();

        //f[i][j]表示从第i个字符到第j个字符需要的最少打印次数
        vector<vector<int>> f(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--) {
            f[i][i] = 1;
            for (int j = i + 1; j < n; j++) {
                //区间两端的元素一样时，f[i][j] = f[i][j - 1]
                if (s[i] == s[j]) {
                    f[i][j] = f[i][j - 1];
                } else {
                    int minn = INT_MAX;
                    for (int k = i; k < j; k++) {
                        minn = min(minn, f[i][k] + f[k + 1][j]);
                    }
                    f[i][j] = minn;
                }
            }
        }
        return f[0][n - 1];
    }
};