#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int totalTime = 0;

        // Traverse points one by one
        for (int i = 1; i < points.size(); i++) {

            // Current point
            int x1 = points[i - 1][0];
            int y1 = points[i - 1][1];

            // Next point
            int x2 = points[i][0];
            int y2 = points[i][1];

            // Distance needed in x and y directions
            int dx = abs(x1 - x2);
            int dy = abs(y1 - y2);

            /*
             We can move diagonally, horizontally, or vertically.
             One diagonal move reduces both dx and dy by 1.

             So the minimum time required is:
             max(dx, dy)
            */
            totalTime += max(dx, dy);
        }

        return totalTime;
    }
};
