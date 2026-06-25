#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>

using namespace std;


class TreeNode{
    public:
        int val;
        TreeNode *left, *right;
    TreeNode(int val){
        this->val = val;
        left = NULL;
        right = NULL;
    }

};

TreeNode *buildTreeFromNotation(string treeAsLine){
    // split on " " and store the node values as strings (with NULLs) in a vector.
    vector<string> arr;
    size_t start = 0;
    while(true) {
        size_t pos = treeAsLine.find(' ', start);
        if (pos == string::npos) {
            string val = treeAsLine.substr(start);
            arr.push_back(val);
            break;
        }
        string val = treeAsLine.substr(start, pos-start);
        arr.push_back(val);
        start = pos + 1; // move to the character right of the space.
        
    }

    // empty tree
    if (arr.size() == 0 || arr[0] == "N") return NULL;

    // now create tree from the constructed vector
    TreeNode *root = new TreeNode(stoi(arr[0]));
    int idx = 0, sz = arr.size();
    queue<TreeNode*> treeQ;treeQ.push(root);
    while(!treeQ.empty()){
        TreeNode *par = treeQ.front();treeQ.pop();
        
        int extraIndex = 1;
        while(extraIndex <= 2) {
            int advancedIdx = extraIndex + idx;
            if (advancedIdx < sz && arr[advancedIdx] != "N") {
                int val = stoi(arr[advancedIdx]);
                TreeNode *child = new TreeNode(val);
                if (extraIndex == 1) par->left = child;
                else par->right = child;

                treeQ.push(child);
            }
            extraIndex++;
        }
        idx += 2;
    }
    return root;
}


void preOrderTraversalRecursive(TreeNode *root){
    if (!root) return;

    cout << root->val << endl;
    preOrderTraversalRecursive(root->left);
    preOrderTraversalRecursive(root->right);
}

void preOrderTraversalIterative(TreeNode *root){
    if (!root) return;

    stack<TreeNode*> preOrder;
    preOrder.push(root);
    while(!preOrder.empty()){
        TreeNode *curr = preOrder.top();preOrder.pop();
        cout << curr-> val << endl;
        if (curr->right) preOrder.push(curr->right);
        if (curr->left) preOrder.push(curr->left);
    }
    return;
    
}

void preOrderTraversal(TreeNode *root, bool isRecursive) {
    if(isRecursive) {
        preOrderTraversalRecursive(root);
        return;
    }
    preOrderTraversalIterative(root);
}

void inOrderTraversalRecursive(TreeNode *root){
    if (!root) return;

    inOrderTraversalRecursive(root->left);
    cout << root->val << endl;
    inOrderTraversalRecursive(root->right);
}

void inOrderTraversalIterative(TreeNode *root){
    if (!root) return;

    stack<TreeNode*> inOrder;
    TreeNode *curr = root;
    while(curr || !inOrder.empty()){
        // add all left nodes
        while(curr){
            inOrder.push(curr);
            curr = curr->left;
        }
        TreeNode *curr = inOrder.top();inOrder.pop();
        cout << curr->val << endl;
        curr = curr->right;
    }
    return;
    
}

void inOrderTraversal(TreeNode *root, bool isRecursive) {
    if(isRecursive) {
        inOrderTraversalRecursive(root);
        return;
    }
    inOrderTraversalIterative(root);
}

void postOrderTraversalRecursive(TreeNode *root){
    if (!root) return;

    postOrderTraversalRecursive(root->left);
    postOrderTraversalRecursive(root->right);
    cout << root->val << endl;
}

void postOrderTraversalIterative(TreeNode *root){
    if (!root) return;

    stack<TreeNode*> postOrder;
    TreeNode *curr = root, *prev = NULL;
    while(curr || !postOrder.empty()){
        while(curr){
            postOrder.push(curr);
            curr = curr->left;
        }
        curr = postOrder.top();
        if (curr->right && prev != curr->right) {
            curr = curr->right;
        }
        else{
            // either curr->right doesn't exist, and curr->left subtree has already been processed,
            // OR curr->right exists and prev == curr->right means the previous 
            // iteration was processing the complete right-subtree under curr
            cout << curr->val << endl;
            prev = curr; // the subtree rooted at curr is also done processing, 
            // and this needs to be told to curr's parent node.
            postOrder.pop();
            curr = NULL; // to ensure loop-exit only depends upon postOrder emptyness.
        }
    }
    return;
    
}

void postOrderTraversal(TreeNode *root, bool isRecursive) {
    if(isRecursive) {
        postOrderTraversalRecursive(root);
        return;
    }
    postOrderTraversalIterative(root);
}

int main(int argc, char* argv[]){
    bool isRecursive = false, isPre = false, isIn = false, isPost = false;
    for(int i = 1;i < argc;i++){
        string arg = argv[i];
        if (arg == "--recur") isRecursive = true;
        if (arg == "--pre") isPre = true;
        if (arg == "--in") isIn = true;
        if (arg == "--post") isPost = true;
    }
    string line;
    while(getline(cin, line)) {
        // process test case
        cout << "Test case: " << line << endl << endl;
        TreeNode *root = buildTreeFromNotation(line);

        if (isPre) preOrderTraversal(root, isRecursive);
        if (isIn) inOrderTraversal(root, isRecursive);
        if (isPost) postOrderTraversal(root, isRecursive);

        cout << endl << string(80, '=') << endl << endl;
    }
    return 0;
}


/*

1233 x
12311
189
11232
12
4
2
3
1


1233
*/