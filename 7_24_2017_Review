/****************************************************************************
45. Permutations    //TOCHECK
[1,2,3]->{[1,2,3],[1,3,2],[2,3,1],[2,1,3],[3,1,2],[]3,2,1}
["abc"]->{"abc","acb","bac","bca","cab","cba"}
Follow up:
    - utilize multithreading
    - how to avoid using a ridiculously large amount of memory?
*/
template<typename T>
class Solution {
public:
    vector<vector<T>> generatePermutation(vector<T> values) {
        ret.clear();
        if (values.size() == 0) return ret;
        vector<T> path;
        vector<bool> mark(values.size(), false);
        dfs(values, path, mark);
        return ret;
    }
private:
    vector<vector<T>> ret;
    void dfs(const vector<T>& values, vector<T>& path, vector<bool>& mark) {
        if (path.size() == values.size()) {
            ret.push_back(path);
            return;
        }
        for(int i = 0; i < values.size(); i++) {
            if (mark[i] == true) continue;
            path.push_back(values[i]);
            mark[i] = true;
            dfs(values, path, mark);
            path.pop_back();
            mark[i] = false;
        }
    }
};

/****************************************************************************
52. Max Stack   //TOCHECK
Follow up 
    - What are the performance characteristics(space required, speed of the operations compared to O(1) for normal stacks)?
    - How do you handle duplicate elements?
    - What needs to be done to make this structure thread-safe?
*/
template<typename T>
class MaxStack {
public:
    void push(T value) {
        st.push(value);
        if (maxST.empty() || value >= maxST.top()) maxST.push(value);
    }
    T top() {
        return st.top();
    }
    void pop() {
        T ret = st.top();
        st.pop();
        if (!maxST.empty() && ret == maxST.top()) maxST.pop();
    }
    T topMax() {
        return maxST.top();
    }
private:
    stack<T> st;
    stack<T> maxST;
};

/****************************************************************************
35. Multi-dimensional Sum  //TODO
1. Sum of elements of a k-dimensional array
    example: Given object m that holds a 2*2*3 array
    a = [[[3,2,2],[1,5,0]],[[2,0,1],[1,1,-2]]
    arraySum(m, [2,2,3]) = (3+2+2+1+5+0+2+0+1+1+1+-2) = 16;
2. findMin that given an instance of the function class and the range of grid search. 
    return the minimum of the function over that range.
*/
class Solution {
public:
    int arraySum(MultiDimArray m, vector<int>& dimensions) {
        int ret = 0;
        int n = dimensions.size();
        vector<int> idx(n, 0);
        // 000,001,001,010,011,012,100,101,102,110,111,112
        
    }
};

/****************************************************************************
36. Ponds and Islands  //TOCHECK
2d integer array where 1's signify land and 0's signify water
output: the number of "island" in the array where an island is defined as a continuous block of 1's(LRUD)
Follow up:
    - Space and time complexity
    - if you had an array of elevations, how would you count the number of "basins"?
*/
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int ret = 0;
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    ret++;
                }
            }
        }
        return ret;
    }
    vector<vector<int>> d = {{-1,0},{1,0},{0,-1},{0,1}};
    void dfs(vector<vector<char>>& maps, int i, int j ) {
        if (i<0 || i >= maps.size() || j < 0 || j >= maps[0].size() || maps[i][j] == '0') return;
        maps[i][j] = '0';
        for(int k = 0; k < 4; k++) {
            dfs(maps, i + d[k][0], j + d[k][1]);
        }
    }
};
/****************************************************************************
37. Message burst processor //TODO
A burst of message is defined as asequence of messages which are surrounded by given "quiet periods"(with no incoming message)
*/
class MessageBurstProcessor {
public:
    MessageBurstProcessor(long quietPeriod) {
    }
//    Identify the last message in each burst.
//    Called in multiple threads concurrently.
//    return true if the message is the last message in a burst
    bool process(Object message) {
        
    }
};


/****************************************************************************
80. K closest values in BST
Solution: 1.inorder get nums; 2.search k closest{left, idx, right} keep them in [0, nums.size() - 1]
Follow up:
    - Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?
*/
class Solution80 {
public:
    // 1. find one closet number in BST
    int closestValue(TreeNode* root, double target) {
        int ret = root->val;
        {   // iterate
            while (root) {
                if (abs(root->val - target)<abs(ret - target)) ret = root->val;
                root = target < root->val ? root->left : root->right;
            }
            return ret;
        }
        {   // recursive
            TreeNode* next = target < root->val ? root->left : root->right;
            if (next == nullptr) return ret;
            int subTree = closestValue(next, target);
            return abs(ret - target) < abs(subTree - target) ? ret : subTree;
        }

    }
    // 2. find K
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        //Solution 1:O(n) runtime (where n = total nodes) iterate
        {
            vector<int> res, v;
            inorder1(root, v);   // get sorted tree values
            int idx = 0;
            double diff = numeric_limits<double>::max();    // get minGap
            for (int i = 0; i < v.size(); ++i) {
                if (diff >= abs(target - v[i])) {
                    diff = abs(target - v[i]);
                    idx = i;
                }
            }
            int left = idx - 1, right = idx + 1; // keep {left, idx, right} in[0, v.size() - 1];
            for (int i = 0; i < k; ++i) {
                res.push_back(v[idx]);
                if (left >= 0 && right < v.size()) {
                    if (abs(v[left] - target) > abs(v[right] - target)) {
                        idx = right;
                        ++right;
                    } else {
                        idx = left;
                        --left;
                    }
                } else if (left >= 0) {
                    idx = left;
                    --left;
                } else if (right < v.size()) {
                    idx = right;
                    ++right;
                }
            }
            return res;
        }
        // Solution 2: generate KClosest when inorder.
        {
            vector<int> res;
            inorder2(root, target, k, res);
            return res;
        }
        // Solution 3: priority_queue<pair<double, int>> pq;
        {
            priority_queue<pair<double, int>> pq;   //pq(double, int)->(gap, root->val);
            inorder3(root, pq, target, k);
            vector<int> ret;
            while(!pq.empty()) {
                ret.push_back(pq.top().second);
                pq.pop();
            }
            return ret;
        }
        // Solution 3: two stack(pre, suc) O(k)
        {
            vector<int> res;
            stack<TreeNode*> pre, suc;
            while (root) {
                if (root->val <= target) {
                    pre.push(root);
                    root = root->right;
                } else {
                    suc.push(root);
                    root = root->left;
                }
            }
            while (k-- > 0) {
                if (suc.empty() || !pre.empty() && target - pre.top()->val < suc.top()->val - target) {
                    res.push_back(pre.top()->val);
                    getPredecessor(pre);
                } else {
                    res.push_back(suc.top()->val);
                    getSuccessor(suc);
                }
            }
            return res;
        }
    }
    void getPredecessor(stack<TreeNode*> &pre) {
        TreeNode *t = pre.top(); pre.pop();
        if (t->left) {
            pre.push(t->left);
            while (pre.top()->right) pre.push(pre.top()->right);
        }
    }
    void getSuccessor(stack<TreeNode*> &suc) {
        TreeNode *t = suc.top(); suc.pop();
        if (t->right) {
            suc.push(t->right);
            while (suc.top()->left) suc.push(suc.top()->left);
        }
    }
    void inorder3(TreeNode* root, priority_queue<pair<double, int>>& pq, double target, int k) {
        if (!root) return;
        inorder3(root->left, pq, target, k);
        pq.push({abs(root->val - target), root->val});
        if(pq.size() > k) pq.pop();
        inorder3(root->right, pq, target, k);
    }
    void inorder2(TreeNode *root, double target, int k, vector<int> &res) {
        if (!root) return;
        inorder2(root->left, target, k, res);
        if (res.size() < k) res.push_back(root->val);
        else if (abs(root->val - target) < abs(res[0] - target)) {
            res.erase(res.begin());
            res.push_back(root->val);
        } else return;
        inorder2(root->right, target, k, res);
    }
    void inorder1(TreeNode* root, vector<int>& nums) {
        if (root == nullptr) return;
        inorder1(root->left, nums);
        nums.push_back(root->val);
        inorder1(root->right, nums);
    }
};
/****************************************************************************
81. K smallest pairs
Given two sorted lists of postive integers, find out the first k pairs with the smallest product.
Each pair contains one number from each lists.
nums1=[1,2,5,9], nums2=[1,3,4,6],k=5 -> [1,1],[2,1],[1,3],[1,4],[5,1]
*/
typedef pair<int, pair<int,int>> PIP;
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int> nums1, vector<int> nums2, int k) {
        vector<vector<int>> ret;
        if (nums1.size() == 0 || nums2.size() == 0) return ret;
        priority_queue<PIP> pq;
        for(int i = 0; i < nums1.size(); i++) {
            for(int j = 0; j < nums2.size(); j++) {
                int product = nums1[i] * nums2[j];
                pq.push({product, {i, j}});
                if (pq.size() > k) pq.pop();
            }
        }
        while(!pq.empty()) {
            PII cur = pq.top().second;
            pq.pop();
            ret.push_back({nums1[cur.first], nums2[cur.second]});
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

