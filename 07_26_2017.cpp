/****************************************************************************
16. Isomorphic Strings (LeetCode205)
"egg", "add"-> true; "foo", "bar" -> false;
Follow up:
    - what if there were three words? 
    - what if there were n words?
    - What is the execution time complexity? Can you make it faster?
*/
class Solution {
public:
    //vector<string> words = {"foo", "bar", "baz", "qux", "oof", "aaa", "aah", "abb", "aba"};
    // output = {{aaa}, {aba}, {abb,foo},{bar,qux,baz},{oof,aah}}
    vector<vector<string>> isIsomorphic_N(vector<string>& words) {
        vector<vector<string>> ret;
        if (words.size() == 0) return ret;
        unordered_map<string, vector<string>> m;    //<"format", word>
        for(int i = 0; i < words.size(); i++) {
            string f = formatting(words[i]);
            m[f].push_back(words[i]);
        }
        for(auto it = m.begin(); it != m.end(); it++) {
            ret.push_back(it->second);
        }
        return ret;
    }
    string formatting(const string& s) {
        string ret;
        unordered_map<char, char> m;
        char c = 'a';
        for(int i = 0; i < s.size(); i++) {
            if (m.find(s[i]) == m.end()) {
                m[s[i]] = c++;
            }
            ret += m[s[i]];
        }
        return ret;
    }
};

/****************************************************************************
23. Data struct with O(1) add, remove, randomremove
Follow up:
    - use Set, Insert, Remove, GetRandom O(1)   //TODO
    - add(T val), remove(T val), T removeRandomeElement all O(1) + template   //TODO
    - TODO
duplicated allowed
*/
template<typename T>
class RandomizedCollection {
public:
    bool add(T element) {
        if (m.find(element) != m.end()) return false;
        m[element] = v.size();
        v.push_back(element);
        return true;
    }
    bool remove(T element) {
        if (m.find(element) == m.end()) return false;
        int idx1 = m[element];
        int idx2 = v.size() - 1;
        removeHelper(idx1, idx2);
        return true;
    }
    T removeRandomElement() {
        int idx1 = rand() % v.size();
        T ret = v[idx1];
        int idx2 = v.size() - 1;
        removeHelper(idx1, idx2);
        return ret;
    }
private:
    unordered_map<T, int> m;
    vector<T> v;
    void removeHelper(int idx1, int idx2) {
        m[v[idx2]] = idx1;
        m.erase(v[idx1]);
        swap(v[idx1], v[idx2]);
        v.pop_back();
    }
};
