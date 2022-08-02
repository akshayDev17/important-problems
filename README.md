1. If n ≤ 12, the time complexity can be O(n!).
2. If n ≤ 25, the time complexity can be O(2n).
3. If n ≤ 100, the time complexity can be O(n4).
4. If n ≤ 500, the time complexity can be O(n3).
5. If n ≤ 10^4, the time complexity can be O(n2).
6. If n ≤ 10^6, the time complexity can be O(n log n).
7. If n ≤ 10^8, the time complexity can be O(n).
8. If n > 10^8, the time complexity can be O(log n) or O(1).

Examples of each common time complexity

- O(n!) [Factorial time]: Permutations of 1 ... n
- O(2n) [Exponential time]: Exhaust all subsets of an array of size n
- O(n3) [Cubic time]: Exhaust all triangles with side length less than n
- O(n2) [Quadratic time]: Slow comparison-based sorting (eg. Bubble Sort, Insertion Sort, Selection Sort)
- O(n log n) [Linearithmic time]: Fast comparison-based sorting (eg. Merge Sort)
- O(n) [Linear time]: Linear Search (Finding maximum/minimum element in a 1D array), Counting Sort
- O(log n) [Logarithmic time]: Binary Search, finding GCD (Greatest Common Divisor) using Euclidean Algorithm
- O(1) [Constant time]: Calculation (eg. Solving linear equations in one unknown)

- 2D vector 1-line declaration : `vector<vector<int>> arr = vector<vector<int>>(M, vector<int>(N, 0));` or (`vector<vector<int>> arr = vector<vector<int>>(M, vector<int>(0));`)


# Resources
1. [Striver's 180 problems sheet](https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/)

# Common Patterns
1. Hash Map
2. Prefix/suffix sum
3. forward/reverse traversal of array
4. BFS/DFS
    1. ## When to use DFS vs When to use BFS
        1. when you want to visit all children nodes at once, then BFS.
        2. When you want to visit each child one by one, process child[1] after processing child[0] , then DFS.
        3. BFS modifications usually won't have the **`visited`** array, whereas DFS usually has this concept.
5. DP
6. Greedy
7. Character array
8. Two pointer
9. Binary Search
10. Map(encode) to [common string pattern](https://leetcode.com/problems/find-and-replace-pattern/)
