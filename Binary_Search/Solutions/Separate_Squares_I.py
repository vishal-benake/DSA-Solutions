class Solution:
    def separateSquares(self, squares: List[List[int]]) -> float:
        
        # Step 1: total area of all squares
        total_area = 0
        min_y = float('inf')
        max_y = float('-inf')
        
        for x, y, side in squares:
            total_area += side * side
            min_y = min(min_y, y)
            max_y = max(max_y, y + side)
        
        target = total_area / 2
        
        # Function to compute area below horizontal line y = k
        def area_below(k):
            area = 0
            for x, y, side in squares:
                bottom = y
                top = y + side
                
                if top <= k:
                    area += side * side
                elif bottom < k < top:
                    area += side * (k - bottom)
            return area
        
        # Step 2: Binary search on y-coordinate
        low, high = min_y, max_y
        
        for _ in range(60):  # enough for precision
            mid = (low + high) / 2
            if area_below(mid) < target:
                low = mid
            else:
                high = mid
        
        return low