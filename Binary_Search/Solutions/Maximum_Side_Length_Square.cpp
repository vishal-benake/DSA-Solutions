class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size();
        int n = mat[0].size();

        /*
         * prefix[i][j] stores sum of submatrix
         * from (0,0) to (i-1,j-1)
         */
        vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));

        // Build 2D prefix sum
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix[i + 1][j + 1] =
                    mat[i][j]
                    + prefix[i][j + 1]
                    + prefix[i + 1][j]
                    - prefix[i][j];
            }
        }

        // Function to check if a k x k square exists with sum <= threshold
        auto isValid = [&](int k) {
            for (int i = 0; i + k <= m; i++) {
                for (int j = 0; j + k <= n; j++) {
                    int sum =
                        prefix[i + k][j + k]
                        - prefix[i][j + k]
                        - prefix[i + k][j]
                        + prefix[i][j];
                    if (sum <= threshold)
                        return true;
                }
            }
            return false;
        };

        // Binary search on side length
        int left = 1, right = min(m, n);
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (isValid(mid)) {
                ans = mid;        // mid is valid
                left = mid + 1;   // try larger square
            } else {
                right = mid - 1;  // reduce size
            }
        }

        return ans;
    }
};