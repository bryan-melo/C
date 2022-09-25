#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>
#include <array>
#include <memory>
#include <thread>
#include "ConsoleColor.h"

using namespace std;

//---
int swaps = 0;
int passes = 0;
int compares = 0;

template <typename T>
class DynamicArray
{
	T* base;
	int isize = 0;
	int capacity = 0;
public:
	DynamicArray(int c = 10) : capacity(c) { allocate(capacity); }
	void set(T v, int offset)
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
	void push(T t) { set(t, isize); }
	void allocate(int c)
	{
		capacity = c + 1;
		base = new T[capacity];
	}
	void resize(int nusize)
	{
		capacity = nusize;
		T* temp = new T[nusize];
		for (int i = 0; i < capacity; i++)
			temp[i] = base[i];
		delete[] base;
		base = temp;
	}
	void pop()
	{
		for (int i = 1; i < size; i++)
			base[i - 1] = base[i];
		isize--;
	}
	void clear()
	{
		delete[] base;
		isize = 0;
		allocate(capacity);
	}
	T& operator[](int index) { return base[index]; }
	void Output()
	{
		for (int i = 0; i < isize; i++)
			cout << yellow << '[' << base[i] << ']' << " ";
		cout << endl;
		this_thread::sleep_for(500ms);
	}
};


template <typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
	::swaps++;
}

void Output(DynamicArray<string>& theArray, int a, int b)
{
	for (int i = 0; i < theArray.size(); i++)
	{
		if (theArray[i] == theArray[b])
			cout << green << '[' << theArray[i] << ']' << " ";
		else if (theArray[i] == theArray[a])
			cout << red << '[' << theArray[i] << ']' << " ";
		else
			cout << gray << '[' << theArray[i] << ']' << " ";
	}
	cout << endl;
	this_thread::sleep_for(500ms);
}

void OutputPartition(DynamicArray<string>& theArray, int a, int b)
{
	for (int i = 0; i < theArray.size(); i++)
	{
		if (i == a)
			cout << green << '[' << theArray[i] << ']' << " ";
		else if (i == b)
			cout << red << '[' << theArray[i] << ']' << " ";
		else
			cout << gray << '[' << theArray[i] << ']' << " ";
	}
	cout << endl;
	this_thread::sleep_for(500ms);
}

void OutputM(DynamicArray<string>& theArray, int a, int b, ostream& color(ostream&))
{
	for (int i = a; i < b; i++)
	{
		if (theArray[i] < theArray[b])
			cout << color << '[' << theArray[i] << ']' << " ";
		else
			cout << color << '[' << theArray[i] << ']' << " ";
	}
	cout << endl;
	this_thread::sleep_for(500ms);
}

void OutputMerged(DynamicArray<string>& theArray, DynamicArray<string>& left, DynamicArray<string>& right)
{
	for (int i = 0; i < theArray.size(); i++)
	{
		int used = 0;
		for (int l = 0; l < left.size(); l++)
		{
			if (theArray[i].compare(left[l]) == 0)
			{
				cout << green << '[' << theArray[i] << ']' << " ";
				used++;
			}
		}
		if (used > 0) continue;
		for (int r = 0; r < right.size(); r++)
		{
			if (theArray[i].compare(right[r]) == 0)
			{
				cout << red << '[' << theArray[i] << ']' << " ";
				used++;
			}
		}
		if (used == 0)
		{
			cout << gray << '[' << theArray[i] << ']' << " ";
		}
	}
	cout << endl;
	this_thread::sleep_for(500ms);
}

/*
The bubble sort works by passing sequentially over a list,
comparing each value to the one immediately after it.
If the first value is greater than the second, their positions are switched.
Over a number of passes, at most equal to the number of elements in the list,
all of the values drift into their correct positions (large values "bubble"
rapidly toward the end, pushing others down around them).
*/
template <typename T>
void BubbleSort(DynamicArray<T>& theArray)
{
	while (::passes < theArray.size())
	{
		for (int index = 1; index < theArray.size(); index++)
		{
			::compares++;
			if (theArray[index] < theArray[index - 1])
			{
				Swap(theArray[index], theArray[index - 1]);
				::swaps++;
				Output(theArray, index, index - 1);
			}
		}
		::passes++;
	}
}

/*
Insertion sort is a simple sorting algorithm that builds
the final sorted array (or list) one item at a time. It
is much less efficient on large lists than more advanced
algorithms such as quicksort, heapsort, or merge sort.
However, insertion sort provides several advantages:
1) Simple implementation
2) Efficient for small data sets
3) Adaptive, efficient for data sets that are partially sorted
4) Stable, does not change the relative order with equal keys
5) In-place, only requires a constant amount O(1)
6) Online, can sort a list as it receives it
*/
template <typename T>
void InsertionSort(DynamicArray<T>& theArray)
{
	for (int x = 1; x < theArray.size(); x++)
	{
		T nextItem = theArray[x];
		int current = x;
		while ((current > 0) && (theArray[current - 1] > nextItem))
		{
			::compares++;
			//if (theArray[current] != theArray[current - 1])
			//	Output(theArray, current-1, current);
			theArray[current] = theArray[current - 1];
			current--;
			::swaps++;
		}
		theArray[current] = nextItem;
		if (current != x)
			OutputPartition(theArray, current, x);
		::passes++;
	}
}

/*
The selection sort algorithm sorts an array by repeatedly
finding the minimum element (considering ascending order)
from unsorted part and putting it at the beginning. The
algorithm maintains two subarrays in a given array.
	1) The subarray which is already sorted.
	2) Remaining subarray which is unsorted.
In every iteration of selection sort, the minimum element
(considering ascending order) from the unsorted subarray
is picked and moved to the sorted subarray.
*/
template <typename T>
void SelectionSort(DynamicArray<T>& theArray)
{
	for (int last = theArray.size() - 1; last >= 1; last--)
	{
		int indexSoFar = 0;
		for (int currentIndex = 1; currentIndex < last + 1; currentIndex++)
		{
			::compares++;
			if (theArray[currentIndex] > theArray[indexSoFar])
			{
				indexSoFar = currentIndex;
			}
		}
		int largest = indexSoFar;
		if (largest != last)
		{
			Output(theArray, largest, last);
			Swap(theArray[largest], theArray[last]);
			Output(theArray, largest, last);
		}
		::passes++;
	}
}
/*
The  shell sort  is named after its inventor D. L. Shell.
Instead of comparing adjacent elements, like the bubble sort,
the shell sort repeatedly compares elements that are a certain
distance away from each other (d represents this distance).
The value of d starts out as half the input size and is halved
after each pass through the array.  The elements are compared
and swapped when needed.  The equation  d = (N + 1) / 2  is used.
*/
template <typename T>
void ShellSort(DynamicArray<T>& theArray)
{
	for (int h = theArray.size() / 2; h > 0; h = h / 2)
	{
		for (int unsorted = h; unsorted < theArray.size(); unsorted++)
		{
			T nextItem = theArray[unsorted];
			::swaps++;
			int loc = unsorted;
			int start = loc;
			::compares++;
			while ((loc >= h) && (theArray[loc - h] > nextItem))
			{
				theArray[loc] = theArray[loc - h];
				loc = loc - h;
				::swaps++;
			}
			theArray[loc] = nextItem;
			if (start != loc)
				Output(theArray, start, loc);
			::swaps++;
		}
		::passes++;
	}
}

template <typename T>
void exchange(T& a, T& b)
{
	Swap(a, b);
}

template <typename T>
int partition(DynamicArray<T>& arr, int left, int right)
{
	T pivot = arr[left];
	cout << cyan << "Pivot: " << pivot << green << "\nLeft: ";
	OutputM(arr, 0, left, green);
	cout << red << "Right: ";
	OutputM(arr, left + 1, 9, red);
	while (left != right)
	{
		if (arr[left] > arr[right])
			exchange(arr[left], arr[right]);
		if (pivot == arr[left])
			right--;
		else
			left++;
		::compares += 2;
	}
	//OutputP(arr, left, right);
	return left;
}

template <typename T>
void QuickSort(DynamicArray<T>& theArray, int first, int last)
{
	if (first < last)
	{
		int pivotIndex = partition(theArray, first, last);
		QuickSort(theArray, first, pivotIndex - 1);
		QuickSort(theArray, pivotIndex + 1, last);
		::passes++;
	}
}

template <typename T>
class MergeSort
{
public:
	void Merge(DynamicArray<T>& arr, int lft, int mid, int rte)
	{
		int ileft, jright, kmerged;
		int n1 = mid - lft + 1;
		int n2 = rte - mid;
		DynamicArray<T> Left(arr.size());
		DynamicArray<T> Right(arr.size());
		for (ileft = 0; ileft < n1; ileft++)
		{
			Left.push(arr[lft + ileft]);
			::swaps++;
		}
		cout << green << "Left:  ";
		OutputM(Left, 0, n1, green);
		for (jright = 0; jright < n2; jright++)
		{
			Right.push(arr[mid + 1 + jright]);
			::swaps++;
		}
		cout << red << "Right: ";
		OutputM(Right, 0, n2, red);
		ileft = 0; // Initial index of first subarray
		jright = 0; // Initial index of second subarray
		kmerged = lft; // Initial index of merged subarray
		while (ileft < n1 && jright < n2)
		{
			::compares++;
			if (Left[ileft] <= Right[jright])
			{
				arr[kmerged] = Left[ileft];
				ileft++;
				::swaps++;
			}
			else
			{
				arr[kmerged] = Right[jright];
				jright++;
				::swaps++;
			}
			kmerged++;
		}
		while (ileft < n1)
		{
			arr[kmerged] = Left[ileft];
			ileft++;
			kmerged++;
			::swaps++;
		}
		while (jright < n2)
		{
			arr[kmerged] = Right[jright];
			jright++;
			kmerged++;
			::swaps++;
		}
		OutputMerged(arr, Left, Right);
	}
	void Sort(DynamicArray<T>& arr, int left, int right)
	{
		if (left < right)
		{
			int mid = left + (right - left) / 2;
			Sort(arr, left, mid);
			//cout << green << "Left:  ";
			//OutputM(arr, left, mid, green);
			//cout << red << "Right: ";
			//OutputM(arr, mid + 1, right, red);
			Sort(arr, mid + 1, right);
			Merge(arr, left, mid, right);
			::passes++;
		}
	}
};

void reset(DynamicArray<string>& theArray)
{
	::swaps = 0;
	::passes = 0;
	::compares = 0;
	::swaps = 0;
	string animals[] =
	{
		"Zebra",
		"Xray",
		"Turtle",
		"Rabbit",
		"Monkey",
		"Kangaroo",
		"Giraffe",
		"Fox",
		"Elephant",
		"Bison",
	};
	theArray.clear();
	for (int i = 0; i < 10; i++)
		theArray.push(animals[i]);
}

void Statistics(DynamicArray<string>& darray)
{
	darray.Output();
	cout << purple << "\nNumber of passes: " << white << ::passes
		<< purple << "\nNumber of swaps: " << white << ::swaps
		<< purple <<"\nNumber of compares: " << white << ::compares
		<< endl;
	cout << purple << "Weight: " << white << ::passes + (5 * ::swaps) + (2 * ::compares) << endl;
	cout << white;
}

void main()
{
	DynamicArray<string> darray;
	cout << yellow << "\n=-= Bubble Sort =-=" << endl;
	reset(darray);
	BubbleSort<string>(darray);
	Statistics(darray);

	cout << yellow << "\n=-= Insertion Sort =-=" << endl;
	reset(darray);
	InsertionSort<string>(darray);
	Statistics(darray);

	cout << yellow << "\n=-= Selection Sort =-=" << endl;
	reset(darray);
	SelectionSort<string>(darray);
	Statistics(darray);

	cout << yellow << "\n=-= Shell Sort =-=" << endl;
	reset(darray);
	ShellSort<string>(darray);
	Statistics(darray);

	cout << yellow << "\n=-= Quick Sort =-=" << endl;
	reset(darray);
	QuickSort<string>(darray, 0, darray.size() - 1);
	Statistics(darray);

	cout << yellow << "\n=-= Merge Sort =-=" << endl;
	reset(darray);
	MergeSort<string>msort;
	msort.Sort(darray, 0, darray.size() - 1);
	Statistics(darray);
}



