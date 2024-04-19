#include <iostream>
#include <queue>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

// TreeNode class represents a node in the BST
class TreeNode {
public:
    int val;
    int leftness;
    int rightness;
    char subtreeFamily; // 'L' for left subtree, 'R' for right subtree, 'N' for neutral

    TreeNode* left;
    TreeNode* right;

    TreeNode(int value, int leftness = 0, int rightness = 0, char family = 'N')
        : val(value), leftness(leftness), rightness(rightness), left(nullptr), right(nullptr), subtreeFamily(family) {}
};

// BST class represents the Binary Search Tree
class BST {
private:
    TreeNode* root;
    int leftnessBorder ,rightnessBorder;
    vector<TreeNode*> leftResultsNodes;
    vector<TreeNode*> rightResultsNodes;
public:
    BST(int value) : root(nullptr) {
        root = new TreeNode(value);
        leftnessBorder=0;   
        rightnessBorder=0;
        leftResultsNodes.push_back(root);
        rightResultsNodes.push_back(root);
    }

    // Function to insert a value into the BST given the value, parent value, and direction
    int insert(int value, int parentValue, char direction) {
        if (root == nullptr) {
            root = new TreeNode(value);
            leftnessBorder=0;
            rightnessBorder=0;
            return 0;
        }

        TreeNode* parent = findNode(root, parentValue);
        if (parent == nullptr) {
            cout << "Parent node not found!" << endl;
            return -1;
        }
        
        TreeNode* new_node = nullptr; 

        if (direction == 'L') {
            new_node =  new TreeNode(value, parent->leftness + 1, parent->rightness, 'L');
            parent->left = new_node;
            handleLeftResults(new_node);
        } else if (direction == 'R') { 
            new_node = new TreeNode(value, parent->leftness, parent->rightness + 1, 'R');
            parent->right = new_node;
            handleRightResults(new_node);
        } else {
            cout << "Invalid direction specified!" << endl;
            return -1;
        }
        // check the subtreeFamily again.
        if (parent->subtreeFamily == 'L' ) {
            new_node->subtreeFamily='L';
        } else if (parent->subtreeFamily == 'R' ) {
            new_node->subtreeFamily='R';
        }
        return 0;
    }
    void handleLeftResults(TreeNode* node) {
    //void handleLeftnessVectors() {
        int index = node->leftness-node->rightness;
        int depth = node->rightness+node->leftness;
        
        if (index >= leftResultsNodes.size()) {
            leftResultsNodes.push_back(node);
            return;
        }

        TreeNode* aimedNode = leftResultsNodes[index];
        int aimedNodeDepth = aimedNode->rightness+aimedNode->leftness;

        if (aimedNodeDepth > depth) {
            leftResultsNodes[index]=node;
            return;
        }
        
        if (aimedNodeDepth == depth) { 
            if (aimedNode->subtreeFamily == 'R')
                leftResultsNodes[index]=node;
        }
    }

    void handleRightResults(TreeNode* node) {
        int index = node->rightness-node->leftness;
        int depth = node->rightness+node->leftness;
        
        if (index >= rightResultsNodes.size()) {
            rightResultsNodes.push_back(node);
            return;
        } 
        
        TreeNode* aimedNode = rightResultsNodes[index];
        int aimedNodeDepth = aimedNode->rightness+aimedNode->leftness;

        if (aimedNodeDepth > depth) {
            rightResultsNodes[index]=node;
            return;
        }
        
        if (aimedNodeDepth == depth) { 
            if (aimedNode->subtreeFamily == 'L')
                rightResultsNodes[index]=node;
        }
    }
    void printTree() {
    if (root == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    int depth = getTreeDepth(root);
    int width = pow(2, depth - 1) * 6; // Adjusted width to reduce spacing

    queue<TreeNode*> q;
    q.push(root);

    for (int i = 0; i < depth; i++) {
        int levelSize = pow(2, i);
        int padding = width / (levelSize * 2);

        cout << string(padding, ' ');

        for (int j = 0; j < levelSize; j++) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr != nullptr) {
                cout << "(" << setw(2) << curr->leftness << ")" << setw(2) << curr->val << "(" << setw(2) << curr->rightness << ")"; // Adjusted spacing
                q.push(curr->left);
                q.push(curr->right);
            } else {
                cout << "        "; // Adjusted spacing
                q.push(nullptr);
                q.push(nullptr);
            }

            cout << string(padding * 2 - 1, ' ');
        }

        cout << endl;
    }
}
    // Function to search for a value in the BST
    bool search(int value) {
        TreeNode* curr = root;
        while (curr != nullptr) {
            if (value == curr->val) {
                return true;
            } else if (value < curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return false;
    }

    // Helper function to find a node in the BST given its value
    TreeNode* findNode(TreeNode* node, int value) {
        if (node == nullptr || node->val == value) {
            return node;
        }

        TreeNode* leftResult = findNode(node->left, value);
        if (leftResult != nullptr) {
            return leftResult;
        }

        return findNode(node->right, value);
    }

    // Helper function to calculate the depth of the tree
    int getTreeDepth(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftDepth = getTreeDepth(node->left);
        int rightDepth = getTreeDepth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }
    void printLeftResults() {
        for (int i=leftResultsNodes.size()-1; i >=0  ; i--)
            cout << leftResultsNodes[i]->val << " ";
    }

    void printRightResults() {
        for (int i=1; i < rightResultsNodes.size() ; i++) {
            cout << rightResultsNodes[i]->val;
            if (i!=rightResultsNodes.size()-1)
                cout << " ";
        }
    }
};

int main() {

    BST bst(1);

    int n;
    cin >> n;
    vector<tuple<int, int, char>> leftInstructions;

    int childValue, parentValue;
    char direction;

    for (int i = 1; i < n; i++) {
        cin >> childValue >> parentValue >> direction;
        int status = bst.insert(childValue, parentValue, direction);
        //if  (status == -1)
        //    leftInstructions.push_back(make_tuple(childValue, parentValue, direction));
    }

    //for (const auto& node : leftInstructions) {
    //    int childValue = get<0>(node);
    //    int parentValue = get<1>(node);
    //    char direction = get<2>(node);
    //    //cout << childValue << " " << parentValue << " " << direction << endl;
    //    int status = bst.insert(childValue, parentValue, direction);
    //        if (status == -1)
    //        
    //}


    bst.printTree();
    // bst.handleLeftnessVectors();
    bst.printLeftResults();
    bst.printRightResults();
    return 0;
}