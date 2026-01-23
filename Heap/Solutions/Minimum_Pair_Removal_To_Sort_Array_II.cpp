#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<long long>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        // Check if already non-decreasing
        bool sorted = true;
        for (int i = 0; i + 1 < n; i++) {
            if (nums[i] > nums[i + 1]) {
                sorted = false;
                break;
            }
        }
        if (sorted) return 0;

        vector<bool> removed(n, false);
        vector<int> prv(n), nxt(n);

        for (int i = 0; i < n; i++) {
            prv[i] = i - 1;
            nxt[i] = (i + 1 < n ? i + 1 : -1);
        }

        // Min-heap of (sum, left_index)
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<>> pq;

        for (int i = 0; i + 1 < n; i++) {
            pq.push({nums[i] + nums[i + 1], i});
        }

        // Count adjacent violations
        int bad = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (nums[i] > nums[i + 1]) bad++;
        }

        int ops = 0;

        while (bad > 0) {
            auto [sum, i] = pq.top();
            pq.pop();

            if (removed[i] || nxt[i] == -1) continue;

            int j = nxt[i];
            if (removed[j] || nums[i] + nums[j] != sum) continue;

            int pi = prv[i];
            int nj = nxt[j];

            // Remove old violations
            if (pi != -1 && nums[pi] > nums[i]) bad--;
            if (nums[i] > nums[j]) bad--;
            if (nj != -1 && nums[j] > nums[nj]) bad--;

            // Merge
            nums[i] = sum;
            removed[j] = true;

            nxt[i] = nj;
            if (nj != -1) prv[nj] = i;

            // Add new violations
            if (pi != -1 && nums[pi] > nums[i]) bad++;
            if (nj != -1 && nums[i] > nums[nj]) bad++;

            // Push updated sums
            if (pi != -1) pq.push({nums[pi] + nums[i], pi});
            if (nj != -1) pq.push({nums[i] + nums[nj], i});

            ops++;
        }

        return ops;
    }
};