class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        int MOD = 1e9 + 7;
        int MAX_VAL = 100000;
        int n = nums.size();

        vector<long long> prefix(MAX_VAL + 1, 0);
        vector<long long> suffix(MAX_VAL + 1, 0);

        long long total = 0;

        for (int num: nums){
            suffix[num]++;
        }

        for(int j = 0; j < n; j++){
            int val = nums[j];
            int target = 2 * val;

            suffix[val]--;

            if(target <= MAX_VAL){
                total = (total + prefix[target] * suffix[target]) % MOD;
            }

            prefix[val]++;
        }
        return total;
    }
};