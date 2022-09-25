// Bryan Melo
// Data Structures - Summer 2021
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
class SList {
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
		if (head == NULL) 
			return;
		

		Node<T>* pCurr = Search(data);
		Node<T>* pPrev;
		Node<T>* pAfter; 

		
		if (pCurr != NULL) {	
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
		while (rover != NULL) {
			cout << rover->data << '\t';
			rover = rover->next;
		}
		cout << endl;
	}
	// prints list from tail of list
	void OutputPrevious()
	{
		Node<T>* rover = tail;
		while (rover != NULL) {
			cout << rover->data << '\t';
			rover = rover->previous;
		}
		cout << endl;
	}
    // Get number of digits in a number
	int digits() {
        int n = findMax();         // Find max element in list
		if (n < 10) 
      		return 1;
      
   		int digits = 0;
   		while (n != 0) {
    		digits++;
    		n /= 10;
   		}
  		return digits;
	}
    // Get max value in list
    int findMax() {
        Node<T>* pCurr = head;
        int max = 0;
        while (pCurr != NULL) {
            if (max < pCurr->data) {
                max = pCurr->data;
            }
            pCurr = pCurr->next;
        }
        return max;
    }
	// Radix sort
	void RadixSort() {
        // Create Array of Buckets with positions 0 - 9
        SList<T>* buckets[10];
        for(int i = 0; i < 10; i++) {
            buckets[i] = new SList<T>();
		}
		int digit = digits();	// Get number of max digits	 
		int pow10 = 1;     
		for (int i = 0; i < digit; i++) {
            // Append values to corresponding bucket
			Node<T>* pCurr = head;
			while(pCurr != NULL) {
                int x = pCurr->data;
                buckets[(x / pow10) % 10]->Append(x);	// Append value to corresponding bucket
				Delete(pCurr->data);		// Remove values from originial list
                pCurr = pCurr->next;
            }
			// Copy values back to original list
			for (int i = 0; i < 10; i++) {
				pCurr = buckets[i]->head;
				while (pCurr != NULL) {
					Append(pCurr->data);
					buckets[i]->Delete(pCurr->data);	// Clear values in buckets
					pCurr = pCurr->next;
				}
			}
			cout << "\nRADIX SORT AFTER PASS " << i + 1 << endl;
			Output();		//  Print original list
			pow10 *= 10;
		}
		// Free up each bucket's memory
   		for (int i = 0; i < 10; i++) {
      		delete buckets[i];
		}
	} 
}; 

int main() {
	SList<int> list;
	int count = 100;
   
	for (int i = 0; i < count; i++) {
       int rnumber = rand() % 10000 + 1;
	   list.Append(rnumber);
    }
	cout << "\nORIGINAL LIST" << endl;
	list.Output();

	// Sort and Test
	list.RadixSort();
    cout << "\nFINAL OUTPUT" << endl;
	list.Output();
	
    return 0;
}