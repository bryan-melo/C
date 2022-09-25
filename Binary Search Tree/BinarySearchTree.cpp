// Bryan Melo
// Data Structures Summer 2021
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

template <typename T>
class TreeNode
{
public:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
    TreeNode<T> () { left = NULL; right = NULL; data = 0; }
    TreeNode<T> (T t) { left = NULL; right = NULL; data = t; }
};

template <typename T>
class BinarySearchTree
{
public:
    TreeNode<T>* root;
    int level;
    BinarySearchTree () { root = NULL; }
    void insert(TreeNode<T>* newNode) 
    {
        level = 0;
        cout << "\n-->insert: " << newNode->data << endl;
        // Check if tree is empty at root
        if (root == NULL) 
        {
            root = newNode;
            cout << " @ level: " << level << endl;
            return;
        }
        else
        {
            TreeNode<T>* pCurr = root;
            while (pCurr) {
                // If Less than (Left)
                if (newNode->data < pCurr->data) 
                {
                    // If left is empty, assign pCurr
                    if (pCurr->left == NULL) 
                    {
                        cout << " Left  <<< " << newNode->data << endl;
                        pCurr->left = newNode;
                        pCurr = NULL;
                        level++; 
                        cout << " @ level: " << level << endl;
                    }
                    else 
                    {
                        // If not empty, go down a level and repeat
                        pCurr = pCurr->left;
                        level++;
                        cout << " Left  <<< " << pCurr->data << endl;
                    }  
                }
                else 
                {
                    // Else greater than (right)
                    // If right is empty, assing pCurr
                    if (pCurr->right == NULL) 
                    {
                        cout << " Right >>> " << newNode->data << endl;
                        pCurr->right = newNode;
                        pCurr = NULL;
                        level++;
                        cout << " @ level: " << level << endl;
                    }
                    else 
                    {
                        // If not empty, go down a level and repeat
                        pCurr = pCurr->right;
                        level++;
                        cout << " Right >>> " << pCurr->data << endl;
                    }
                }
            }
        }
    }
    // Search for function in Tree
    TreeNode<T>* search(T find) 
    {
        TreeNode<T>* pCurr = root;
        int n = 0;
        cout << "\nSearch: " << find << endl;
        while (pCurr) {
            // Return if found at root
            if (pCurr->data == find) {
                n = levelPos(pCurr);
                cout << "Found @ level " << n << endl;
                return pCurr;
            }
            // If NOT, check if key is on the left side
            else if (find < pCurr->data) {
                pCurr = pCurr->left;
                cout << "Left <<<" << endl;
            }
            // Else check if key is on the right side
            else {
                pCurr = pCurr->right;
                cout << ">>> Right" << endl;
            }
        }
        // Return 0 if key was not found
        cout << "Not found" << endl;
        return NULL;
    }
    // Find level of Node
    int levelPos(TreeNode<T>* x) 
	{
        TreeNode<T>* pCurr = root;
        int pos = 0;
        while (pCurr) {
            if (pCurr->data == x->data) {
                return pos;
            }
            else if (x->data < pCurr->data) {
                pCurr = pCurr->left;
                pos++;
            }
            else {
                pCurr = pCurr->right;
                pos++;
            }
        }
        // If not found
        return 0;
	}
    void printTree() 
    {
        queue <TreeNode<T>*> treeQ;
        treeQ.push(root);   // Start at root
        while(!treeQ.empty()) 
        {
            level = 0;
            queue <TreeNode<T>*> next;  // Go through levels  
            while(!treeQ.empty()) 
            {
                TreeNode<T> *pCurr = treeQ.front();     // Start at front of queue
                treeQ.pop();
                if (pCurr != NULL) {
                    cout << pCurr->data << " ";
                    next.push(pCurr->left);
                    next.push(pCurr->right);
                    if(pCurr->left != NULL) 
                        level++;
                    if(pCurr->right != NULL) 
                        level++;
                } 
                else {
                    cout << "- ";   // "-" for every null posistion
                    next.push(NULL);
                    next.push(NULL);
                }
            }
            // End of level
            cout << "|" << endl;
            treeQ = next;
            if(level == 0)
                return;
        }
    }
};

int main () {
    BinarySearchTree<int> tree;
    cout << "\nTesting Insert" << endl;
    cout << "--------------" << endl;
    for (int i = 0; i < 10; i++) {
        tree.insert(new TreeNode<int>(rand() % 100 + 1));
    }
    cout << "\n\nTesting Search" << endl;
    cout << "--------------" << endl;
    TreeNode<int>* test;
    test = tree.search(24);
    test = tree.search(20);

    cout << "\nInorder" << endl;
    tree.printTree();
}