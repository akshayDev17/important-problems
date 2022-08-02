# Table of Contents
1. [01 Matrix]()

# 01 Matrix<a name="p1"></a>
1. [Reference Link](https://leetcode.com/problems/01-matrix/)

## Solution
1. rather than randomly starting from i,j , its better if we first visit all 0's and put them into the **BFS Queue**.
2. go ahead with the vanilla BFS, without the `visited` array.
    1. rather than visited, if `dist[i][j]+1 < dist[next_i][next_j]` , this will serve as the `visited` checking condition.
    2. if true, push into the queue, if false continue.

