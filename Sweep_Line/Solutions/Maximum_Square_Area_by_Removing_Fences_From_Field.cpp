class Solution {
public:
    int maxSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        const long long MOD = 1e9 + 7;

        // Add boundary fences
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        // Sort fence positions
        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        // Store all possible horizontal distances
        unordered_set<long long> horizontalDistances;

        int H = hFences.size();
        for (int i = 0; i < H; i++) {
            for (int j = i + 1; j < H; j++) {
                horizontalDistances.insert(
                    (long long)hFences[j] - hFences[i]
                );
            }
        }

        long long maxSide = 0;

        // Check vertical distances against horizontal ones
        int V = vFences.size();
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                long long width = (long long)vFences[j] - vFences[i];
                if (horizontalDistances.count(width)) {
                    maxSide = max(maxSide, width);
                }
            }
        }

        if (maxSide == 0) return -1;

        return (maxSide % MOD) * (maxSide % MOD) % MOD;
    }
};
