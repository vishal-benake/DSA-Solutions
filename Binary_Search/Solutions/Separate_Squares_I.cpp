class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        
        double totalArea = 0.0;
        double minY = 1e18, maxY = -1e18;

        // Step 1: Calculate total area and vertical bounds
        for (auto &sq : squares) {
            double y = sq[1];
            double side = sq[2];
            totalArea += side * side;
            minY = min(minY, y);
            maxY = max(maxY, y + side);
        }

        double target = totalArea / 2.0;

        // Function to calculate area below y = mid
        auto areaBelow = [&](double mid) {
            double area = 0.0;
            for (auto &sq : squares) {
                double y = sq[1];
                double side = sq[2];
                double bottom = y;
                double top = y + side;

                // Square completely below the line
                if (top <= mid) {
                    area += side * side;
                }
                // Square partially below the line
                else if (bottom < mid) {
                    area += side * (mid - bottom);
                }
                // else: square completely above → contributes 0
            }
            return area;
        };

        // Step 2: Binary search on y-coordinate
        double low = minY, high = maxY;

        // 60 iterations give enough precision for double
        for (int i = 0; i < 60; i++) {
            double mid = (low + high) / 2.0;
            if (areaBelow(mid) < target)
                low = mid;
            else
                high = mid;
        }

        return low;
    }
};