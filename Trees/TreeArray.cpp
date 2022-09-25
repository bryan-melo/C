
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class TreeNode
{
	public:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
};

template <typename T>
class BinarySearchTree
{
	vector<T> array;
	int size;
public:
	BinarySearchTree(int s) : size(s)
	{
		size = reSize(size);
		array.resize(size);
		for (int x = 0; x < size; x++) 
			array[x] = 0;
	}
	int reSize(int x) 
	{
		int value = pow(x, 2);
		return value;
	}
	void insert(T x) 
	{
		int currentIndex = 0;
		cout << "\n-->insert: " << x << endl;
		while (true) 
		{
			if (array[currentIndex] == 0) 
			{
				array[currentIndex] = x;
				cout << "Inserted @ index: ";
				cout << currentIndex % 2;
				cout << currentIndex << endl;
				break;
			}
			else if (x < array[currentIndex]) 
			{
				currentIndex = (2 * currentIndex + 1);
				cout << " Left <<< " << currentIndex << endl;
			}
			else  
			{
				currentIndex = (2 * currentIndex + 2);
				cout << " Right >>> " << currentIndex << endl;
			}
		}
	}
	void search(T x) 
	{
		cout << "Search: " << x << endl;
		int currentIndex = 0;
		while (true) 
		{
			if (array[currentIndex] == 0) 
			{
				cout << "Not Found" << endl;
				break;
			}
			if (array[currentIndex] == x) 
			{
				cout << "Found at index: " << currentIndex << endl;
				break;
			}
			else if (x < array[currentIndex]) 
			{
				cout << " Left <<< " << endl;
				currentIndex = (2 * currentIndex + 1);
			}
			else 
			{
				cout << " >>> Right " << endl;
				currentIndex = (2 * currentIndex + 2);
			}
		}
	}
	void parent(int x) 
	{
		while (x != 0) 
		{
			x = (x - 1) / 2;
			cout << "---|";
		}
	}
	void inOrder(int currentIndex) 
	{
		if (array[currentIndex] != 0) 
		{
			inOrder(2 * currentIndex + 1);
			parent(currentIndex);
			cout << array[currentIndex] << endl;
			inOrder(2 * currentIndex + 2);
		}
	}
	void preOrder(int currentIndex)
	{
		if (array[currentIndex] != 0)
		{
			parent(currentIndex);
			cout << array[currentIndex] << " " << endl;
			preOrder(2 * currentIndex + 1);
			preOrder(2 * currentIndex + 2);
		}
	}
	void postOrder(int currentIndex) 
	{
		if (array[currentIndex] != 0) 
		{
			postOrder(2 * currentIndex + 1);
			postOrder(2 * currentIndex + 2);
			parent(currentIndex);
			cout << array[currentIndex] << " " << endl;
		}
	}
	void reverseOrder(int currentIndex)
	{
		if (array[currentIndex] != 0)
		{
			reverseOrder(2 * currentIndex + 2);
			parent(currentIndex);
			cout << array[currentIndex] << " " << endl;
			reverseOrder(2 * currentIndex + 1);
		}
	}
	void printArray()
	{
		int exp = 0;
		int sum = int(pow(2, exp));
		int power = sum;
		for (int i = 0; i < size; i++)
		{
			if (i == sum)
			{
				cout << "| " << endl;
				exp++;
				power = int(pow(2, exp));
				sum += power;
			}
			if (array[i])
			{
				(i % 2) ? cout << array[i] << ' ' : cout << array[i] << ' ';
			}
			else
			{
				cout << "- ";
			}
		}
		cout << endl;
	}
};

int main() 
{
	vector<int> varray;
    varray.push_back(42);
	varray.push_back(68);
	varray.push_back(35);
	varray.push_back(1);
	varray.push_back(70);
	varray.push_back(25);
	varray.push_back(79);
	varray.push_back(59);
	varray.push_back(63);
	varray.push_back(65);
	int resize = varray.size() * log(varray.size());
	BinarySearchTree<int> bst(varray.size());
	for (int i = 0; i < varray.size(); i++)
		bst.insert(varray[i]);
	cout << endl;
	cout << "Inorder" << endl;
	bst.inOrder(0);
	cout << "Preorder" << endl;
	bst.preOrder(0);
	cout << "Postorder" << endl;
	bst.postOrder(0);
	cout << "\nSearch" << endl;
	bst.search(16);
	cout << "\nIn memory" << endl;
	bst.printArray();
	bst.reverseOrder(0);
}

/*
Left < Less than
Right > Greater than


	Root
Left	Right
(prev)	(Next)


		  0
	1	     	2
3	   4	5		6




*/