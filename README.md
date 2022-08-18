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
    2. [You might want to start *coloring* at positions where the answer is obvious](https://leetcode.com/submissions/detail/760735176/).
    3. the concept of visited is emulated as level number in BFS.
    ```cpp
    // assume q is filled with the set of coordinates from which BFS needs to be started.
    int level = 0;
    while(!q.empty()){
        int sz = q.size();
        while(sz){
            pair<int,int> p = q.front();q.pop();
            int r = p.first, c = p.second;
            for(int i = 0;i<4;i++){
                int nr = r + moves[i], nc = c + moves[i+1];
                if(!isInvalid(i,j,m,n) && grid[nr][nc] != 1) q.push(make_pair(nr, nc));
            }
            sz--;
        }
        level++;
    }
    ```
    4. Coloring nodes in an alternative fashion might result into something, such as the *Detect a Bipartite graph* problem.
    5. If the answer is to be found via going through multiple paths((0,0)-->(m-1,n-1)), such that the paths will have common cells, then `visited` array will not work as the optimal path can have nodes common to a non-optimal path, but if the non-optimal path is traversed through first, some nodes will be marked visited, and hence the optimal path will never be found.
    Hence something like a `distance` array will help better, because if `dist[i][j]` is updated, it means we have found a better path than the previously traversed ones.
    `visited` array usually requires a *directed graph*, whereas if an **undirected one** is given it could mean that some **nodes will be traversed more than once** while traversing through all possible paths.
5. DP
    1. Knapsack approach
        1. Rather than working with the array, work with the X value.
            1. i.e., start from `ans(x=0), then ans(x=1).....ans(x=X)`.
6. Greedy
7. Character array
8. Two pointer
9. Binary Search
10. Map(encode) to [common string pattern](https://leetcode.com/problems/find-and-replace-pattern/)

# Best Practices<a name="best_practices"></a>

## Pass By Reference for big vectors and big strings
1. Its always better to use pass by reference for helper functions when using big vectors/strings, or else you might get a TLE because the compile will be forced to create a new copy of that large *container* for each call.
    1. Codes such as `dfs` can easily get TLE due to this.

## Int to String
    1. ```cpp
        int x = 234;
        string ans;
        stringstream ss; ss<< x;
        ss >> ans;
       ```
    
