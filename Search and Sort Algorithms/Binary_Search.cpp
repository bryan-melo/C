#include <iostream>
using namespace std;

int BinarySearch(int numbers [], int numbersSize, int key) {
   int mid = 0;
   int low = 0;
   int high = numbersSize - 1;
   
   while (high >= low) {
      mid = (high + low) / 2;
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

int main() {
   int numbers [] = {0, 2, 19, 23, 29, 34, 41, 50, 71, 76, 82, 92 };
   int NUMBERS_SIZE = 12;
   int key, keyIndex;

   
   cout << "NUMBERS: ";
   for (int i = 0; i < NUMBERS_SIZE; ++i) {
      cout << numbers[i] << " ";
   }
   cout << endl;
   
   cout << "Enter a value: ";
   cin >> key;
   
   keyIndex = BinarySearch(numbers, NUMBERS_SIZE, key);
   
   if (keyIndex == -1) {
      cout << key << " was not found." << endl;
   }
   else {
      cout << "Found " << key << " at index " << keyIndex << "." << endl;
   }
}
