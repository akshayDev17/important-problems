#include<iostream>
#include<vector>
#include<queue>
#include<string>

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

TreeNode *buildTreeFromArr(vector<int> arr){
    // index i is parent of 2*i+1 and 2*i+2 ==> heap logic
    int N = arr.size();
    TreeNode *root = new TreeNode(arr[0]);
    
    // store the current node to process, and this trio: 
    queue<pair<int, TreeNode*> > treeQ;
    
    treeQ.push(pair<int, TreeNode*> (0, root));
    while(!treeQ.empty()){
        pair<int,TreeNode*> currTop = treeQ.front();treeQ.pop();
        int currIdx = currTop.first;
        TreeNode *currPar = currTop.second;

        int right_idx = 2*currIdx + 2,left_idx = 2*currIdx + 1;
        if (left_idx < N) {
            // create left node and attach to current parent node
            TreeNode *left = new TreeNode(arr[left_idx]);
            currPar->left = left;
            treeQ.push(pair<int,TreeNode*>(left_idx, left));
        }
        if (right_idx < N) {
            // create right node and attach to current parent node
            TreeNode *right = new TreeNode(arr[right_idx]);
            currPar->right = right;
            treeQ.push(pair<int,TreeNode*>(right_idx, right));
        }
    }
    return root;
}

TreeNode *buildTreeFromNotationUtil(vector<string> nodeVals){
    // index i is parent of 2*i+1 and 2*i+2 ==> heap logic
    int N = nodeVals.size();
    TreeNode *root = new TreeNode(stoi(nodeVals[0]));
    
    // store the current node to process, and this trio: 
    queue<TreeNode*> treeQ;
    int idx = 0;
    
    treeQ.push(root);
    while(!treeQ.empty()){
        TreeNode *currPar = treeQ.front();treeQ.pop();

        int extraIndex = 1;
        while(extraIndex <= 2) {
            idx++;
            if (idx < N && nodeVals[idx] != "N") {
                TreeNode *child = new TreeNode(stoi(nodeVals[idx]));
                if (extraIndex == 1) currPar->left = child;
                else currPar->right = child;
                treeQ.push(child);
            }
            extraIndex++;
        }
    }
    return root;
}

int subtreeWidth(TreeNode *root){
    if(!root) return 0;
    if (!root->left && !root->right) return std::to_string(root->val).length();

    int leftSubtreeWidth = subtreeWidth(root->left);
    int rightSubtreeWidth = subtreeWidth(root->right);
    int digits = std::to_string(root->val).length();

    // // pipe style of print
    // if (leftSubtreeWidth == 0 || rightSubtreeWidth == 0) {
    //     return max(digits, leftSubtreeWidth + rightSubtreeWidth);
    // }
    // return leftSubtreeWidth + digits + rightSubtreeWidth + 2;

    // back and front slash style of print
    return leftSubtreeWidth + digits + rightSubtreeWidth + 2;
}

void printTree(TreeNode *root, bool debug){
    // go `depth` levels down and then start printing
    // print left subtree as is, print the right subtree starting with a ' '*leftPad space-padding
    
    if (!root || (!root->left && !root->right)) return;

    // store the current node to process, and this quatro: 
    // 1. padding required for the current subtree
    // 2. depth of the current node
    // 3. is current node a right-node (right will have the pad space filled with hyphens instead of spaces)
    // 4. parent node terminal index
    queue<pair<TreeNode*, vector<int> > > treeQ;
    
    vector<int> initVals(4, 0); // 0, 0, 0, 0

    treeQ.push(pair<TreeNode*,vector<int> >(root, initVals));

    int lastDepth = 0, currDepthCursorPos = 0;

    queue<int> connectorCharPosQ;

    while(!treeQ.empty()){
        pair<TreeNode*,vector<int> > top = treeQ.front();treeQ.pop();
        TreeNode *currPar = top.first;
        vector<int> currParVals = top.second;
        int treePad = currParVals[0];
        int depth = currParVals[1];
        int isParRightNode = currParVals[2];
        int parTerminalIdx = currParVals[3];


        int leftSubtreeWidth = subtreeWidth(currPar->left);
        int rightSubtreeWidth = subtreeWidth(currPar->right);

        // currPar->val to be centered between (leftSubtreeWidth + rightSubtreeWidth) / 2
        int digits = std::to_string(currPar->val).length();
        
        // // print using pipe
        // int startPos = (leftSubtreeWidth == 0 || rightSubtreeWidth == 0) ? 0 : leftSubtreeWidth+1;

        // print using slash
        int startPos = leftSubtreeWidth+1;
        
        if (lastDepth != depth){
            // pipe's to be printed at a newline.
            cout << endl;

            // check if connectorCharPosQ has anything, if yes, empty all and print those first.
            int cursor = 0;
            char connectorChar = isParRightNode ? '\\'  : '/';
            // while(!connectorCharPosQ.empty()){
            //     int pipeCharPos = connectorCharPosQ.front();connectorCharPosQ.pop();

            //     if (!debug) cout << string(pipeCharPos - cursor, ' ') << connectorChar;
            //     cursor = pipeCharPos + 1;
            // }

            // depth changed, we are at child level
            cout << endl;

            lastDepth = depth;
            currDepthCursorPos = 0;
        }

        // print root between its right and left blocks(subtrees)
        if (!debug) cout << string(startPos + treePad - currDepthCursorPos, ' ') << currPar->val;

        // store position of current root in order to later on print pipes below it.
        // push the ABSOLUTE column (startPos + treePad), not the gap: 
        // the pipe row tracks its own running cursor, so subtracting 
        // currDepthCursorPos here would double-count the spacing already 
        // consumed by earlier pipes.
        if (currPar->left || currPar->right) connectorCharPosQ.push(startPos + treePad);

        // // DEBUG: print this to know what happens.
        if (debug) cout << "processing node " << currPar->val << " with startPos = " << startPos << ", currDepthCursorPos = " << currDepthCursorPos << ", no. of preceding spaces = " << startPos + treePad - currDepthCursorPos << ", leftSubtreeWidth = " << leftSubtreeWidth << ", rightSubtreeWidth = " << rightSubtreeWidth << ", treePad = " << treePad <<  ", digits = " << digits << ", depth = " << depth << ", lastDepth = " << lastDepth << endl;

        currDepthCursorPos = startPos + treePad + digits;

        // add children to the queue, only the right subtree has a padding from the left.
        // we get to add the dashes only if the parent node's both children exist
        int leftExists = 0;
        if (currPar->left) {
            vector<int> newVals(4, -1);
            newVals[0] = treePad;
            newVals[1] = depth+1;
            newVals[2] = 0;
            newVals[3] = currDepthCursorPos - digits;
            newVals.insert(newVals.end(), );
            newVals.insert(newVals.end(), 0);
            treeQ.push(pair<TreeNode*,vector<int> >(currPar->left, newVals));

            leftExists = 1; // only if a node's left child exist will the right 
            // child shall be allowed to print the hyphens, otherwise there's 
            // no point in connecting the nodes as they belong to different 
            // parent nodes.
        }
        if (currPar->right) {
            vector<int> newVals;
            // // pipe based printing
            // int extraPad = (leftSubtreeWidth == 0 || rightSubtreeWidth == 0) ? 0 : 2 + digits;

            // slash based printing
            int leftPad = (leftSubtreeWidth == 0) ? 0 : 1+leftSubtreeWidth;
            int extraPad = leftPad + 1 + digits;
            newVals.insert(newVals.end(), treePad + extraPad );
            newVals.insert(newVals.end(), depth+1);
            newVals.insert(newVals.end(), leftExists);
            treeQ.push(pair<TreeNode*,vector<int> >(currPar->right, newVals));
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // run ./a.out to run in normal mode
    // run `./a.out --debug` to run in debug mode

    bool debug = false;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--debug") {
            debug = true;
        }
    }

    // vector<int> arr;
    // // for(int i=11;i<=27 ;i++) arr.insert(arr.end(), i);
    // for(int i=1;i<=7 ;i++) arr.insert(arr.end(), i);

    // TreeNode *root = buildTreeFromArr(arr);
    // printTree(root);

    string line;

    while (getline(cin, line)) {

        // process test case
        cout << "Test case: " << line << endl << endl;

        vector<string> treeVals;
        size_t start = 0;
        while(true){
            size_t pos = line.find(' ', start);
            if (pos == string::npos) {
                string last = line.substr(start);
                treeVals.push_back(last);
                break;
            }
            string curr = line.substr(start, pos - start);
            treeVals.push_back(curr);
            start = pos + 1;
        }
        TreeNode *root = buildTreeFromNotationUtil(treeVals);
        printTree(root, debug);

        cout << "\n" << string(80, '=')  << "\n\n";
    }

    return 0;
}
/*
    ________________1___
   /                    \
  2                      3
 /                        \
4                          7
 \                        /
  12                    14
    \                  /
     11232          432
          \
           189
          /   \
      1233     12311


                               _1_
                              /   \
   __________________________2     3
  /
 4                                          7
  \
   12                                   14
     \
      11232____                      432
               \
                189_
                /   \
            1233     12311
*/