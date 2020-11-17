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

void mirrorTree(TreeNode *root){
	if(!root) return;
	if(!(root->left || root->right)) return;
	mirrorTree(root->left);
	mirrorTree(root->right);
	TreeNode *temp = root->right;
	root->right = root->left;
	root->left = temp;
	return;
}

int main(){
	int t;cin >> t;
	while(t--){
		int n;cin >> n;
		
	}
}