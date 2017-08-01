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
