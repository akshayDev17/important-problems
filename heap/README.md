# Table of Contents

1. [Swim in rising water](#p1)
   1. [Solution](#sol1)
2. [Furthest Building You Can Reach](#p2)





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


# Furthest Building You Can Reach<a name="p2"></a>

1. <blockquote>
    You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.

    You start your journey from building 0 and move to the next building by possibly using bricks or ladders.

    While moving from building i to building i+1 (0-indexed),

    If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
    If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.
    Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally. 
  </blockquote>

2. The first solution that you can think of is to exhaust all bricks and then use up all ladders.
    1. The problem with this is that the optimal approach be: B L L B L B B.
    2. A sample test case - 
        ```cpp
        arr = [1,5,1,2,3,4,10000];
        bricks = 4, ladders = 1;
        ```
3. Ladders would be most helpful for the largest leaps.
    1. Hence a subproblem is: *find the `ladders` largest jumps*.
    2. But this is not the solution, as for the remaining jumps not handled by ladders, the total of these jumps could be greater than `bricks`.
4. Hence, iterate from first building, till `ladders` jumps are found, using ladders for all, i.e. **push into priority_queue(min heap)**.
    1. Now for `(ladders+1)'th` jump, push it and pop off the top(least jump encountered till now), checking whether it(the smallest jump) less than or equal to bricks.
        1. if its less, advance forward. This means that the smallest jump found till now can be cross by bricks, and the other remaining jumps found till now will be performed using Ladders.
        2. if not, it means that the smallest jump found till now, i.e. the most smallest jump amongst the first `ladders+1` jumps cannot be performed by bricks. Hence bricks are useless, and only ladders will take us to the furthest possible building.
    2. Continue to iterate through other jumps , checking whether the smallest jump can be made by remaining bricks.
