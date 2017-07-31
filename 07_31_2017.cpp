/****************************************************************************
34. Triangle  
Follow up: 
    - find all triplets can form a triangle. O(nlogn) ???
    - find the number of triplets can form a triangle. O(n**2)
    - whether allowed to use one number more than once. 
*/
class Solution {
public:
    // 0. find any triplet compose one triangle
    vector<int> getTriangle_0(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); i++) {
            int j = i + 1, k = nums.size() - 1;
            while(j < k) {
                if (nums[i] + nums[j] > nums[k]) return {nums[i], nums[j], nums[k]};
                j++;
            }
        }
        return {};
    }
    // 1. O(nlogn) all triplets
    vector<vector<int>> getTriangle_1(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); i++) {
            int j = i + 1, k = nums.size() - 1;
            while(j < k) {
                if (nums[i] + nums[j] > nums[k]) {
                    ret.push_back({nums[i], nums[j], nums[k]});
                    return ret;
                }
                j++;
            }
        }
        return ret;
    }
    // 2. one number one time.
    //  the number of all triplets O(n**2) = O(n) * (O(n) + O(n)) = i * (j + k);
    int getTriangle_2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ret = 0, n = nums.size();
        for(int i = 0; i < n - 2; i++) {
            int k = i + 2;
            for(int j = i + 1; j < n; j++) {
                while(k < n && nums[i] + nums[j] > nums[k]) k++;
                cout << i << " " << j << " " << k << endl;
                for(int p = j + 1; p < k; p++) cout << "    " << nums[i] << " " << nums[j] << " " << nums[p] << endl;
                ret += k - j - 1;
            }
        }
        return ret;
    }
    // 3. allowed to use one number more than once. the number of all triplets
    int getTriangle_3(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ret = 0, n = nums.size();
        for(int i = 0; i < n; i++) {
            int k = i;
            for(int j = i; j < n; j++) {
                while(k < n && nums[i] + nums[j] > nums[k]) k++;
                cout << i << " " << j << " " << k << endl;
                for(int p = j; p < k; p++) cout << "    " <<  nums[i] << " " << nums[j] << " " << nums[p] << endl;
                ret += k - j;
            }
        }
        return ret;
    }
};

int triangleNumber(vector<int>& nums) {
    // o(N^2)
    int res = 0, n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = n - 1; i >= 2; --i) {
        int left = 0, right = i - 1;
        while (left < right) {
            if (nums[left] + nums[right] > nums[i]) {
                res += right - left;
                --right;
            } else {
                ++left;
            }
        }
    }
    return res;
}
