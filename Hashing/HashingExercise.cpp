// Bryan Melo
// Data Structures - Summer 2021
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Customer 
{
public:
    string lastname;
    string firstname;
    string id;
	Customer() { lastname = ""; firstname = ""; id = ""; }
	Customer(string lName, string fName, string ID) { 
		lastname = lName; 
		firstname = fName; 
		id = ID; 
	}
};

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
class DList {
	public:
	Node<T>* tail;
	Node<T>* head;
	DList() { head = NULL; tail = NULL; }  // default constructor
	
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
		while (rover != NULL) {
			cout << rover->data << " -> ";
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
}; 

template <typename T>
class DynamicArray
{
	protected:
		DList<Customer>* list;
		T* base;
		int isize = 0;
		int capacity = 0;
	public:
		DynamicArray(int c = 10) : capacity(c) 
		{
			allocate(capacity);
		}
		DynamicArray(T t, int c) : capacity(c) 
		{
			allocate(capacity);
			for (int i = 0; i < capacity; i++) {
				base[i] = t;
			}
		}
		void set(DList<Customer> v, int offset) 
		{
			if (offset >= capacity)
				resize(capacity * 2);
			base[offset] = v;
			isize++;
		}
		T get(int offset) { return base[offset]; }
		int size() { return isize; }
		T begin() { return base[0]; }
		T end() { return base[isize - 1]; }
		void push(T t) { set(t , isize); }
		void pop(int index) 
		{
			for (int i = index; i < isize - 1; isize++)
				base[i] = base[i + 1];
			isize--; 
		}
		void allocate(int c) 
		{
			capacity = c;
			base = new T[capacity];
		}
		void resize(int nusize) 
		{
			capacity = nusize;
			T* temp = new T[nusize];
			for (int i = 0; i < isize; i++) 
				temp[i] = base[i];
			delete [] base;
			base = temp;
		}
		void clear() 
		{
			delete [] base;
			isize = 0;
			allocate(capacity);
		}
		T& operator[](int index) { return base[index]; }
		void Output(int index) 
		{
			DList<Customer> pCurr = base[index];
			while (pCurr.head != NULL) {
				cout << pCurr.head->data.firstname;
				cout << " " << pCurr.head->data.lastname;
				pCurr.head = pCurr.head->next;
			}

		}
};

const unsigned TABLE_SIZE = 512;
static int maximum = TABLE_SIZE;

int OddEven(string key) 
{
	int sum = key[0];
	for (int c = 1; c < key.length(); c++) {
		if (c % 2 == 1)
			sum += key[c] * 3;
		else 
			sum += key[c] * 2;
	}
	return sum;
}

int HashMultiplicative(string key)
{
	int sum = OddEven(key);
	float knum = sum * 0.693;
	float remainder = knum - int(knum);
	int hash = int(remainder * 255.0) % TABLE_SIZE;
	return hash;
}

int HashMidSquare(string key)
{
	int sum = OddEven(key);
	int squaredKey = sum * sum;
	string snumber = to_string(squaredKey);
	string smid = "";
	for (int i = 1; i < snumber.size() - 1; i++)
		smid += snumber[i];
	int midnumber = stoi(smid);
	return midnumber % 400;
}

int HashDivisionMethod(string key)
{
	int sum = OddEven(key);
	return sum % 400;
}

// a good hashing function returns few collisions
int getHash(string key)
{
	// return HashMultiplicative(key);
	// return HashMidSquare(key);
	return HashDivisionMethod(key);
}

int hashfunc(string a, int tablesize) {
    int sum=0;
    for (unsigned int pos=0; pos<a.length(); pos++) {
        sum += int(a[pos]); // getting ordinal values, and using positional values to weight them
        //adding them up, and using the remainder method to get a hash value.
    }

    return sum%tablesize;
}


int main() {
	DynamicArray<DList<Customer> > table(TABLE_SIZE);
	Customer* customers = new Customer[TABLE_SIZE];
	DList<Customer>* list = new DList<Customer>[TABLE_SIZE];

	ifstream file("Customer.csv");
	string lastname, firstname, id, line;
	int i = 0;
	while(getline(file, line)) 
	{
		stringstream temp(line);
		getline(temp, lastname, ',');
		getline(temp, firstname, ',');
		temp >> id;
		customers[i] = Customer(lastname, firstname, id);
		int n = 0;
		n = getHash(customers[i].lastname + customers[i].firstname + customers[i].id);
		list[n].Append(customers[i]);
		i++;
	}
	file.close();

	for (int x = 0; x < TABLE_SIZE; x++) 
	{
		int y = hashfunc(customers[i].lastname + customers[i].firstname + customers[i].id, 400);
		table.set(list[x], y);
	}
	int used = 0;
	int collisions = 0;
	for (int x = 0; x < 400; x++) 
	{
		int test = 0;
		cout << "[" << x << "]\t"; 
		if (list[x].head != NULL)
			used++;
		while (list[x].head != NULL) {
		cout << list[x].head->data.lastname << ",";
		cout << list[x].head->data.firstname << "->";
		list[x].head = list[x].head->next;
		test++;
		}
		if (test > 1)
			collisions++;
		cout << endl;
	}
	cout << "\nStatistics:" << endl;
	cout << "\tMaximum = " << maximum << endl;
	cout << "\tUsed = " << (float)used / (float)400*100.0 << "%" << endl;
	cout << "\tCollisions = " << float(collisions) / float(400) * 100.0 << "%" << endl;

    return 0;
}
