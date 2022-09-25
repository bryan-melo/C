// Bryan Melo
// Data Structures - Summer 2021
#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T>
class Node {
	public:
	T data;
	Node<T>* next;
	Node<T>* previous;
	Node<T>() { next = NULL; previous = NULL; data = 0;  }
	Node<T>(T t) { next = NULL; previous = NULL; data = t; }
};

template <typename T>
class SList
{
	public:
	Node<T>* tail;
	Node<T>* head;
	SList() { head = NULL; tail = NULL; }  // default constructor
	
	// appends to tail of list
	void Append(T data)
	{
		Node<T>* newNode = new Node<T>(data);
		if (head == NULL) {    // If list is empty
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode;
			newNode->previous = tail;
			tail = newNode;
		}
	}
	// prepends to head of list
	void Prepend(T data)
	{
		Node<T>* newNode = new Node<T>(data);
		if (head == NULL) {    // If list is empty
			head = newNode;
			tail = newNode;
		}
		else {
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
		}
	}
	// inserts data after found data
	void InsertAfter(T find, T data)
	{
		Node<T>* newNode = new Node<T>(data);
		Node<T>* pCurr = head;
		Node<T>* nextNode;

		while (pCurr != NULL) {		// Assuming list is not empty
			if (pCurr->data == find && pCurr != tail) {
				// Insert after "find" 
				nextNode = pCurr->next;
				newNode->next = nextNode;
				newNode->previous = pCurr;
				pCurr->next = newNode;
				nextNode->previous = newNode;
			}
			if (pCurr->data == find && pCurr == tail) {    // If inserting after the last node, then update tail
				tail->next = newNode;
				newNode->previous = tail;
				tail = newNode;
			}
			pCurr = pCurr->next;
		}
	}
	// inserts data before found data
	void InsertBefore(T find, T data)
	{
		Node<T>* newNode = new Node<T>(data);
		Node<T>* pCurr = head;
		Node<T>* prevNode;

		while (pCurr != NULL) {    // Assuming list is not empty
			if (pCurr->data == find && pCurr != head) {
				// Insert before "find"
				prevNode = pCurr->previous;
				newNode->next = pCurr;
				newNode->previous = prevNode;
				pCurr->previous = newNode;
				prevNode->next = newNode;
			}
			if (pCurr->data == find && pCurr == head) {    // If inserting before the first node, then update head
				newNode->next = head;
				head->previous = newNode;
				head = newNode;
			}
			pCurr = pCurr->next;
		}
	}	
	// finds data node and returns it
	Node<T>* Search(T data)
	{
		Node<T>* pCurr = head;

		while (pCurr != NULL) {
			if (pCurr->data == data) {
				return pCurr;
			}
			pCurr = pCurr->next;
		}
		return NULL;
	}
	// deletes a node from the list
	void Delete(T data)
	{
		Node<T>* pCurr = head;
		Node<T>* pPrev;
		Node<T>* pAfter; 

		while (pCurr != NULL) {		// Assuming list is not empty
			if (pCurr->data == data) {
				pAfter = pCurr->next;
				pPrev = pCurr->previous;
				if (pAfter != NULL) {
					pAfter->previous = pPrev;
				}
				if (pPrev != NULL) {
					pPrev->next = pAfter;
				}
				if (pCurr == head) {		// Update head if removed from the beginning of list
					head = pAfter;
				}
				if (pCurr == tail) {		// Updata tail if removed from the end of list
					tail = pPrev;
				}
				delete pCurr;		// delete node
			}
			pCurr = pCurr->next;
		}
	}
	// returns number of nodes in list
	int Count()
	{
		Node<T>* data = head;
		int count = 0;

		while (data != NULL) {
			data = data->next;
			count++;
		}
		return count;
	}
	// returns true if list is empty
	bool IsEmpty()
	{
		if (head == NULL) {
			return true;
		}
		return false;
	}
	// prints list by calling Recursive function
	void Output()
	{
		Recursive(tail);
	}

    // Recursive Output Function tail to head
    void RecursiveOut(Node<T> *node) {
        if (node == NULL) {
            return;
        }
        else {
			cout << node->data << '\t';
			RecursiveOut(node->previous);
        }
    }
    // Recursive Output Function head to tail
    void Recursive(Node<T> *node) {
        if (node == NULL) {
            return;
        }
        else {
            Recursive(node->previous);
			cout << node->data << '\t';
			
        }
    }

};

int main() {
    SList<int> list;
	
    cout << "\nAppending 1-5..." << endl;
	list.Append(1);
    list.Append(2);
    list.Append(3);
    list.Append(4);
    list.Append(5);
    cout << "List using Recursive Output fucntion" << endl;
	list.Output();
	cout << endl;

}