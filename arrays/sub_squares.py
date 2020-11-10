class Solution:
    def countSquares(self, matrix: List[List[int]]) -> int:
        rowLen = len(matrix)
        colLen = len(matrix[0])
        memo = [[0]*colLen for _ in range(rowLen)]
        count = 0
        
        for row in range(rowLen):
            for col in range(colLen):
                if matrix[row][col] == 1:
                    memo[row][col] = 1 + min(memo[row][col - 1], memo[row - 1][col], memo[row - 1][col - 1])
                    count += memo[row][col]
        
        return count