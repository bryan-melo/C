// Bryan Melo
// Data Structures - Summer 2021
// Sources used: cplusplus and geeksforgeeks, Stanford library, and google
#include <iostream>
#include <unordered_map>	
#include <unordered_set>	
#include <string>
using namespace std;

template <typename T>
class Node {
	public:
	T data;
	Node<T>* next;
	Node<T>* prev;
	Node<T>() { next = NULL; prev = NULL; }
	Node<T>(T d) { next = NULL; prev = NULL; data = d; }
};

template <typename T>
class DList
{
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
			newNode->prev = tail;
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
			head->prev = newNode;
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
				newNode->prev = pCurr;
				pCurr->next = newNode;
				nextNode->prev = newNode;
			}
			if (pCurr->data == find && pCurr == tail) {    // If inserting after the last node, then update tail
				tail->next = newNode;
				newNode->prev = tail;
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
				prevNode = pCurr->prev;
				newNode->next = pCurr;
				newNode->prev = prevNode;
				pCurr->prev = newNode;
				prevNode->next = newNode;
			}
			if (pCurr->data == find && pCurr == head) {    // If inserting before the first node, then update head
				newNode->next = head;
				head->prev = newNode;
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
				pPrev = pCurr->prev;
				if (pAfter != NULL) {
					pAfter->prev = pPrev;
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
	bool CheckIfEmpty()
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
};

template <typename T>
class pQueue : public DList<T> {
    public:
	
        void Enqueue(T data) 
        {
			int priority;
            if (this->head == NULL) 
            {
                Node<T>* newNode = new Node<T>(data, priority);
                this->head = newNode;
                return;
            }

            Node<T>* node = new Node<T>(data, priority);
            Node<T>* temp = this->head;
            Node<T>* parent = NULL;

            while(temp != NULL && temp->priority <= priority)
            {
                parent = temp;
                temp = temp->next;
            }

            if (parent == NULL) 
            {
                node->next = this->head;
                this->head->prev = node;
                this->head = node;
            }
            else if (temp == NULL)
            {
                parent->next = node;
                node->prev = parent;
            }
            else 
            {
                parent->next = node;
                node->prev = parent;
                node->next = temp;
                temp->prev = node;
            }
        }
        Node<T>* Dequeue()
        {
            if (this->head != NULL) {
                Node<T>* temp = this->head;
                this->head = this->head->next;
                this->head->prev = NULL;
                pQueue::Delete(temp->data);
                return temp;
            }
            else
                return NULL;
        }
        Node<T>* Peek()
        {
            if (this->head != NULL)
                return this->head;
            else
                return NULL;
        } 
        bool IsEmpty()
        {
            return pQueue::CheckIfEmpty();
        }
        int GetLength()
        {
            return pQueue::Count();
        }
};

template <typename T>
class Vertex {
public:
   string label;
   Vertex(const string& vertexLabel) {
      label = vertexLabel;
   }
};

template <typename T>
class Edge {
public:
   Vertex<T>* fromVertex;
   Vertex<T>* toVertex;
   double weight;
    
   Edge(Vertex<T>* from, Vertex<T>* to, double edgeWeight) {
      fromVertex = from;
      toVertex = to;
      weight = edgeWeight;
   }
};

template <typename T>
class Graph 
{
private:
	unordered_map<Vertex<T>*, DList<Edge<T>*>*> fromEdges;
   	unordered_map<Vertex<T>*, DList<Edge<T>*>*> toEdges;
public:
	Vertex<T>* addVertex(const string& data) 
	{
      Vertex<T>* vertex = new Vertex<T>(data);
      fromEdges[vertex] = new DList<Edge<T>*>();
      toEdges[vertex] = new DList<Edge<T>*>();
      return vertex;
   	}
	
   	Vertex<T>* getVertex(const string& data) 
	{
      	for (auto& keyValue : fromEdges) {
         	Vertex<T>* vertex = keyValue.first;
         	if (vertex->label == data) 
            	return keyValue.first;
      	}
      	return NULL;
  	}

	pair<Edge<T>*, Edge<T>*> addEdge(Vertex<T>* vertexA, Vertex<T>* vertexB, int weight = 1.0) 
	{
        return pair<Edge<T>*, Edge<T>*>( directedEdge(vertexA, vertexB, weight), directedEdge(vertexB, vertexA, weight));
   	}
   	
	Edge<T>* directedEdge(Vertex<T>* v1, Vertex<T>* v2, int weight = 1) 
	{   
      Edge<T>* edge = new Edge<T>(v1, v2, weight);
      fromEdges[v1]->Append(edge);
      toEdges[v2]->Append(edge);
      return edge;
   	}
	
   	unordered_set<Edge<T>*> getEdges() const 
	{
    	unordered_set<Edge<T>*> set;
      	for (auto& key : fromEdges) {
        	DList<Edge<T>*>* edges = key.second;
         	for (Edge<T>* edge : *edges) {
            	set.insert(edge);
         	}
      	}
      	return set;
   	}

	void printMST(Graph<T>& graph) 
	{
   		pQueue<Edge<T>*> eQueue;
   		for (Edge<T>* edge : graph.getEdges())
      		eQueue.Enqueue(edge);
      
   		DList<T>* allVertices = graph.GetVertices();
   		DList<T>* vertexSets(allVertices);
   		DList<Edge<T>*> mstList;
      
   		while (eQueue.GetLength() > 0) 
		{	
      		Edge<T>* nextEdge = eQueue.Dequeue();
      		// Implement a Vertex set collection function ~ set1
      		// Implement a Vertex set collection function ~ set2

			/*  
      		if (set1 != set2) 
			{
         		resultList.Append(nextEdge);
         		// merge both sets
      		}
			*/
   		} 
   		// return mstList;
	}
};

// Driver code
int main()
{
	Graph<string> graph;
	string airportNames[] = {"SFO", "LAX", "DFW", "ORD", "JFK", "MIA", "BOS"};
	for (string& vertexName : airportNames)
		graph.addVertex(vertexName);

	graph.addEdge(graph.getVertex("SFO"), graph.getVertex("LAX"), 337);
   	graph.addEdge(graph.getVertex("SFO"), graph.getVertex("ORD"), 1846);
   	graph.addEdge(graph.getVertex("SFO"), graph.getVertex("BOS"), 2704);
   	graph.addEdge(graph.getVertex("SFO"), graph.getVertex("DFW"), 1464);
   	graph.addEdge(graph.getVertex("LAX"), graph.getVertex("DFW"), 1235);
   	graph.addEdge(graph.getVertex("LAX"), graph.getVertex("MIA"), 2342);
   	graph.addEdge(graph.getVertex("DFW"), graph.getVertex("ORD"), 802);
   	graph.addEdge(graph.getVertex("DFW"), graph.getVertex("MIA"), 1121);
   	graph.addEdge(graph.getVertex("MIA"), graph.getVertex("JFK"), 1090);
   	graph.addEdge(graph.getVertex("MIA"), graph.getVertex("BOS"), 1258);
   	graph.addEdge(graph.getVertex("ORD"), graph.getVertex("JFK"), 740);
   	graph.addEdge(graph.getVertex("ORD"), graph.getVertex("BOS"), 867);
   	graph.addEdge(graph.getVertex("BOS"), graph.getVertex("JFK"), 187);
	
	graph.printMST(graph);

	return 0;
}
 
/*

Expected output:

Minimum spanning tree:

JFK -> BOS, weight: 187
SFA -> LAX, weight: 337
ORD -> JFK, weight: 740
DFW -> ORD, weight: 802
JFK -> MIA, weight: 1090
LAX -> DFW, weight: 1235

Total weight: 4391

*/