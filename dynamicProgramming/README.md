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

1. [CODE](#lcs.cpp)
2. simple 2-D DP problem
3. initialize matrix `lcs[n][m]` where `n = x.length(), m = y.length()`
   1. `lcs[i][j]` indicates the length of longest common subsequence, for the substrings `x[0..i]` and `y[0...j]`
4. consider `lcs[i][j], x[0...i], y[0...j]`
   1. now the characters `x[i+1]` and `y[j+1]` will be added to the LCS only if they are equal, i.e. `if(x[i] == y[j]) lcs[i+1][j+1] = 1+lcs[i][j]`
   2. otherwise `lcs[i+1][j+1] = max(lcs[i][j+1], lcs[i+1][j])`
   3. this is the subproblem construction for this DP problem
5. the answer is contained in the `lcs[n][m]` cell, which tells us the LCS between `x[0...n-1]` and `y[0...m-1]`







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