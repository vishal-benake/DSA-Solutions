class Solution {
public:
    // Helper function to find longest consecutive streak
    int longestConsecutiveStreak(vector<int>& bars) {
        sort(bars.begin(), bars.end());

        int maxStreak = 1;
        int currStreak = 1;

        for (int i = 1; i < bars.size(); i++) {
            // Check if bars are consecutive
            if (bars[i] == bars[i - 1] + 1) {
                currStreak++;
            } else {
                currStreak = 1;
            }
            maxStreak = max(maxStreak, currStreak);
        }

        return maxStreak;
    }

    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        // Longest consecutive removable bars
        int maxH = longestConsecutiveStreak(hBars) + 1;
        int maxV = longestConsecutiveStreak(vBars) + 1;

        // Largest possible square side
        int side = min(maxH, maxV);

        return side * side;
    }
};
