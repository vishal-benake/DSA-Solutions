class Solution:
    def rotate(self, nums: list[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        if n == 0: 
            return
        
        # Ensure k is within bounds of the array length
        k = k % n

        # Right Rotation: Take last k elements and put them at the front
        # nums[-k:] -> The 'tail' that moves to front
        # nums[:-k] -> The 'head' that shifts to the right
        nums[:] = nums[-k:] + nums[:-k]
