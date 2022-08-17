# Table of Contents
1. [Linked List Cycle](#linked_list_cycle)
2. [DFS using stack(iterative dfs)](#iterative_dfs)
3. [Dynamic Programming - Knapsack](#knapsack)
4. [Customer Priority Queue](#custom_priority_queue)

# Linked List Cycle<a name="linked_list_cycle"></a>
1. Given a linked list, tell where does the cycle begin, *if there is any*.

## Solution
1. Check cycle by the slow-fast pointer method.
    1. If fast becomes `NULL` - no cycle.
    2. If `slow == fast` - cycle located.
2. Measure the length of cycle, i.e. the number of nodes in the cycle = `l`.
3. Now, initialize `slow` at `head`, travel `l` nodes forward.
4. Now initialize `fast` at head, and iterate till `slow == fast`.
5. The following diagram explains why this works: <img src="linked_list_cycle.png" />

# DFS using stack(iterative DFS)<a name="iterative_dfs"></a>

# Dynamic Programming - Knapsack<a name="knapsack"></a>
1. Its not always necessary to think about building up on the array.
    1. for eg. dp[i] = will depend on arr[0...i]
    2. you could rather think about this target variable, and start building up on either target=0 or target=target.
2. Similar problem - [Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/)

# Custom Priority Queue<a name="custom_priority_queue"></a>

## Constructor

## Operator Function

## Less Than override

## Greater than override

