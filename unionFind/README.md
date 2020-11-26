# Table of Contents

1. []()





# Implementation-1 : Linear<a name="linear"></a>

1. ```cpp
   // Naive implementation of find
   int find(int parent[], int i)
   {
       if (parent[i] == -1)
           return i;
       return find(parent, parent[i]);
   }
     
   // Naive implementation of union()
   void Union(int parent[], int x, int y)
   {
       int xset = find(parent, x);
       int yset = find(parent, y);
       parent[xset] = yset;
   }
   ```

2. the trees created to represent the various disjoint subset become a linked list, in the worst case scenario.

   ```
   Let there be 4 elements 0, 1, 2, 3
   
   Initially, all elements are single element subsets.
   0 1 2 3 
   
   Do Union(0, 1)
      1   2   3  
     /
    0
   
   Do Union(1, 2)
        2   3   
       /
      1
    /
   0
   
   Do Union(2, 3)
            3    
           /
         2
        /
      1
    /
   0
   ```

   1. the problem with this being that the worst case time complexity for finding the parent becomes linear.







# Implementation-2 : Logarithmic<a name="log"></a>

1. implementation by rank(union by rank)

   1. The idea is to always attach smaller depth tree under the root of the deeper tree.
   2. The term *rank* is preferred instead of height because if path compression technique (we have discussed it below) is used, then *rank* is not always equal to height.

2. hence the size of the tree thus created(to represent each disjoint subset) tends to O(Log n), thus the worst case time complexity to access parent becomes O(Log n)

3. ```
   Initially, all elements are single element subsets.
   0 1 2 3 
   
   Do Union(0, 1)
      1   2   3  
     /
    0
   
   Do Union(1, 2)
      1    3
    /  \
   0    2
   
   Do Union(2, 3)
       1    
    /  |  \
   0   2   3
   ```

4. ```cpp
   int find(std::vector<std::vector<int> > &p, int x){
   	if(p[x][0] != x)
   		p[x][0] = find(p, p[x][0]); // flattening the tree/Path compression step
   	return p[x][0];
   }
   
   void Union(std::vector<std::vector<int> > &p, int x, int y){
   	int xp = find(p, x);
   	int yp = find(p, y);
   	
   	if(p[xp][1] < p[yp][1]){
   		p[xp][0] = yp; // attaching the smaller subtree to the large subtree
   	}
   	else if(p[xp][1] > p[yp][1]){
   		p[yp][0] = xp;
   	}
   	else{
   		p[yp][0] = xp;
   		p[xp][1]++;
   	}
   }
   ```

5. The second optimization to naive method is ***Path Compression***. 

   1. The idea is to flatten the tree when *find()* is called. 
   2. When *find()* is called for an element x, root of the tree is returned(root means `p[x][0] == x`). 
   3. The *find()* operation traverses up from x to find root(`if(p[x][0] != x) p[x][0] = find(p, p[x][0])`) . 
   4. The idea of path compression is to make the found root as parent of x(`p[x][0] = find(p, p[x][0]);`) so that we don’t have to traverse all intermediate nodes again. 
   5. If x is root of a sub-tree, then path (to root) from all nodes under x also compresses<a name="this-1"></a>.

6. ```
   Let the subset {0, 1, .. 9} be represented as below and find() is called
   for element 3.
                 9
            /    |    \  
           4     5      6
        /     \        /  \
       0        3     7    8
               /  \
              1    2  
   
   When find() is called for 3, we traverse up and find 9 as representative
   of this subset. With path compression, we also make 3 as the child of 9 so 
   that when find() is called next time for 1, 2 or 3, the path to root is reduced.
   
                  9
            /    /  \    \
           4    5    6     3 
        /           /  \   /  \
       0           7    8  1   2  
   ```

   1. `3` is the root of the sub-tree `3-->[1,2]`, and on calling find(3) for the first time, the search will terminate when it reaches the root(`p[x][0] == x`) and will thus set parent of `3` to `9`
   2. this will also ensure that when `find(1)` or `find(2)` is called the search jumps to `3` and then `9` is directly returned, without having to travel all the way up to `9`, thus achieving [this](#this-1)

7. The two techniques complement each other. 

8. The time complexity of each operation becomes even smaller than O(Log n). 

9. In fact, amortized time complexity effectively becomes small constant. 