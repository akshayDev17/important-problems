#include <iostream>

using namespace std;

class TreeNode{
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(){val = -1;left = NULL;right = NULL;}
	TreeNode(int data){val = data;left = NULL;right = NULL;}
	TreeNode(int data, TreeNode *l, TreeNode *r){val = data;left = l;right = r;}
}

bool isMirror(TreeNode *root1, TreeNode *root2){
	if(!root1 && !root2) return true;

	if(root1 && root1 && root1->val == root2->val){
		return isMirror(root1->left, root2->right) && isMirror(root1->right, root2->left);
	}
	return false;
}

bool isSymmetric(TreeNode *root){
	if(!root) return true;
	if(!(root->left || root->right)) return true;
	return isMirror(root, root);
}

int main(){
	int t;cin >> t;
	while(t--){
		int n;cin >> n;
		TreeNode *root = new TreeNode();
		cout << isSymmetric(root) << endl;
	}
}