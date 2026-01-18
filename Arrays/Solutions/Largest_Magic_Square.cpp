#include <vector>
using namespace std;

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // rowPrefix[r][c] = sum of grid[r][0..c-1]
        vector<vector<int>> rowPrefix(m, vector<int>(n + 1, 0));

        // colPrefix[r][c] = sum of grid[0..r-1][c]
        vector<vector<int>> colPrefix(m + 1, vector<int>(n, 0));

        // Build prefix sums
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowPrefix[i][j + 1] = rowPrefix[i][j] + grid[i][j];
                colPrefix[i + 1][j] = colPrefix[i][j] + grid[i][j];
            }
        }

        // Lambda for row sum in O(1)
        auto rowSum = [&](int r, int c1, int c2) {
            return rowPrefix[r][c2] - rowPrefix[r][c1];
        };

        // Lambda for column sum in O(1)
        auto colSum = [&](int c, int r1, int r2) {
            return colPrefix[r2][c] - colPrefix[r1][c];
        };

        int maxK = min(m, n);

        // Try squares from largest to smallest
        for (int k = maxK; k >= 2; k--) {
            for (int r = 0; r + k <= m; r++) {
                for (int c = 0; c + k <= n; c++) {

                    int target = rowSum(r, c, c + k);
                    bool valid = true;

                    // Check rows
                    for (int i = r; i < r + k; i++) {
                        if (rowSum(i, c, c + k) != target) {
                            valid = false;
                            break;
                        }
                    }

                    if (!valid) continue;

                    // Check columns
                    for (int j = c; j < c + k; j++) {
                        if (colSum(j, r, r + k) != target) {
                            valid = false;
                            break;
                        }
                    }

                    if (!valid) continue;

                    // Main diagonal
                    int diag1 = 0, diag2 = 0;
                    for (int i = 0; i < k; i++) {
                        diag1 += grid[r + i][c + i];
                        diag2 += grid[r + i][c + k - 1 - i];
                    }

                    if (diag1 != target || diag2 != target)
                        continue;

                    return k;
                }
            }
        }

        return 1;
    }
};