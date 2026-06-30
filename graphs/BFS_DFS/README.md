# Table of Contents
1. [01 Matrix](#p1)
2. [Maximum Fuel Cost](#p2)

# 01 Matrix<a name="p1"></a>
1. [Reference Link](https://leetcode.com/problems/01-matrix/)

## Solution
1. rather than randomly starting from i,j , its better if we first visit all 0's and put them into the **BFS Queue**.
2. go ahead with the vanilla BFS, without the `visited` array.
    1. rather than visited, if `dist[i][j]+1 < dist[next_i][next_j]` , this will serve as the `visited` checking condition.
    2. if true, push into the queue, if false continue.

# Maximum Fuel Cost<a name="p2"></a>
1. [Link](https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/description/?envType=problem-list-v2&envId=graph)

## Thought Process
1. yes you have to compute the answer via DFS traversal
2. think w.r.t. leaf node representatives, how would they travel
3. think at those non-leafs which are junctions for leafs
    1. think how the rearrangement of cars would take place at this junction node
    2. observe that the leaf representatives, until they arrived at this junction node, travelled for those many hops
    3. a junction could very well be just a single leaf arriving at that node
    4. hence, think in terms of subtree of a node.
4. recursively build on steps 2-3.
5. the car rearrangements will happen on each node.