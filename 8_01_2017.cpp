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
