// Bryan Melo
// Student ID: 20429830
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
	// prints list from head of list
	void Output()
	{
		Node<T>* rover = head;
		while (rover != NULL)
		{
			cout << rover->data << '\t';
			rover = rover->next;
		}
		cout << endl;
	}
	// prints list from tail of list
	void OutputPrevious()
	{
		Node<T>* rover = tail;
		while (rover != NULL)
		{
			cout << rover->data << '\t';
			rover = rover->previous;
		}
		cout << endl;
	}
};

// Stack Class derived from SList
template <typename T>
class Stack : public SList<T> {
	public:
	// Inserts data on top of stack
	void Push(T data) {
		Stack::Prepend(data);
	}
	// Returns and removes item at top of stack
	Node<T>* Pop() {
		Node<T>* deletedNode = this->head;
		this->head = this->head->next;
		Stack::Delete(deletedNode->data);
		return deletedNode;
	}
	// Returns but does not remove item at top of stack
	Node<T>* Peek() {
		return this->head;
	}
	// Returns the number of items in the stack
	int GetLength() {
		return Stack::Count();
	}
};

// Queue Class derived from SList
template <typename T>
class Queue : public SList<T> {
	public:
	// Inserts data at end of the queue
	void Push(T data) {
		Queue::Append(data);
	}
	// Returns and removes item at front of queue
	Node<T>* Pop() {
		Node<T>* deletedNode = this->head;
		this->head = this->head->next;
		Queue::Delete(deletedNode->data);
		return deletedNode;
	}
	// Returns but does not remove item at front of queue
	Node<T>* Peek() {
		return this->head;
	}
	// Returns the number of items in the queue
	int GetLength() {
		return Queue::Count();
	}
};

int main()
{
	Stack<int> myStack;
	Queue<int> myQueue;
	Node<int>* nodeA;

	// Stack
	cout << "\nSTACK AUTOMATED TESTS" << endl;
	cout << "=====================" << endl;
	myStack.Push(1);	// Testing Push function
	myStack.Push(2);
	myStack.Push(3);
	cout << "Stack after push: ";
	myStack.Output();

	cout << " Stack after pop: ";
	nodeA = myStack.Pop();		// Testing Pop function
	myStack.Output();
	cout << "    Node deleted: " << nodeA->data << endl;

	if (!myStack.IsEmpty()) {	// Testing Is Empty function
	nodeA = myStack.Peek();		// // Testing Peek function
	cout << "  Executing Peek: " << nodeA->data << endl;
	}

	cout << "\nChecking if Stack is empty..." << endl;
	if (myStack.IsEmpty()) {	// // Testing Is Empty function
		cout << "Stack is empty" << endl;
	}
	else {
		cout << "Stack is not empty" << endl;
	}
	cout << "Stack lenght: " << myStack.GetLength() << endl;	// Testing Get Length function

	// Additional tests
	cout << "\nTesting if Stack was empty" << endl;
	cout << "--------------------------" << endl;
	cout << "Stack after two pops: ";
	myStack.Pop();
	nodeA = myStack.Pop();
	myStack.Output();
	cout << "Nodes deleted: " << nodeA->previous->data << " and " << nodeA->data << endl;

	cout << "Checking if Stack is empty..." << endl;
	if (myStack.IsEmpty()) {
		cout << "Stack is empty" << endl;
	}
	else {
		cout << "Stack is not empty" << endl;
	}
	cout << "Stack lenght: " << myStack.GetLength() << endl;


	// Queue
	cout << "\n\nQUEUE AUTOMATED TESTS" << endl;
	cout << "=====================" << endl;
	myQueue.Push(1);			// Testing Push function
	myQueue.Push(2);
	myQueue.Push(3);
	cout << "Queue after push: ";
	myQueue.Output();

	cout << " Queue after pop: ";
	nodeA = myQueue.Pop();		// Testing Pop function
	myQueue.Output();
	cout << "    Node deleted: " << nodeA->data << endl;

	if (!myQueue.IsEmpty()) {	// Testing Is Empty function
	nodeA = myQueue.Peek();		// Testing Peek function
	cout << "  Executing Peek: " << nodeA->data << endl;
	}

	cout << "\nChecking if Queue is empty..." << endl;
	if (myQueue.IsEmpty()) {	// Testing Is Empty function
		cout << "Queue is empty" << endl;
	}
	else {
		cout << "Queue is not empty" << endl;
	}
	cout << "Queue lenght: " << myQueue.GetLength() << endl << endl;	// Testing Get Length fucntion

	// Additional tests
	cout << "Testing if Queue was empty" << endl;
	cout << "--------------------------" << endl;
	cout << "Queue after two pops: ";
	myQueue.Pop();
	nodeA = myQueue.Pop();
	myQueue.Output();
	cout << "Nodes deleted: " << nodeA->previous->data << " and " << nodeA->data << endl;

	cout << "Checking if Queue is empty..." << endl;
	if (myQueue.IsEmpty()) {
		cout << "Queue is empty" << endl;
	}
	else {
		cout << "Queue is not empty" << endl;
	}
	cout << "Queue lenght: " << myQueue.GetLength() << endl << endl;

	return 0;
}

// Doubly-linked automated tests
/*
	// Doubly-linked list
	SList<int> list;
	
	cout << "\nDOUBLY-LINKED LIST AUTOMATED TESTES" << endl;
	cout << "===================================" << endl;
	list.Append(1);
	list.Append(2);
	list.Append(3);
	cout << "List after Append: ";
	list.Output();

	list.Prepend(4);
	list.Prepend(5);
    cout << "List after Prepend: ";
	list.Output();

	int n = 10;
	cout << "Inserting " << n << " after 1..." << endl;
	list.InsertAfter(1, n);
	list.Output();

	n = 9;
	cout << "Inserting " << n << " before 2..." << endl;
	list.InsertBefore(2, n);
	list.Output();

	cout << "Removing 2 from list:\n";
	list.Delete(2);
	list.Output();

	cout << "Printing list using 'previous' pointer..." << endl;
	list.OutputPrevious();

	n = 10;
	nodeA = list.Search(n);
	cout << "\nSearching for " << n << "...\n";
	if (nodeA != NULL && nodeA->data == n) {
		cout << nodeA->data << " was found" << endl;
	}
	else {
		cout << n << " was not found" << endl;
	}
	
	cout << "Doubly-linked list length: " << list.Count() << endl;

	if (!list.IsEmpty()) {
		cout << "Doubly-linked list is not empty" << endl << endl;
	}
	else {
		cout << "Doubly-linked list is empty." << endl << endl;
	}
*/
