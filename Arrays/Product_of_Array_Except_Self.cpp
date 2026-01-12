class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        // output[i] will store product of all elements to the LEFT of i
        vector<int> output(n, 1);

        // First pass: compute prefix products
        for (int i = 1; i < n; i++) {
            output[i] = output[i - 1] * nums[i - 1];
        }

        // right stores product of all elements to the RIGHT of i
        int right = 1;

        // Second pass: multiply suffix products
        for (int i = n - 1; i >= 0; i--) {
            output[i] *= right;
            right *= nums[i];
        }

        return output;
    }
};
