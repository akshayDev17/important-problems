# Table of Contents

1. [N-Queens Problem](#nqueens)
   1. [Solution](#sol1)
2. [Gold Coins](#gold-coins)
   1. [Solution](#sol2)





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







# Gold Coins<a name="gold-coins"></a>

1. In a gold mine `grid` of size `m * n`, each cell in this mine has an integer representing the amount of gold in that cell, `0` if it is empty.

   Return the maximum amount of gold you can collect under the conditions:

   - Every time you are located in a cell you will collect all the gold in that cell.
   - From your position you can walk one step to the left, right, up or down.
   - You can't visit the same cell more than once.
   - Never visit a cell with `0` gold.
   - You can start and stop collecting gold from **any** position in the grid that has some gold.

2. [LEETCODE](https://leetcode.com/problems/path-with-maximum-gold/)

3. **Example 1:**

   ```bash
   Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
   Output: 24
   Explanation:
   [[0,6,0],
    [5,8,7],
    [0,9,0]]
   Path to get the maximum gold, 9 -> 8 -> 7.
   ```

   **Example 2:**

   ```bash
   Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
   Output: 28
   Explanation:
   [[1,0,7],
    [2,0,6],
    [3,4,5],
    [0,3,0],
    [9,0,20]]
   Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
   ```

   

4. **Constraints:**

   - `1 <= grid.length, grid[i].length <= 15`
   - `0 <= grid[i][j] <= 100`
   - There are at most **25** cells containing gold.





## Solution<a name="sol2"></a>

1. the point here is just to compare the codes of the dfs functions in the below 2 solution codes:

   ```cpp
   class Solution {
   public:
       int getGold(int sr, int sc, vector<vector<int> > &grid, int n, int m){
           if(sr < 0 || sr >= n || sc < 0 || sc >= m || grid[sr][sc] == 0) return 0;
           // if(grid[sr][sc] == 0) return 0;
           
           // neither visited, nor non-zero cell
           int temp = grid[sr][sc];
           grid[sr][sc] = 0; // mark this cell as visited
           
           int a1 = getGold(sr+1, sc, grid, n, m), a2 = getGold(sr, sc+1, grid, n, m), a3 = getGold(sr, sc-1, grid, n, m), a4 =  getGold(sr-1, sc, grid, n, m);
           int res = max(a1, max(a2, max(a3, a4)));
           grid[sr][sc] = temp;
           return temp + res;
           
       }
       int getMaximumGold(vector<vector<int>>& grid) {
           int n = grid.size();
           if(n == 0) return 0;
           int m = grid[0].size();
           if(m == 0) return 0;
           int ans = 0;
           for(int i = 0;i<n;i++){
               for(int j = 0;j<m;j++){
                   ans = max(
                       getGold(i, j, grid, n, m),
                       ans);
               }
           }
           return ans;
       }
   };
   ```

   ```cpp
   class Solution {
   public:
       int getGold(int sr, int sc, vector<vector<int> > grid, int n, int m, vector<vector<bool> > &vis){
           if(sr < 0 || sr >= n || sc < 0 || sc >= m) return 0;
           if(grid[sr][sc] == 0  || vis[sr][sc]) return 0;
           // neither visited, nor non-zero cell
           vis[sr][sc] = true;
           vector<int> paths;
           paths.push_back(getGold(sr, sc+1, grid, n, m, vis));
           paths.push_back(getGold(sr, sc-1, grid, n, m, vis));
           paths.push_back(getGold(sr-1, sc, grid, n, m, vis));
           paths.push_back(getGold(sr+1, sc, grid, n, m, vis));
           vis[sr][sc] = false;
           return grid[sr][sc] + *max_element(paths.begin(), paths.end());
           
       }
       int getMaximumGold(vector<vector<int>>& grid) {
           int n = grid.size();
           if(n == 0) return 0;
           int m = grid[0].size();
           if(m == 0) return 0;
           int ans = 0;
           
           vector<bool> tmp(m, false);
           vector<vector<bool> > vis(n, tmp);
           for(int i = 0;i<n;i++){
               for(int j = 0;j<m;j++){
                   // vis[i][j] = true;
                   ans = max(
                       getGold(i, j, grid, n, m, vis),
                       ans);
                   // vis[i][j] = false;
               }
           }
           return ans;
       }
   };
   ```

2. **Takeaways:**

   1. don't use visited array unnecessarily (:angry:) , here `grid[sr][sc]=0;` will do the job for us, no need to use extra memory.
   2. the second code **yielded a TLE** on [leetcode](https://leetcode.com/problems/path-with-maximum-gold/) , Possible reasons:
      1. usage of vis(visited matrix), its updation and re-updation times.
      2. usage of `vector`, with **4 `push_back()`** operations and **`*max_element()`** function, which may lead to an excess complexity, as compared to the simple 4 variable storage and nested `max()` functions, which yielded a solution of only **56ms** time.