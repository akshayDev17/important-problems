# Table of Contents

1. [Longest Increasing Subsequence](#lis)
   1. [Solution](#sol1)
2. [Longest Common Subsequence](#lcs)
   1. [Solution](#sol2)
3. [Longest Common Substring](#lcsub)
   1. [Solution](#sol3)
4. [0-1 Knapsack Problem](#0-1kp)
   1. [Solution](#sol4)
5. [Egg Dropping Problem](#egg-dropping)
   1. [Solution](#sol5)
6. [Shortest Common Supersequence](#scs)
   1. [Solution](#sol6)
7. [Stone Game](#stone-game)
   1. [Solution](#sol7)
8. [Stone Game 2](#stone-game-2)
   1. [Solution](#sol8)
9. [Team with no conflicts](#team-with-no-conflicts)
   1. [Solution](#sol9)







# Longest Increasing Subsequence<a name="lis"></a>

1. find the length of the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. 

2. ```bash
   Input: arr[] = {3, 10, 2, 1, 20}
   Output: Length of LIS = 3
   The longest increasing subsequence is 3, 10, 20
   
   Input: arr[] = {3, 2}
   Output: Length of LIS = 1
   The longest increasing subsequences are {3} and {2}
   
   Input: arr[] = {50, 3, 10, 7, 40, 80}
   Output: Length of LIS = 4
   The longest increasing subsequence is {3, 7, 40, 80}
   ```



## Solution<a name="sol1"></a>

1. [CODE - O(n^2)](lis.cpp),   [CODE - O(nlogn)](lis_2.cpp)
2. maintain an array `lis[i]` , that contains the length of the longest increasing subsequence for the  subarray `arr[0...i]` , such that the last element of this subsequence is `arr[i]`
3. hence a recursive solution is formed, such that `lis[i] = 1 + max(lis[0], lis[1], ....lis[i-1])` with `arr[i] > arr[0], arr[i] > arr[1], .... arr[i] > arr[i-1]` and if this inequality holds false, then `lis[i] = 1`
   1. it may so happen that this inequality holds true for some indices , say 0, 2, 4, 5, ... and doesn't hold true for other, say 1, 3, 6, ....
   2. 
4. the final answer would be `max(lis[0], lis[1], .... lis[n-1])` , n : size of array.
5. `lis`  will obviously be initialised as `[1,1,.....1]` since by definition each element is a subsequence of length=1.
6. this **DP** based approach can give an answer for both
   1. longest **non-decreasing** subsequence
   2. longest **strictly increasing** subsequence







# Longest Common Subsequence<a name="lcs"></a>

1. Given two strings, find the length of longest subsequence present in both of them.

2. ```bash
   Input:
   A = 6, B = 6
   str1 = ABCDGH
   str2 = AEDFHR
   Output: 3
   
   Input:
   A = 3, B = 2
   str1 = ABC
   str2 = AC
   Output: 2
   ```



## Solution<a name="sol2"></a>

1. [CODE](lcs.cpp)
2. simple 2-D DP problem
3. initialize matrix `lcs[n][m]` where `n = x.length(), m = y.length()`
   1. `lcs[i][j]` indicates the length of longest common subsequence, for the substrings `x[0..i]` and `y[0...j]`
4. consider `lcs[i][j], x[0...i], y[0...j]`
   1. now the characters `x[i+1]` and `y[j+1]` will be added to the LCS only if they are equal, i.e. `if(x[i] == y[j]) lcs[i+1][j+1] = 1+lcs[i][j]`
   2. otherwise `lcs[i+1][j+1] = max(lcs[i][j+1], lcs[i+1][j])`
   3. this is the subproblem construction for this DP problem
5. the answer is contained in the `lcs[n][m]` cell, which tells us the LCS between `x[0...n-1]` and `y[0...m-1]`
6. to print the subsequence
   1. traverse this 2D array, starting from `lcs[n][m]`
   2. if `x[n-1] == y[m-1]` *pre-pend*    this character to the answer string(if not do nothing), we pre-pend this character because we know that this is the last character of the Longest common subsequence, for the strings `x[0...n-1], y[0...m-1]` . 
      1. after this, `i--;j--` since we know `lcs[n][m] = 1 + lcs[n-1][m-1] if x[n-1] == y[m-1]`
   3. **else**, move in the direction of `max(lcs[n-1][m], lcs[n][m-1])`, i.e. if `lcs[n-1][m] > lcs[n][m-1]` do `i--` else do `j--` .
   4. continue this till either of i or j hits 0.





# Longest Common Substring<a name="lcsub"></a>

1. Given two strings **X** and **Y**. The task is to find the length of the longest common substring.

2. ```bash
   Input: X = ABCDGH, Y = ACDGHR
   Output: 4
   
   Input: X = ABC, Y = AC
   Output: 1
   ```



## Solution<a name="sol3"></a>

1. [CODE](lc_substring.cpp)
2. almost all of the solution is common to the above longest common **subsequence** problem
3. here, the dp array stores the longest common **suffix** for the strings `x[0...i-1]` and `y[0...j-1]`
4. the only different step is `if(x[i-1] != y[j-1]) dp[i][j] = 0`
   1. this is because, since the longest common suffix is calculated, if the last characters are different, naturally the suffixes are not the same, hence there is no possibility of having a longest common suffix.
5. After this 2D array is filled, we iterate through all cells, and extract the cell with the maximum `dp[i][j]` value, since that represents the longest common suffix for the sub-strings  `x[0...i-1]` and `y[0....j-1]` .
6. Time complexity = O(n\*m), `n = x.length(), m = y.length()` .





# 0-1 Knapsack Problem<a name="0-1kp"></a>

1. Given weights and values of `n` items, put these items in a knapsack of capacity `W` to get the maximum total value in the knapsack.

2. the items will be picked in a 0-1 fashion, i.e. no item has multiple copies of it.

3. ```bash
   Input:
   N = 3
   W = 4
   values[] = {1,2,3}
   weight[] = {4,5,1}
   Output: 3
   
   Input:
   N = 3
   W = 3
   values[] = {1,2,3}
   weight[] = {4,5,6}
   Output: 0
   ```





## Solution<a name="sol4"></a>

1. [CODE](01kp.cpp)
2. either an item will be included or excluded.
3. the dp 2D matrix is created by iterating for all possible weights that the knapsack can carry, i.e. `w = 1 to W`
4. for each of these weights, the `ith` item **may be** picked only if `wt[i] <= w`
   1. if `wt[i] > w` we obviously cannot pick item `i` for our knapsack of capacity = `w`
   2. if `wt[i] <= w`, we may either benefit from picking item-i or not, which is decided by comparing `values[i]+dp[w-weights[i]][i-1]` (pick item i and find value for the remaining capacity of the knapsack) with `dp[w][i-1]`, i.e. reject `i` and find the value for knapsack of capacity `w`.
5. thus the time and memory complexities are O(n*W), W = capacity of knapsack, n = total available items.
6. the **[fractional knapsack](../greedy/README.md/#fkp)** is a **greedy-approach** based problem.







# Egg Dropping Problem<a name="egg-dropping"></a>

1. N eggs and you want to determine from which floor in a K-floor building you can drop an egg such that it doesn't break.

   1. determine the **minimum number of attempts** you need in order find the critical floor in the worst case while using the best strategy.
   2. An egg that survives a fall can be used again.
   3. A broken egg must be discarded.
   4. The effect of a fall is the same for all eggs.
   5. If the egg doesn't break at a certain floor, it will not break at any floor below.
   6. If the eggs breaks at a certain floor, it will break at any floor above.

2. ```bash
   Input:
   N = 2, K = 10
   Output: 4
   
   Input:
   N = 3, K = 5
   Output: 3
   ```

3. [geeksforgeeks practice](https://practice.geeksforgeeks.org/problems/egg-dropping-puzzle-1587115620/1),  [geeksforgeeks explanation](https://www.geeksforgeeks.org/egg-dropping-puzzle-dp-11/)



## Solution<a name="sol5"></a>

1. [CODE](egg.cpp),  [TEST](eggTest.txt)
2. When we drop an egg from a floor x, there can be two cases:
   1. The egg breaks
   2. The egg doesn’t break.
3. If the egg breaks after dropping from floor `x` , then we only need to check for floors lower than `x` with remaining eggs as some floor should exist lower than `x` in which egg would not break; so the problem reduces to `x-1` floors and `n-1` eggs.
4. If the egg doesn’t break after dropping from the floor `x` , then we only need to check for floors higher than `x`; so the problem reduces to `k-x` floors and `n` eggs.
5. Since we need to minimize the number of trials in *worst* case, we take the maximum of two cases. 
6. We then go on to choose the floor with the minimum of all these maximum values.
   1. this is done so as to optimize the worst case scenario.
7. thus `cost[i][j] = min(1+max(cost[i-1][j-1], cost[i][j-x])), for x = [1,2,3,....j]`, where `i` represents the eggs remaining, and `j` represents the number of floors remaining to be checked.
   1. if number of stones is 1, i.e. `i == 1`, then `dp[i][j] = j` 
   2. `dp[i][1] = 1, for i >=1`







# Shortest Common Supersequence<a name="scs"></a>

1. [geeks for geeks practice](https://practice.geeksforgeeks.org/problems/shortest-common-supersequence/0)

2. Given two strings `str1` and `str2`, find the shortest string that has both `str1` and `str2` as **subsequences**.

3. ```bash
   Input:   str1 = "geek",  str2 = "eke"
   Output: "geeke"
   
   Input:   str1 = "AGGTAB",  str2 = "GXTXAYB"
   Output:  "AGXGTXAYB"
   ```





## Solution<a name="sol6"></a>

1. [CODE](scs.cpp),  [TEST](scsTest.txt)

2. the approach is very similar to finding [longest common subsequence](#lcs) of 2 strings.

3. `dp[i][j]` will represent the length value of the optimal supersequence for sub-strings `x[0...i-1], y[0...j-1]`

4. now, `if x[i-1] == y[j-1]`, this means that this character might be the last occurring character, as part of the LCS of `x[0...i-1], y[0...j-1]` , and after this character, all characters which are not common within `x[i...n-1], y[j....m-1]` will be occurring.

   1. hence this line `if(x[i-1] == y[j-1]) dp[i][j] = 1 + dp[i-1][j-1];`  represents this.

5. if they aren't equal, that means that we need to find the shortest supersequence, among `x[0....i-1], y[0.....j-2]` and `x[0....i-2], y[0....i-1]` and then the respective remaining character, i.e. `y[j-1]` (if the former is selected) or `x[i-1]` (if the latter is selected) will be appended to the supersequence obtained.

   1. this line represents this point: `else dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);`

6. trivially, if the first string is empty, all characters of the other string will become the supersequence <a name="trivial"></a>

   1. this is represented by:

      ```cpp
      if(i == 0) dp[i][j] = j;
      else dp[i][j] = i; // j == 0
      ```

7. now, for **printing** the supersequence

   1. the approach is almost entirely same as LCS(since the process of building up the 2D array was entirely the same)
   2. start with `dp[n][m]` , if `x[n-1] == y[m-1]` , *pre-pend* the last character and decrement `i--; j--;`
   3. else find out which of the `dp[n-1][m], dp[n][m-1]` yields a shorter common supersequence
      1. if the former one does so, then *pre-pend* `x[n-1]`
      2. else *pre-pend* `y[m-1]`
   4. continue this till either `i == 0` or `j == 0`
   5. this basically means that at-most one of the strings has some remaining characters, as was cleared by [this point](#trivial)
      1. if `i != 0` then *pre-pend* all remaining characters of `x`
      2. else *pre-pend* all remaining characters of `y`.







# Stone Game<a name="stone-game"></a>

1. [Leetcode](https://leetcode.com/problems/stone-game/)

   1. the question here has some additional constraints which makes the problem a bit more simpler, but we decided to remove them, so as to understand the DP aspect solely.

2. Alex and Lee play a game with piles of stones. There are a number of piles **arranged in a row**, and each pile has a positive integer number of stones `piles[i]`.

   The objective of the game is to end with the most stones. 

   Alex and Lee take turns, with Alex starting first. Each turn, a player takes the entire pile of stones from either the beginning or the end of the row. This continues until there are no more piles left, at which point the person with the most stones wins.

   Assuming Alex and Lee play optimally, return `True` if and only if Alex wins the game.



## Solution<a name="sol7"></a>

1. ```cpp
   bool stoneGame(vector<int>& piles) {
       int n = piles.size();
       vector<int> temp(n, 0);
       vector<vector<int> > dp(n, temp);
       for(int i = 0;i<n;i++) dp[i][i] = piles[i];
       for(int size = 1;size < n;size++){
           for(int i = 0;i<n-size;i++){
               dp[i][i+size] = max(piles[i] - dp[i+1][i+size], piles[i+size]-dp[i][i+size-1]);
           }
       }
       return dp[0][n-1];
   }
   ```

2. `dp[i][j]` = in the sub-array `piles[i]...piles[j]`, biggest number of stones Alex can get more than Lee in the mentioned pile-picking manner.

3. since the starting player can pick the starting or ending pile, here either `piles[i]` or `piles[j]` can be picked.

   1. if `piles[i]` is picked, result will be `piles[i]-dp[i+1][j]`
   2. if `piles[j]` is picked, result will be `piles[j]-dp[i][j-1]`

4. thus we have `dp[i][j] = max(piles[i] - dp[i+1][j], piles[j]-dp[i][j-1])`.

5. We start from smaller sub-array and then we use that to calculate bigger sub-array.

   1. hence the outer loop of the nested loop is the one where size changes , since we need to formulate answers for the smallest of sub-arrays starting from all possible starting indices within the `piles` array.







# Stone Game 2<a name="stone-game-2"></a>

1. [Leetcode](https://leetcode.com/problems/stone-game-ii/)

2. Alice and Bob continue their games with piles of stones. There are a number of piles **arranged in a row**, and each pile has a positive integer number of stones `piles[i]`. The objective of the game is to end with the most stones. 

   Alice and Bob take turns, with Alice starting first. Initially, `M = 1`.

   On each player's turn, that player can take **all the stones** in the **first** `X` remaining piles, where `1 <= X <= 2M`. Then, we set `M = max(M, X)`.

   The game continues until all the stones have been taken.

   Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.

3. ```bash
   Input: piles = [2,7,9,4,4]
   Output: 10
   Explanation:  If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. Alice can get 2 + 4 + 4 = 10 piles in total. If Alice takes two piles at the beginning, then Bob can take all three piles left. In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger. 
   ```

4. ```bash
   Input: piles = [1,2,3,4,5,100]
   Output: 104
   ```





## Solution<a name="sol8"></a>

1. ```cpp
   class Solution {
   public:
       int dp(int idx, int m, vector<vector<int> > &mem, int n, vector<int> suffixSum){
           if(idx + 2*m >= n) return mem[idx][m] = suffixSum[idx];
           if(mem[idx][m] != -1) return mem[idx][m];
           int result = 0, currPlayerScore = 0;
           for(int i = 1;i<=2*m;i++) result = max(result, suffixSum[idx] - dp(idx+i, max(m, i), mem, n, suffixSum) );
           return mem[idx][m] = result;
       }
       int stoneGameII(vector<int>& piles) {
           int n = piles.size();
           if(n == 1) return piles[0];
           if(n == 2) return piles[0]+piles[1];
           
           vector<int> suffixSum(n, 0);suffixSum[n-1] = piles[n-1];
           for(int i = n-2;i>=0;i--) suffixSum[i] = suffixSum[i+1]+piles[i];       
           
           vector<int> temp(n, -1);
           vector<vector<int> > mem(n, temp);
           dp(0, 1, mem, n, suffixSum);
           return mem[0][1];
       }
   };
   ```

2. the step `result = max(result, suffixSum[idx] - dp(idx+i, max(m, i), mem, n, suffixSum) );`  signifies that out of the currently remaining `suffixSum[idx]` stones, we take out `dp(idx+i, max(m, i), mem, n, suffixSum)` because this is the number of stones that will be taken by the opponent, thus leaving us with the difference of these quantities.

3. since we want to maximise the number of stones that we picked in this round, we take a max of all possible differences.





# Team with no conflicts<a name="team-with-no-conflicts"></a>

1. [LeetCode](https://leetcode.com/problems/best-team-with-no-conflicts/)

2. You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the **sum** of scores of all the players in the team.

   However, the basketball team is not allowed to have **conflicts**. A **conflict** exists if a younger player has a **strictly higher** score than an older player. A conflict does **not** occur between players of the same age.

   Given two lists, `scores` and `ages`, where each `scores[i]` and `ages[i]` represents the score and age of the `ith` player, respectively, return *the highest overall score of all possible basketball teams*.

3. ```
   Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
   Output: 34
   Explanation: You can choose all the players.
   ```

4. ```
   Input: scores = [4,5,6,5], ages = [2,1,2,1]
   Output: 16
   Explanation: It is best to choose the last 3 players. Notice that you are allowed to choose multiple people of the same age.
   ```

5. ```
   Input: scores = [1,2,3,5], ages = [8,9,10,1]
   Output: 6
   Explanation: It is best to choose the first 3 players. 
   ```





## Solution<a name="sol9"></a>

1. ```cpp
   class Solution {
   public:
       static bool compare(const pair<int,int> &a, const pair<int,int> &b){
           if(a.second != b.second) return a.second < b.second;
           return a.first < b.first;
       }
       int bestTeamScore(vector<int>& scores, vector<int>& ages) {
           int n = scores.size();
           if(n == 1) return scores[0];
           vector<pair<int,int> > vec(n, make_pair(0, 0));
           for(int i = 0;i<n;i++) vec[i] = make_pair(scores[i], ages[i]);
           sort(vec.begin(), vec.end(), compare);
   
           vector<int> allScores(n, 0);
           for(int i = 0;i<n;i++){
               allScores[i] = vec[i].first;
               for(int j = 0;j<i;j++){
                   if(vec[j].first <= vec[i].first) allScores[i] = max(vec[i].first + allScores[j], allScores[i]);
               }
           }
           return *max_element(allScores.begin(), allScores.end());
       }
   };
   ```

2. firstly, this is just a slight modification on the [LIS](#lis) problem.

3. ascending sorting w.r.t. ages :-

   1. if ages are same, we need to ascend sort w.r.t. scores, or else the LIS part of the algorithm will fail in capturing all allowed players, since it will think that the players having score larger than the current will always be in a conflict, but its not true, since players having same age won't ever have  a conflict.

   2. for instance, in the case:

      ```bash
      [319776,611683,835240,602298,430007,574,142444,858606,734364,896074]
      [1,1,1,1,1,1,1,1,1,1]
      ```

      all ages are the same, hence if we perform a descend sort w.r.t. scores, then the LIS algorithm will give us the answer as **`896074`**, since the array gets sorted into `[896074, 858606, 835240,...]` and the LIS of this array is obviously `896074`.

4. now, for the current player, suppose we have made the decision of selecting this player, (`allScores[i] = vec[i[.first]]`)

   1. iterate through all players younger than this one(`j< i`), and if their score is smaller/equal to that of the current player, then check whether including this player(`vec[i].first + allScores[j]`) increases the overall score `allScores[i]`

5. after building this array of LIS, return the maximum element, and not `allScores[n-1]`, which would mean purposely selecting player with `scores[n-1], ages[n-1]`