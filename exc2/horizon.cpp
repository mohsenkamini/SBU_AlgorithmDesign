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
        //rightResultsNodes.push_back(root);
    }

    // Function to insert a value into the BST given the value, parent value, and direction
    void insert(int value, int parentValue, char direction) {
        if (root == nullptr) {
            root = new TreeNode(value);
            leftnessBorder=0;
            rightnessBorder=0;
            return;
        }

        TreeNode* parent = findNode(root, parentValue);
        if (parent == nullptr) {
            cout << "Parent node not found!" << endl;
            return;
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
            return;
        }
        // check the subtreeFamily again.
        if (parent->subtreeFamily == 'L' ) {
            new_node->subtreeFamily='L';
        } else if (parent->subtreeFamily == 'R' ) {
            new_node->subtreeFamily='R';
        }
    }
    void handleLeftResults(TreeNode* node) {
    //void handleLeftnessVectors() {
        int index = node->leftness-node->rightness;
        if (index >= leftResultsNodes.size()) {
            leftResultsNodes.push_back(node);
            return;
        }

        if (leftResultsNodes[index]->rightness > node->rightness) {
            leftResultsNodes[index]=node;
        } else if (leftResultsNodes[index]->rightness == node->rightness) { 
            if (leftResultsNodes[index]->subtreeFamily == 'R')
                leftResultsNodes[index]=node;
        }
    }

    void handleRightResults(TreeNode* node) {
        int index = node->rightness-node->leftness;
        if (index >= rightResultsNodes.size()) {
            rightResultsNodes.push_back(node);
            return;
        } 

        if (rightResultsNodes[index]->leftness > node->leftness) {
            rightResultsNodes[index]=node;
        } else if (rightResultsNodes[index]->leftness == node->leftness) { 
            if (rightResultsNodes[index]->subtreeFamily == 'L')
                rightResultsNodes[index]=node;
        }
    }
    // Helper function for inorder traversal
    void inorderHelper(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        inorderHelper(node->left);
        cout << node->val << " ";
        inorderHelper(node->right);
    }

    // Function to perform an inorder traversal of the BST
    void inorderTraversal() {
        inorderHelper(root);
    }

    void printTree() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
    
        int depth = getTreeDepth(root);
        int width = pow(2, depth - 1) * 8; // Updated width to accommodate leftness and rightness values
    
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
                    cout << "(" << setw(2) << curr->leftness << ")" << setw(2) << curr->val << " " << curr->subtreeFamily << "(" << setw(2) << curr->rightness << ")";
                    q.push(curr->left);
                    q.push(curr->right);
                } else {
                    cout << "                  "; // Updated spacing to accommodate leftness and rightness values
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
        for (int i=0; i < rightResultsNodes.size() ; i++)
            cout << rightResultsNodes[i]->val << " ";
    }
};

int main() {

    BST bst(1);

    int n;
    cin >> n;

    int childValue, parentValue;
    char direction;

    for (int i = 1; i < n; i++) {
        cin >> childValue >> parentValue >> direction;
        bst.insert(childValue, parentValue, direction);
    }

    //bst.printTree();
    // bst.handleLeftnessVectors();
    bst.printLeftResults();
    bst.printRightResults();
    return 0;
}