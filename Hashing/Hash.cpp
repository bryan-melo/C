// Bryan Melo
// Data Structures - Summer 2021
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <fstream>
using namespace std;

template <typename T>
class DynamicArray
{
	protected:
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
		void set(T v, int offset) 
		{
			if (offset >= capacity)
				resize(capacity * 2);
			v.used++;
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
		void Output() 
		{
			for (int i = 0; i < isize; i++)
				cout << '[' << base[i] << ']' << " ";
				cout << endl;
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
	return midnumber % maximum;
}

int HashDivisionMethod(string key)
{
	int sum = OddEven(key);
	return sum % maximum;
}

// a good hashing function returns few collisions
int getHash(string key)
{
	// return HashMultiplicative(key);
	// return HashMidSquare(key);
	 return HashDivisionMethod(key);
}

class HashElement 
{
private:
      int key = 0;
      string value = "";
public:
	  int used = 0;
      HashElement(int k = 0, string v = "",int u = 0) 
	  {
            key = k;
            value = v;
			used = u;
      }
	  void setKeyValue(int k, string v)
	  {
		  key = k;
		  value = v;
		  used++;
	  }
      int getKey() 
	  {	
            return key;
      }
      string getValue() 
	  {
            return value;
      }
	  operator int() { return getKey(); }
};

class HashTable 
{
private:
      DynamicArray<HashElement> table;
	  int collisions = 0;
public:
	HashTable(int s = 1) { table.resize(s); }
	int size() { return table.size(); }
	int getcollisions() { return collisions; }
	string get(string key) 
	{
		int hash = getHash(key);
		return table[hash].getValue();
	}
	HashElement get(int index)
	{
		return table[index];
	}
	void set(string value) 
	{
		int hash = getHash(value);
		HashElement element(hash, value);
		int key = table[hash].getKey();
		if (key > 0)
		{
			collisions++;
			element.used++;
		}
		table.set(element, hash);
	}     
	HashElement operator [] (int index)
	{
		return get(index);
	}
}; 

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
			cout << rover->Customer.lastname << '\t';
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

int main() {
	Customer* customers = new Customer[512];
	DList<int> list;
	
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
		i++;
	}
	file.close();

	DynamicArray<DList<Customer> > table;
	table.allocate(4);


	HashTable htable(TABLE_SIZE);
	for (int x = 0; x < TABLE_SIZE; x++) 
		htable.set(customers[x].lastname + customers[x].firstname + customers[x].id);
	int used = 0;
	for (int x = 0; x < htable.size(); x++)
	{
		HashElement hentry = htable.get(x);
		cout << endl;
		if (hentry.getKey() > 0)
		{
			used++;
			if (hentry.used > 1)
			{
				cout << "[" << hentry.getKey() << "] " << '\t' << hentry.getValue();
			}
			else
				cout << "[" << hentry.getKey() << "] " << '\t' << hentry.getValue();
		}
		else
			cout << "[" << x << "]\t...";
	}
	cout << "\nStatistics:" << endl;
	cout << "\tMaximum = " << maximum << endl;
	cout << "\tUsed = " << (float)used / (float)htable.size()*100.0 << "%" << endl;
	cout << "\tCollisions = " << float(htable.getcollisions()) / float(TABLE_SIZE) * 100.0 << "%" << endl;


    return 0;
}
/*
	int j = 1;
	while (list->head != NULL) {
	cout << j << ": " << list->head->data.lastname << " " << list->head->data.firstname << " " << list->head->data.id << endl;
	list->head = list->head->next;
	j++;
	}
*/