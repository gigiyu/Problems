/****************************************************************************
44. Connected Components in an undirected graph
Given an undirected graph, find the number of connected components.
Union Find
*/
class Graph {
public:
    int connectedComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for(int i = 0; i < edges.size(); i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        vector<int> visited(n, 0);
        int ret = 0;
        for(int i = 0; i < n; i++) {
            if (visited[i] == 0){
                dfs(n, graph, visited, i);
                ret++;
            }
        }
        return ret;
    }
    void dfs(int n, vector<vector<int>>& graph, vector<int>& visited, int idx) {
        if (visited[idx]) return;
        visited[idx] = 1;
        for(int i = 0; i < graph[idx].size(); i++) {
            dfs(n, graph, visited, graph[idx][i]);
        }
    }
    int unionFindSets(int n, vector<vector<int>>& edges) {
        vector<int> p(n, -1);
        for(auto e : edges) {
            int x = findRoot(p, e[0]);
            int y = findRoot(p, e[1]);
            if (x == y) continue;
            p[y] = x;
            showV(p);
        }
        int ans = 0;
        for(auto n : p) if (n == -1) ans++;
        return ans;
    }
    int findRoot(vector<int>& p, int i) {
        return p[i] < 0 ? i : (i = findRoot(p, p[i]));
    }
};

/****************************************************************************
43. Function Time
*/
struct FunInfo {
    string name;
    string status;
    int time;
    FunInfo(string n, string s, int t) : name(n), status(s), time(t) {}
};

class FuntionTime {
public:
    // "fun1:start:0"
    vector<int> funcTime(vector<string>& input, string jobName) {
        if (input.empty() || jobName.empty()) throw invalid_argument("Error");
        vector<int> ret(2, 0);
        vector<FunInfo> funLists = deserilizeFun(input);
        stack<FunInfo> st;
        int subFunTime = 0;
        for(auto f : funLists) {
            cout << f.name << " " << f.status << " " << f.time << endl;
            if (st.empty()) {
                if (f.name == jobName && f.status == "start") st.push(f);
            } else {
                if (f.name == jobName) {
                    FunInfo top = st.top(); st.pop();
                    ret[0] += f.time - top.time;
                    ret[1] += ret[0] - subFunTime;
                    subFunTime = 0;
                }else {
                    if (f.status == "start") st.push(f);
                    else {
                        FunInfo top = st.top(); st.pop();
                        subFunTime += f.time - top.time;
                    }
                }
            }
        }
        return ret;
    }
    vector<FunInfo> deserilizeFun(vector<string>& input) {
        vector<FunInfo> ret;
        for(auto s : input) {
            size_t idx1 = s.find(':');
            size_t idx2 = s.find(':', idx1 + 1);
            FunInfo f(s.substr(0, idx1), s.substr(idx1+1, idx2 - idx1 - 1), stoi(s.substr(idx2 + 1)));
            ret.push_back(f);
        }
        return ret;
    }
};
/****************************************************************************
42. Array Equal Partition
Given an array with random number, given a parameterk, determine whether it is possible to divide the array into k sub arrays,
whose sums are equivalent to each other.
[4,3,2,3,5,2,1], k=4 -> (5)(1,4)(2,3)(2,3)
[2,1,6,3,7,-1]
*/
class Divisible {
public:
    //[4,3,2,3,5,2,1], k=4 -> (5)(1,4)(2,3)(2,3)
    // {-1, 1, 10, -10, 100, -100} k = 3;
    bool divisible(const vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k) return false;
        int target = total / k;
        vector<int> mark(nums.size(), 0);
        vector<vector<int>> ret;
        vector<int> path;
        for(int i = 0; i < nums.size(); i++) {
             if (mark[i] == 0) {
                if (dfs(nums, k, target, ret, path, 0, mark, i)) {
                    ret.push_back(path);
                    path.clear();
                }
             }
        }
        show(ret);
        for(auto n : mark) if (n == 0) return false;
        return ret.size() == k;
    }
    bool dfs(const vector<int>& nums, int k, int target, vector<vector<int>>& ret, vector<int>& path, int sum, vector<int>& mark, int idx) {
        if (sum == target && path.size() > 0){
            return true;
        }
        // if (sum > target) return false; //  no need this. eg. target=0 [1,-1,2,-2] k = 2;
        for(int i = idx; i < nums.size(); i++) {
            if (mark[i] == 0) {
                mark[i] = 1;
                path.push_back(nums[i]);
                if (dfs(nums, k, target, ret, path, sum + nums[i], mark, i)) {
                    return true;
                }
                mark[i] = 0;
                path.pop_back();
            }
        }
        return false;
    }
};
class Divisible {
public:
    //[4,3,2,3,5,2,1], k=4 -> (5)(1,4)(2,3)(2,3)
    // only calculate number of subset.
    bool divisible(const vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k) return false;
        int target = total / k;
        vector<int> mark(nums.size(), 0);
        int ret = 0;
        for(int i = 0; i < nums.size(); i++) {
             if (mark[i] == 0) {
                if (dfs(nums, target, 0, mark, 0))  ret++;
                if (target == 0 && ret + 1 == k) {
                    int tmp = 0;
                    for(int i = 0; i < nums.size(); i++){
                        if (mark[i] == 0) tmp += nums[i];
                    }
                    if (tmp == target) return true;
                }
             }
        }
        for(auto n : mark) if (n == 0) return false;
        return ret == k;
    }
    bool dfs(const vector<int>& nums, int target, int sum, vector<int>& mark, int cnt) {
        if (sum == target && cnt > 0) return true;
        //if (sum > target) return false;
        for(int i = 0; i < nums.size(); i++) {
            if (mark[i] == 0) {
                mark[i] = 1;
                if (dfs(nums, target, sum + nums[i], mark, cnt + 1)) return true;
                mark[i] = 0;
            }
        }
        return false;
    }
};

/****************************************************************************
41. Intersection and Union of sorted lists
A={2,4,6,8,10}, B={1,2,3,4,5} A Union B={1,2,3,4,5,6,8,10};  A Intersection B={2,4}
Follow up:
    - what if input may have duplicates, but the result of the intersection or union must not
    - Multiple lists
    - multiple CPU cores? concurrency? (Why your solution works.)
    - When does it make sense to do this sort of optimization? Does it depend on length of the lists, number of processor cores?  
*/
class IntersectionAndUnion {
public:
    vector<int> Union(const vector<int>& a, const vector<int>& b) {
        set<int> s;
        vector<int> ret;
        for(auto n : a) s.insert(n);
        for(auto n : b) s.insert(n);
        for(auto it: s) ret.push_back(it);
        return ret;
    }
    vector<int> Union_MultipleLists(const vector<vector<int>>& lists) {
        set<int> s;
        vector<int> ret;
        for(auto num : lists) {
            for(auto n : num) s.insert(n);
        }
        for(auto it: s) ret.push_back(it);
        return ret;

    }
    vector<int> Intersection_noduplicate(const vector<int>& a, const vector<int>& b) {
        vector<int> ret;
        unordered_map<int, int> m;
        for(auto n : a) m[n]++;
        for(auto n : b){
            if (m.find(n) != m.end()) {
                ret.push_back(n);
                m.erase(n);
            }
        }
        return ret;
    }
    vector<int> Intersection_withDuplicates(const vector<int>& a, const vector<int>& b) {
        vector<int> ret;
        unordered_map<int, int> m;
        for(auto n : a) m[n]++;
        for(auto n : b){
            if (!ret.empty() && n == ret.back()) continue;
            if (m.find(n) != m.end()) {
                ret.push_back(n);
                m[n]--;
                if(m[n] == 0) m.erase(n);
            }
        }
        return ret;
    }
    vector<int> Intersection_MultipleLists(const vector<vector<int>>& lists) {
        vector<int> ret;
        if (lists.empty()) return ret;
        if (lists.size() < 2) return lists[0];
        ret = Intersection_noduplicate(lists[0], lists[1]);
        for(int i = 2; i < lists.size(); i++) {
            if (ret.empty() || lists[i].empty()) return {};
            ret = Intersection_noduplicate(ret, lists[i]);
        }
        return ret;
    }
    // parallelize
    vector<int> Union_Parallelize(const vector<int>& a, const vector<int>& b) {
        vector<int> a1(a.begin(), a.begin() + a.size() / 2); // divide into two part.
        vector<int> a2(a.begin() + a.size() / 2, a.end());
        vector<int> b1(b.begin(), b.begin() + b.size() / 2);
        vector<int> b2(b.begin() + b.size() / 2, b.end());
        // &IntersectionAndUnion::Union,
        // this
        auto tmp1 = std::async(&IntersectionAndUnion::Union, this, ref(a1), ref(b1));
        auto tmp2 = std::async(&IntersectionAndUnion::Union, this, ref(a2), ref(b2));

        return Union(tmp1.get(), tmp2.get());

    }
};
