# Table of Contents

1. [sub-square-matrices with all a's](#sub-square-all-1s)





# sub-square-matrices with all a's<a name="sub-square-all-1s"></a>

1. Given a `m * n` matrix of ones and zeros, return how many **square** submatrices have all ones.

2. ```bash
   Input: matrix =
   [
     [0,1,1,1],
     [1,1,1,1],
     [0,1,1,1]
   ]
   Output: 15
   Explanation: 
   There are 10 squares of side 1.
   There are 4 squares of side 2.
   There is  1 square of side 3.
   Total number of squares = 10 + 4 + 1 = 15.
   ```

3. [sub_squares.py](sub_squares.py)



## Solution<a name="sub-squares-sol"></a>

1. `memo` = a matrix of same dimensionality, and all elements initialised to 0
2. for a cell `matrix[i,j]` 
   1. if it itself is 1, then it can contribute to the total count , since it itself represents a square matrix of 1x1.
   2. if it is a part of a bigger matrix of all 1's, then that is possible if and only if `memo[i-1,j],memo[i,j-1],memo[i-1,j-1]` are all 1's, then only will `memo[i,j] > 1` .
   3. if any of the 3 elements are 0, then only the contribution of `matrix[i,j] == 1`, i.e. a matrix of 1x1 is to be counted.
   4. this code considers the outcome that cell `i,j` is the bottom-right cell of a matrix of order mxm. and we are basically checking for how many such square-matrices of all 1's can the cell `i,j` be their bottom-right element.
   5. by default the first row and first column of `memo` is equal to that of `matrix`.
   6. 