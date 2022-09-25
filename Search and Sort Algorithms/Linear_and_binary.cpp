#include <iostream>
using namespace std;

int LinearSearch(int* numbers, int numbersSize, int key, int& comparisons) {
   // Added parameter to hold total number of comparisons.
   comparisons = 0;

   for (int i = 0; i < numbersSize; i++) {
      comparisons++;
      if (numbers[i] == key) {
         return i;
      }
   }
   return -1; // not found
}

int BinarySearch(int* numbers, int numbersSize, int key, int& comparisons) {
   // Added parameter to hold total number of comparisons.
   comparisons = 0;

   // Variables to hold the low and high indices of the area being searched. 
   // Starts with entire range.
   int low = 0;
   int high = numbersSize - 1;
   
   // Loop until "low" passes "high"
   while (high >= low) {
      // Calculate the middle index
      int mid = (high + low) / 2;

      // Cut the range to either the left or right half,
      // unless numbers[mid] is the key
      comparisons++;
      if (numbers[mid] < key) {
         low = mid + 1;
      }
      else if (numbers[mid] > key) {
         high = mid - 1;
      }
      else {
         return mid;
      }
   }
   
   return -1; // not found
}

// Main program to test both search functions
int main() {
   int numbers[] = { 2, 4, 7, 10, 11, 32, 45, 87 };
   int numbersSize = sizeof(numbers) / sizeof(numbers[0]);
   cout << "NUMBERS: [" << numbers[0];
   for (int i = 1; i < numbersSize; i++) {
      cout << ", " << numbers[i];
   }
   cout << "]" << endl;

   // Prompt for an integer to search for
   cout << "Enter an integer value: ";
   int key = 0;
   cin >> key;
   cout << endl;

   int comparisons = 0;
   int keyIndex = LinearSearch(numbers, numbersSize, key, comparisons);
   if (keyIndex == -1) {
      cout << "Linear search: " << key << " was not found with ";
      cout << comparisons << " comparisons." << endl;
   }
   else {
      cout << "Linear search: Found " << key << " at index " << keyIndex;
      cout << " with " << comparisons << " comparisons." << endl;
   }
      
   keyIndex = BinarySearch(numbers, numbersSize, key, comparisons);
   if (keyIndex == -1) {
      cout << "Binary search: " << key << " was not found with ";
      cout << comparisons << " comparisons." << endl;
   }
   else {
      cout << "Binary search: Found " << key << " at index " << keyIndex;
      cout << " with " << comparisons << " comparisons." << endl;
   }
}
