// printTree_claude_code_opus_4.8.cpp
//
// Two things in one file:
//   1. Build a binary tree from level-order test cases (same notation as
//      printTreeTests.txt, e.g. "1 2 3 4 N N 7 ..." where N == null).
//   2. Pretty-print the tree with correct alignment in every case:
//        - both subtrees present
//        - only the right subtree present
//        - only the left subtree present
//
// The renderer is a C++ port of the well-tested "box merge" algorithm used by
// the Python `binarytree` library: each node returns a rendered box plus the
// span of its root, and parents stitch child boxes together with '/' '\' and
// '_' connectors. This makes alignment correct regardless of how wide/lopsided
// the subtrees are.
//
// Written for plain C++98 (the default `g++` on macOS):
//   g++ printTree_claude_code_opus_4.8.cpp -o tree
//   ./tree < printTreeTests.txt          # read test cases from stdin
//   ./tree printTreeTests.txt            # or pass a file path

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// C++98 has no std::to_string.
static string toStr(long v) {
    ostringstream oss;
    oss << v;
    return oss.str();
}

class TreeNode {
public:
    long val;
    TreeNode *left, *right;
    TreeNode(long v) : val(v), left(NULL), right(NULL) {}
};

// -------------------------------------------------------------------------
// 1. Build a tree from level-order tokens, "N" meaning a missing child.
//    Children are only allocated for non-null parents (standard LeetCode
//    serialization), so e.g. "1 2 N 3" attaches 3 under 2, not under a null.
// -------------------------------------------------------------------------
TreeNode *buildTreeFromTokens(const vector<string> &tokens) {
    if (tokens.empty() || tokens[0] == "N" || tokens[0].empty()) return NULL;

    TreeNode *root = new TreeNode(atol(tokens[0].c_str()));
    queue<TreeNode *> q;
    q.push(root);

    size_t i = 1;
    while (!q.empty() && i < tokens.size()) {
        TreeNode *parent = q.front();
        q.pop();

        // left child
        if (i < tokens.size()) {
            if (tokens[i] != "N") {
                parent->left = new TreeNode(atol(tokens[i].c_str()));
                q.push(parent->left);
            }
            i++;
        }
        // right child
        if (i < tokens.size()) {
            if (tokens[i] != "N") {
                parent->right = new TreeNode(atol(tokens[i].c_str()));
                q.push(parent->right);
            }
            i++;
        }
    }
    return root;
}

// -------------------------------------------------------------------------
// 2. Pretty printer.
//
// buildBox returns, for the subtree rooted at `node`:
//   lines      : the rendered block, every line padded to `width`
//   width      : width of the block
//   rootStart  : column where the root's text begins
//   rootEnd    : column where the root's text ends (inclusive)
// -------------------------------------------------------------------------
struct Box {
    vector<string> lines;
    int width;
    int rootStart;
    int rootEnd;
    Box() : width(0), rootStart(0), rootEnd(0) {}
};

Box buildBox(TreeNode *node) {
    if (!node) return Box(); // empty box, width 0

    string line1, line2;
    string repr = toStr(node->val);
    int rootWidth = (int)repr.size();
    int gapSize = rootWidth;

    Box l = buildBox(node->left);
    Box r = buildBox(node->right);

    int newRootStart;

    // Connect to the left sub-box with a '/' rising toward this root.
    if (l.width > 0) {
        int lRoot = (l.rootStart + l.rootEnd) / 2 + 1;
        line1 += string(lRoot + 1, ' ');
        line1 += string(l.width - lRoot, '_');
        line2 += string(lRoot, ' ');
        line2 += '/';
        line2 += string(l.width - lRoot, ' ');
        newRootStart = l.width + 1;
        gapSize += 1;
    } else {
        newRootStart = 0;
    }

    // The root itself.
    line1 += repr;
    line2 += string(rootWidth, ' ');

    // Connect to the right sub-box with a '\' falling toward it.
    if (r.width > 0) {
        int rRoot = (r.rootStart + r.rootEnd) / 2;
        line1 += string(rRoot, '_');
        line1 += string(r.width - rRoot + 1, ' ');
        line2 += string(rRoot, ' ');
        line2 += '\\';
        line2 += string(r.width - rRoot, ' ');
        gapSize += 1;
    }

    int newRootEnd = newRootStart + rootWidth - 1;

    Box result;
    result.lines.push_back(line1);
    result.lines.push_back(line2);

    // Stack the two child boxes side by side under the connector rows.
    string gap(gapSize, ' ');
    int rows = (int)max(l.lines.size(), r.lines.size());
    for (int i = 0; i < rows; i++) {
        string lLine = i < (int)l.lines.size() ? l.lines[i] : string(l.width, ' ');
        string rLine = i < (int)r.lines.size() ? r.lines[i] : string(r.width, ' ');
        result.lines.push_back(lLine + gap + rLine);
    }

    result.width = (int)result.lines[0].size();
    result.rootStart = newRootStart;
    result.rootEnd = newRootEnd;
    return result;
}

void printTree(TreeNode *root) {
    if (!root) {
        cout << "(empty tree)\n";
        return;
    }
    Box box = buildBox(root);
    for (size_t i = 0; i < box.lines.size(); i++) {
        const string &line = box.lines[i];
        // trim trailing spaces so each line is as short as possible
        size_t end = line.find_last_not_of(' ');
        if (end == string::npos) cout << "\n";
        else cout << line.substr(0, end + 1) << "\n";
    }
}

// -------------------------------------------------------------------------
// Driver: split a whitespace-separated line into tokens, build, print.
// -------------------------------------------------------------------------
vector<string> tokenize(const string &line) {
    vector<string> tokens;
    istringstream iss(line);
    string tok;
    while (iss >> tok) tokens.push_back(tok);
    return tokens;
}

int main(int argc, char *argv[]) {
    istream *in = &cin;
    ifstream file;
    if (argc > 1) {
        file.open(argv[1]);
        if (!file) {
            cerr << "Could not open file: " << argv[1] << "\n";
            return 1;
        }
        in = &file;
    }

    string line;
    while (getline(*in, line)) {
        // skip blank lines
        if (line.find_first_not_of(" \t\r\n") == string::npos) continue;

        cout << "Test case: " << line << "\n\n";

        vector<string> tokens = tokenize(line);
        TreeNode *root = buildTreeFromTokens(tokens);
        printTree(root);

        cout << "\n" << string(80, '=') << "\n\n";
    }
    return 0;
}
