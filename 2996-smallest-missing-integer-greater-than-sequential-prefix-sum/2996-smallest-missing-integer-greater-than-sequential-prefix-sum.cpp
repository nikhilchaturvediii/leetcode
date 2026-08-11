class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: find length of sequential prefix
        int i = 1;
        while (i < n && nums[i] == nums[i - 1] + 1) {
            i++;
        }
        
        // sum of the sequential prefix = candidate starting point
        long long candidate = 0;
        for (int j = 0; j < i; j++) {
            candidate += nums[j];
        }
        
        // Step 2: put all elements into a set for quick lookup
        unordered_set<int> present(nums.begin(), nums.end());
        
        // Step 3: find smallest missing integer >= candidate
        while (present.count((int)candidate)) {
            candidate++;
        }
        
        return (int)candidate;
    }
};