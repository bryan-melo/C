// Bryan Melo
// Data Stuctures Summer 2021
#include <iostream>
#include <queue>
#include "ConsoleColor.h"

using namespace std;

template <typename T>
class TreeNode
{
public:   
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T>(T t) { data = t; left = NULL; right = NULL; }
};

template <typename T>
class AVL
{
    TreeNode<T>* root;
public:
    AVL() { root = NULL; }
    TreeNode<T>* getRoot() { return root; }
    void insert(TreeNode<T>* newNode)
    {
        cout  << cyan << newNode->data << " ";
        if (root == NULL)
        {
            root = newNode;
            return;
        }
        else
        {
            TreeNode<T> *pCurr = root;
            while (pCurr)
            {
                if (newNode->data < pCurr->data)
                {
                    if (pCurr->left == NULL)
                    {
                        pCurr->left = newNode;
                        pCurr = NULL;
                    }
                    else
                        pCurr = pCurr->left; 
                }
                else
                {
                    if (pCurr->right == NULL)
                    {
                        pCurr->right = newNode;
                        pCurr = NULL;
                    }
                    else
                        pCurr = pCurr->right; 
                }
            }
        }
    }
    //~~~~~~~~~~~~~~~~~~
    TreeNode<T>* search(T find)
    {
        TreeNode<T> *pCurr = root;
        cout << "\nSearch: " << find << endl;
        while (pCurr)
        {
            if (pCurr->data == find)
            {
                cout << "Found: " << pCurr->data << endl;
                return pCurr;
            }
            else if (find < pCurr->data)
            {
                pCurr = pCurr->left;
                cout << "Left <<<" << endl;
            }
            else
            {
                pCurr = pCurr->right;
                cout << ">>> Right" << endl;
            }
        }
        cout << "Not found" << endl;
        return NULL;
    }
    //~~~~~~~~~~~~~~~~~~
    int height(TreeNode<T>* pCurr)
    {
		if (pCurr != NULL)
		{
			int leftHeight = height(pCurr->left);
			int rightHeight = height(pCurr->right);
			int max_height = max(leftHeight, rightHeight);
            return max_height + 1;
		}
		return 0;
    }
    //~~~~~~~~~~~~~~~~~~
    int getBalance(TreeNode<T>* pCurr) 
    {
        if (pCurr == NULL)
            return 0;
        return height(pCurr->left) - height(pCurr->right);
    }
    //~~~~~~~~~~~~~~~~~~
    TreeNode<T>* rotateLeft(TreeNode<T>* pCurr)
    {
        TreeNode<T>* temp = pCurr->right;
        pCurr->right = temp->left;
        temp->left = balance(pCurr);
        return balance(temp);
    }
    //~~~~~~~~~~~~~~~~~~
    TreeNode<T>* rotateRight(TreeNode<T>* pCurr)
    { 
       TreeNode<T>* temp = pCurr->left;
        pCurr->left = temp->right;
        temp->right = balance(pCurr);
        return balance(temp);
    }
    //~~~~~~~~~~~~~~~~~~
    bool isBalanced(TreeNode<T>* pCurr)
    {
        if (pCurr == NULL)
            return true;

        int left = height(pCurr->left);
        int right = height(pCurr->right);

        return abs(left - right) <= 1 && isBalanced(pCurr->left) && isBalanced(pCurr->right);
    }
    //~~~~~~~~~~~~~~~~~~
    TreeNode<T>* balance(TreeNode<T>* pCurr)
    {
        int bal_factor = getBalance(pCurr);
        if(bal_factor > 1)
        { 
            if(getBalance(pCurr->left) > 0) 
                return rotateRight(pCurr);
            else 
            { 
                pCurr->left = rotateLeft(pCurr->left);
                return rotateRight(pCurr);
            }
        }
        else if(bal_factor < -1)
        { 
            if(getBalance(pCurr->right) < 0)
                return rotateLeft(pCurr);
            else
            { 
                pCurr->right = rotateRight(pCurr->right);
                return rotateLeft(pCurr);
            }
        }
        return root = pCurr;
    }
    //~~~~~~~~~~~~~~~~~~
     TreeNode<T>* balanceTree(TreeNode<T>* pCurr) 
     {
        if (isBalanced(root))
            return NULL;
            
        if(pCurr == NULL) 
            return NULL;

        pCurr->left = balanceTree(pCurr->left);
        pCurr->right = balanceTree(pCurr->right);

        return balance(pCurr); 
    }
    //~~~~~~~~~~~~~~~~~~
    void printTree()
    {
        queue<TreeNode<T> *> treeQ;
        treeQ.push(root);
        while (!treeQ.empty()) 
        {
            int n = 0;
            queue<TreeNode<T> *> next;
            while (!treeQ.empty()) 
            {
                TreeNode<T> *pCurr = treeQ.front();
                treeQ.pop();
                if (pCurr != NULL) 
                {
                    cout << white << pCurr->data << " ";
                    next.push(pCurr->left);
                    next.push(pCurr->right);
                    if (pCurr->left != NULL)
                        n++;
                    if (pCurr->right != NULL)
                        n++;
                }
                else 
                {
                    cout << cyan << "_ ";
                    next.push(NULL);
                    next.push(NULL);
                }
            }
            cout << cyan << "|" << endl;
            treeQ = next;
            if (n == 0)
                return;
        }
    }
};

// Driver Code
int main()
{
    // Test 1 increase - Build Tree 
    AVL<int> tree;
    int num = 1;
    cout << "\nInsert: ";
    for (int i = 0; i < 15; i++)
        tree.insert(new TreeNode<int>(num++));

    // Print Unbalanced Tree
    cout << endl << endl;
    tree.printTree();

    // Balance and Print Balanced Tree
    tree.balanceTree(tree.getRoot());
    cout << endl << endl;
    tree.printTree();
    if (tree.isBalanced(tree.getRoot()))
        cout << "Tree is balanced" << endl << endl;
    else
        cout << "Tree is unbalanced" << endl << endl;

    // Test 2 decrease - Build Tree 
    AVL<int> tree2;
    num = 15;
    cout << white << "\nInsert: ";
    for (int i = 0; i < 15; i++)
        tree2.insert(new TreeNode<int>(num--));

    // Print Unbalanced Tree
    cout << endl << endl;
    tree2.printTree();

    // Balance and Print Balanced Tree
    tree2.balanceTree(tree2.getRoot());
    cout << endl << endl;
    tree2.printTree();
    if (tree2.isBalanced(tree2.getRoot()))
        cout << "Tree is balanced" << endl << endl;
    else
        cout << "Tree is unbalanced" << endl << endl;

    return 0;
}