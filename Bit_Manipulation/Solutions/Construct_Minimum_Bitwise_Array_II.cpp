class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;

        for (int N : nums) {

            // If N is even, it's impossible
            // because (x | (x + 1)) is always odd
            if (N % 2 == 0) {
                ans.push_back(-1);
                continue;
            }

            int res = -1;

            // To minimize x, unset the MOST SIGNIFICANT set bit
            for (int bit = 30; bit >= 0; bit--) {
                if (N & (1 << bit)) {

                    // Unset this bit
                    int x = N ^ (1 << bit);

                    // Check if condition is satisfied
                    if ((x | (x + 1)) == N) {
                        res = x;
                        break;  // first valid is minimum
                    }
                }
            }

            ans.push_back(res);
        }

        return ans;
    }
};