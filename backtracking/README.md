# Table of Contents

1. [N-Queens Problem](#nqueens)
   1. [Solution](#sol1)





# N-Queens Problem<a name="nqueens"></a>

1. The N Queen is the problem of placing N chess queens on an N×N chessboard so that no two queens attack each other.

2. ```bash
   Input: N = 4
   Output: { 0,  1,  0,  0}
           { 0,  0,  0,  1}
           { 1,  0,  0,  0}
           { 0,  0,  1,  0}
   ```





## Solution<a name="sol1"></a>

1. [CODE](nQueens.cpp), 	[TEST](nQueensTest.txt)
2. for N = 1, only possible position is `{1}`
   1. for N = 2, not possible
   2. for N = 3, not possible
3. place queens one by one in different columns, starting from the leftmost column.
4. When we place a queen in a column, we check for clashes with already placed queens.
5. In the current column, if we find a row for which there is no clash, we mark this row and column as part of the solution(candidate position for this column's queen).
6. If we do not find such a row due to clashes then we backtrack and return false(i.e. for this N value, such an arrangement is not possible).
7. if for the first queen, i.e. 1st column, no such row is found for which the problem could be solved further, then `false` is returned, stating that no such configuration is possible for this particular N value.