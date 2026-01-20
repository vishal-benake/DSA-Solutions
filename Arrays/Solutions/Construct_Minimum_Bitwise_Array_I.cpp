class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;

        for (int num : nums) {
            int best = -1;

            // Try all possible x from 0 to num
            for (int x = 0; x <= num; x++) {
                // Check the required condition
                if ((x | (x + 1)) == num) {
                    best = x;   // first valid x is the minimum
                    break;
                }
            }

            ans.push_back(best);
        }

        return ans;
    }
};