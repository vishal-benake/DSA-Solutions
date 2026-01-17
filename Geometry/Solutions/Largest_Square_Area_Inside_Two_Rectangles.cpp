class Solution {
public:
    int largestSquareArea(vector<vector<int>>& bottomLeft,
                          vector<vector<int>>& topRight) {

        int n = bottomLeft.size();
        long long maxArea = 0;

        // Check every pair of rectangles
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                // Intersection bottom-left corner
                int x1 = max(bottomLeft[i][0], bottomLeft[j][0]);
                int y1 = max(bottomLeft[i][1], bottomLeft[j][1]);

                // Intersection top-right corner
                int x2 = min(topRight[i][0], topRight[j][0]);
                int y2 = min(topRight[i][1], topRight[j][1]);

                // If no overlap, skip
                if (x2 <= x1 || y2 <= y1)
                    continue;

                // Dimensions of intersection rectangle
                int width  = x2 - x1;
                int height = y2 - y1;

                // Largest square inside this intersection
                int side = min(width, height);

                // Update maximum area
                maxArea = max(maxArea, 1LL * side * side);
            }
        }

        return (int)maxArea;
    }
};