# Table of Contents
1. [Linked List Cycle](#linked_list_cycle)
2. [DFS using stack(iterative dfs)](#iterative_dfs)
3. [Dynamic Programming - Knapsack](#knapsack)
4. [Custom Sorting](#custom_sort)
5. [Custom Priority Queue](#custom_priority_queue)

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

# HeapSort<a name="heapsort"></a>

## Max Heap

## Min Heap

## Sort

### Time Complexities

# Custom Sorting<a name="custom_sort"></a>

## Syntax

## How to return the correct inequality?
1. The value returned indicates whether the element passed as first argument is considered to go before the second in the specific strict weak ordering it defines. [Doc link](https://cplusplus.com/reference/algorithm/sort/)
2. In other words, `comp(x,y)` should return true if `x `is supposed to be placed before `y` in the resulting vector.
3. Furthermore from the documentation: *This can either be a function pointer or a function object.*
    1. Usually for comparator, we should pass the class that encompasses the `operator()` member function -> **Function object method**.
        ```cpp
        class cmp{
            public:
            bool operator() (int a, int b){return a < b;}
        };
        ...
        vector<int> vec;
        ...
        sort(vec.begin(), vec.end(), cmp());
        ```
    2. The **function pointer** method involves passing the comparator functions's pointer:
        ```cpp
        bool cmp (int a, int b){return a < b;}
        ...
        vector<int> vec;
        ...
        sort(vec.begin(), vec.end(), cmp);
        ```
        1. This by itself works if cmp is not a member function of some class.
            ```cpp
            bool cmp (int a, int b){return a < b;}
            ...
            int main(){
                vector<int> vec;
                ...
                sort(vec.begin(), vec.end(), cmp);
                ...
                return 0;
            }
            ```
        2. But if the `cmp` has to be included as a member function of the *`Solution`* class, then it cannot be non-static.
        3. This could be avoided if the `cmp` function is written outside the body of `class Solution`.
        4. Another alternative: use the **`lambda format`**: `sort(vec.begin(), vec.end(), [](int a, int b) -> bool {return a < b; });`
4. 


# Custom Priority Queue<a name="custom_priority_queue"></a>

## Constructor

## Operator Function
1. [From documentation:](https://cplusplus.com/reference/queue/priority_queue/) The expression `comp(a,b)`, where `comp` is an object of this type and `a` and `b` are elements in the container, shall return true if `a` is considered to go before `b` in the strict weak ordering the function defines.
    1. **Note:** Priority queues are a type of container adaptors, specifically designed such that its *first element is always the greatest of the elements* it contains, according to some strict weak ordering criterion.
    2. Lambda Function as comparator:
        ```cpp
        auto comp = [](int a, int b){return a > b;};
        priority_queue<int,vector<int>,decltype(comp)> pq(comp);
        ```
    3. if `a > b` then `a` will be placed before, hence the greatest(top) element of the heap will be the one placed last, i.e. the smallest one. Hence this is a min-heap.
    **Note:** The same lambda function for `sort` would return the array sorted in non-increasing order.

## Less Than override

## Greater than override

