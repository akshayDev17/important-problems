# Table of Contents

1. [Swim in rising water](#p1)
   1. [Solution](#sol1)





# Swim in rising water<a name="p1"></a>

1. On an N x N `grid`, each square `grid[i][j]` represents the elevation at that point `(i,j)`.

   Now rain starts to fall. At time `t`, the depth of the water everywhere is `t`. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most `t`. You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.

   You start at the top left square `(0, 0)`. What is the least time until you can reach the bottom right square `(N-1, N-1)`?

2. ```
   Input: [[0,2],[1,3]]
   Output: 3
   Explanation:
   At time 0, you are in grid location (0, 0).
   You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
   
   You cannot reach point (1, 1) until time 3.
   When the depth of water is 3, we can swim anywhere inside the grid.
   
   
   Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
   Output: 16
   Explanation:
    0  1  2  3  4
   24 23 22 21  5
   12 13 14 15 16
   11 17 18 19 20
   10  9  8  7  6
   
   The final route is marked in bold.
   We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
   ```

3. [Leetcode](https://leetcode.com/problems/swim-in-rising-water/)





## Solution<a name="sol1"></a>

1. ```cpp
   class Solution {
   public:
       class Point{
           public:
           int val;
           int row;
           int col;
           Point(int v, int i, int j){
               val = v;row = i;col = j;
           }
           
       };
       class Comp{
           public:
           bool operator() (Point const& a, Point const& b){
               return a.val > b.val;
           }
       };
       int swimInWater(vector<vector<int>>& grid) {
           int n = grid.size();
           set<pair<int,int> > s;
           s.insert(make_pair(0, 0));
           priority_queue<Point, vector<Point>, Comp> hp;
           Point p(grid[0][0], 0, 0);
           hp.push(p);
           int dir[] = {0, -1, 0, 1, 0}, result = INT_MIN;
           while(!hp.empty()){
               p = hp.top();hp.pop();
               // cout << p.val << " ";
               result = max(result, p.val);
               if(p.row == n-1 && p.col == n-1) return result;
               for(int k = 0;k<4;k++){
                   int x = p.row+dir[k], y = p.col + dir[k+1];
                   pair<int,int> temp(x, y);
                   if(x >= 0 && y >= 0 && x < n && y < n && s.find(temp) == s.end()){
                       s.insert(temp);
                       Point curr(grid[x][y], x, y);
                       hp.push(curr);
                   }
               }
           }
           return result;
       }
   };
   ```

2. this solution works because if suppose a wrong path is chosen, due to the greedy nature of choosing the next cell, a better path is automatically chosen.

3. this is ensured due to the numbers in the matrix being in the range `[0 to N*N-1]`

4. for instance, if suppose the input grid is:

   ```
   Input:
   0  1  2  3  4
   15 23 22 21  5
   12 13 14 24 16
   11 17 18 19 20
   10  9  8  7  6
   ```

   1. the values that will be first popped are 0, 1, 2, 3, 4, 5, 16, after which the algorithm will realise that the a better path actually lies on a forking path at the starting cell(**it may not be always necessary that a better path is **), i.e. from 0->15
   2. thus the next popped items in sequential order are 15, 12, 11, 10, 9, 8, 7, 6.