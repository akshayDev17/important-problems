# Table of Contents
1. [Max XOR of two elements in array](#max_xor)
2. [Knapsack using bitset](#bitset_knapsack)
3. [Number of triangles in a given graph](#num_triangles_in_graph)

# Max XOR of two elements in array<a name="max_xor"></a>
1. Given an array of size n(n <= 2 * 10^5) , return max xor value of two elements. All elements are non-negative.
2. Explanation:
    1. Mask each element.
        1. w.r.t. the test case `[3,10,5,25,2,8]`, till bit > 4, all mask to 0.
        2. at bit=4 , idx=3 masks to 16, all others mask to 0.
        3. at bit-3, idx=3-->24, idx=1,5--->8, idx=0,2,4-->0
        4. at bit=2, idx=3-->24, idx=1,5--->8, idx=2-->4, idx=0,4-->0
    2. insert mask into a set.
    3. the idea here is that if `newMax` is the answer, it should be found by xoring atleast 1 pair in the given array. \
    Say the pair is a,b , where a and b are masks of actual values A,B. \
    if `a^b = newMax`, then `a^newMax = b` , hence we xor off all masks in the set(`a`) with `newMax` to see if `b` is found, if yes, `mx=newMax`, i.e. a new maximum is found. \
    4. `newMax(at bit=i) >= (at bit=i+1)` because `mx` will either remain unchanged(the if condition wasn't met), or if the condition is met, then `mx` goes from `...1000...` --> `...1100...`
2. Solution: [max_xor.cpp](max_xor.cpp)

# Knapsack using bitset<a name="bitset_knapsack"></a>
1. your given `N <= 1000` items, each with weight `w[i]`, such that `w[i] <= 1000000000`, and also a value `W`. Find if its possible to form a bag having weight exactly equal to `W`.
2. Solution: for each w[i], all bags with weights between w[i] and W can be formed if w[W-i] can be formed.
```cpp
int maxW = 1000000001;
bool numWays(vector<int> w, int W){
    int n = w.size();
    bitset<maxW> bs;
    bs[0] = true; // a bag with 0 weight can be formed by selecting no item
    /*
    Initial approach:
    vector<bool> can(W+1, false);
    can[0]=true; // a bag with 0 weight can be formed by selecting no item
    for(int i=0;i<n;i++){
        for(int j=W;j>=w[i];j--){
            if(can[j-w[i]]) can[j]=true;
        }
    }
    return can[W];
    */
    for(int i=0;i<n;i++){
        bs = bs | (bs << w[i]);
        /*
        with weight=m is possible, bs[m]=1 else 0.

        maxW = 10, W = 5
        00000000001 (bs[0] = true)

        x=2
        00000000101(same as 00000000001 | (00000000001 << 2 = 00000000100))
        i-th bit + 2 would mean that all i+2(bs[i]=1) are made possible, which is nothing but shifting `bs` by 2.

        x=3
        3,3+2 would be set
        00000101101(same as 00000000101 | (00000000101 << 3 = 00000101000))
                            00000101000
        */
    }
    return bs[W];
}
```

# Number of triangles in a given graph<a name="num_triangles_in_graph"></a>
1. Given a graph with N<=2000 vertices, count triangles (a,b,c).
2. Solution:
    1. for each vertex(`a`), check its adjancency list(`l1`).
    2. for each element(`b`) in this adjacency list, check its adjancency list(`l2`).
    3. the common vertices(`c`) in `l1` and `l2` will form a triangle.
    4. these common vertices can be found by **bitmasking** the **adjacency lists `l1` and `l2`** and counting the set bits of the **bitwise and** of these masks.
    5. for each vertex, all masks would be declared of the form: `bitset<2001>bs;`
        ```cpp
        /*
        lets say for convenience, N <= 10
        1 = {2,3,4,7,8}  -> 00110011100
        2 = {1,3,5,7,10} -> 10010101010 , AND = 00010001000, count=2
        ...

        1 = {2,3,4,7,8}  -> 00110011100
        3 = {1,2,4,5}    -> 00000110110, AND = 0000010100, --> triangle (1,2,3) gets counted twice
        ...

        2 = {1,3,5,7,10} -> 10010101010
        3 = {1,2,4,5}    -> 00000110110, AND = 0000000010, --> triangle (1,2,3) gets counted thrice
        ...
        */
        ```
    6. the actual answer would be `SUM/3`, since all triangles would be triple-counted. `(a,b  b,c  a,c)`