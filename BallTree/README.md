# Table of Contents
1. [Introduction](#intro)
2. [Distance Metrics](#distance_metrics)
    1. [Euclidean](#euclidean)
    2. [Manhattan](#manhattan)
    3. [Chebyshev Distance](#chebyshev)
    4. [Cosine distance](#cosine)
3. [Sklearn's BallTree](#sklearn_balltree)

# Introduction<a name="intro"></a>
- `input`: a list of given points on which to fit the ball tree
- each node of a ball tree represents a ball of points from the given `input` set of points
- a ball tree **node** stores the following:
    - `index_start`
    - `index_end`
        - `input[index_start:index_end]` denotes the points inside this node(ball). 
    - `centroid`: centroid of the points within the node(ball)
    - `radius`: distance of the farthest point from the centroid.
- max possible depth: each leaf node contains a single point from `input` list of points
- pre-pruning(depth limiting) a ball tree
    - no. of points in a leaf node (`node.index_end - node.index_start + 1`) should meet a minimum threshold `leaf_size`
    - radius of a leaf node should meet a minimum `radius_threshold`
- hence, a ball tree stores the following
    - `leaf_size`
    - `radius_threshold`
    - `pt_idx_arr`: stores the indices of each point provided in the `input` set of points 
- starting at the root node,
    - `root_node.index_start = 0, root_node.index_end = n-1`
    - find `root_node.centroid`, and `root_node.radius`
    - threshold criterion check
        - `root_node.end - root_node.start + 1 > ballTree.leaf_size`
        - `root_node.radius > ballTree.radius_threshold`
    - split if check passes, else mark the node as a leaf node.
    - split: 2 methods of split, 2-means clustering or furthest distance based clustering
        - **2-means clustering**
            - perform a kmeans clustering, k = 2
            - w.r.t. the 2 clusters formed, their centroids will be the left and right child of the root node, and the cluster members(points) will be the points that land up in the respective child nodes.
            - reshuffle the `pt_idx_arr` s.t. indices of all points belonging to the left-child cluster are in the first segment of the array, and the indices of the other cluster on the remaining portion of the array
                - for instance, say `pt_idx_arr = [0 1 2 3 4 5 6 7 8 9]`, s.t. left-cluster indices = `[1,4,7,8]`, right-cluster indices = `[0,2,3,5,6,9]`
                - after reshuffling, `pt_idx_arr = [1,4,7,8,0,2,3,5,6,9]`, s.t. `left_child.index_start = 0, left_child.index_end=3, right_child.index_start = 4, right_child.index_end=9`
            - post reshuffling, compute the centroids and radii of both balls formed.
        - **distance-based clustering**
            - randomly pick a point in the current node(ball) --> `p1`
            - find the point in the current node(ball) furthest from `p1` ---> `p2`
            - find distance of all points in the current node from `p1` and `p2`, and assign them to either `p1` or `p2` depending upon which is closer.
            - `p1`: left-child, `p2`: right-child
            - reshuffle `pt_idx_arr` as done in 2-means clustering
            - post reshuffling, compute the centroids and radii of both balls formed.
            - *slight modification*
                - lets call the first randomly picked point `p'`, and the point furthest from this point as `p1`
                - find the point furthest from `p1` in the current node --> `p2`
                - `p1`: left-child, `p2`: right-child, and follow the same reshuffling + centroid + radius computation steps.
                - <font color="red">check change in performance due to this modification</font>
- repeat the above steps for each node recursively till pre-pruning criteria is hit.

# Distance metrics<a name="distance_metrics"></a>
## Euclidean<a name="euclidean"></a>
- the go-to metric for any vector-distance related calculations
- <font color="maroon">Cons:</font> points that are quite close but are represented by high-dimensional vectors tend to have a higher euclidean distance
    - this is because the no. of terms(squares) that add up to form the Euclidean distance increase, and all these terms are non-negative.
    - thus increasing the *usually observed* Euclidean distance value

## Manhattan<a name="manhattan"></a>
- $L_1 \textrm{ norm } (\vec{x} - \vec{y}) = |\vec{x} - \vec{y}|_1 = \sum\limits_{i=1}^d |x_i - y_i|$
- an advantage over Euclidean: no squaring of terms, hence *theoretical lesser* requirement of memory(since a smaller number will be produced) and less computation(absence of the multiplication op.) 
    - absolute value is just chucking off the sign bit
- <font color="maroon">Cons:</font> suffers from the same problem as Euclidean

## Chebyshev Distance<a name="chebyshev"></a>
- $max.(x_i - y_i) \, , \, \forall \, i \, \epsilon \, \left[1,2,\cdots , d\right]$
- easy to compute
- <font color="maroon">Cons:</font> shit when vectors are sparse or 

## Cosine distance<a name="cosine"></a>
- $1 - \dfrac{\vec{u}.\vec{v}}{|\vec{u}|.|\vec{v}|}$, where the latter term is the cosine similarity term.
- since numbers being added to form the dot product can have opposite signs, the no. of terms being added, i.e. vector-dimensionality doesn't affect this metric unlike Euclidean distance.
- usually suited for higher dimensional points(vectors)

# Sklearn's BallTree<a name="sklearn_balltree"></a>
- based on creating 