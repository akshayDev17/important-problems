# Table Of Contents

1. [Mirror a Binary Tree](#mirror-tree)
   1. [solution](#sol1)
2. [Symmetric Tree](#symmetric-tree)
3. [All Nodes at distance K](#nodes-at-distance-k)





# Mirror a Binary Tree<a name="mirror-tree"></a>

1.  Mirror of a Binary Tree T is another Binary Tree M(T) with left and right children of all non-leaf nodes interchanged.
2. <img src="mirror.gif" />





## Solution<a name="sol1"></a>

1. [CODE](mirrorTree.cpp), [TEST](mirrorTreeTest.txt)
2. Call Mirror for left-subtree
3. Call Mirror for right-subtree
4. Swap left and right subtrees.
5. [geeksforgeeks practice](https://practice.geeksforgeeks.org/problems/mirror-tree/1)





# Symmetric Tree<a name="symmetric-tree"></a>

1. basically check if a tree is a mirror image of itself.
2. check if roots are mirror images
   1. if roots are both NULL, or both have same value, move forward, if not return `false`.
3. return `isMirror(root1->left, root2->right) && isMirror(root1->right, root2->left)`, meaning that 
   1. left subtree of left tree and right subtree of right tree have to be mirror images
   2. right subtree of left tree and left subtree of right tree have to be mirror images
4. [CODE](isSymmetric.cpp)





# All Nodes at distance K<a name="nodes-at-distance-k"></a>

1. We are given a binary tree (with root node `root`), a `target` node, and an integer value `K`.

   Return a list of the values of all nodes that have a distance `K` from the `target` node. The answer can be returned in any order.

2. [Leetcode](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/)

3. **Example 1:**

   ```bash
   Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
   
   Output: [7,4,1]
   
   Explanation: 
   The nodes that are a distance 2 from the target node (with value 5)
   have values 7, 4, and 1.
   
   
   
   Note that the inputs "root" and "target" are actually TreeNodes.
   The descriptions of the inputs above are just serializations of these objects.
   ```

<img src="prob3_1.png" width=300/>





## Solution<a name="sol2"></a>

1. ```cpp
   vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
       unordered_map<TreeNode*,TreeNode*> parent;
       unordered_map<TreeNode*,bool> vis;
       queue<TreeNode*> q;q.push(root);
       while(!q.empty()){
               // annotate parent node of all nodes
           TreeNode *top = q.front();q.pop();
           if(top->left){
               parent[top->left] = top;
               q.push(top->left);
           }
           if(top->right){
               parent[top->right] = top;
               q.push(top->right);
           }
       }
       q.push(target);
       vis[target] = true;
       int count = K;
       while(count){ // capture all nodes at a distance of K in the queue
           int sz = q.size();
           // cout << sz << endl;
           while(sz){
               /* process all the nodes currently in the 
               queue and replace them with their child/parent.*/
               TreeNode *curr = q.front();q.pop();
               if(curr->left && !vis[curr->left]){
                   vis[curr->left] = true;
                   q.push(curr->left);
               }
               if(curr->right && !vis[curr->right]){
                   vis[curr->right] = true;
                   q.push(curr->right);
               }
               if(parent[curr] && !vis[parent[curr]]){
                   vis[parent[curr]] = true;
                   q.push(parent[curr]);
               }
               sz--;
           }
           count--;
           /*
           when count == 0, the queue will contain only nodes at a distance
           of K from target node
           */
       }
       vector<int>  ans;
       while(!q.empty()){ans.push_back(q.front()->val);q.pop();}
       return ans;
   }
   ```

2. as seen above, annotation of parent nodes is used, and it turns out that TreeNode* is serializable.