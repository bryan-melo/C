#include <iostream>
#include <string>
using namespace std;

int LinearSearch(int numbers [], int numbersSize, int key) {
   for (int i = 0; i < numbersSize; ++i) {
      if (numbers[i] == key) {
         return i;
      }
   }
   return -1;  // not found
}
   
int main() {
   int numbers [] = {2, 4, 7, 10, 11, 32, 45, 87};
   const int NUMBERS_SIZE = 8;
   int key, keyIndex;
      
   cout << "NUMBERS: ";
   for (int i = 0; i < NUMBERS_SIZE; ++i) {
      cout << numbers[i] << " ";
   }
   cout << endl;
      
   cout << "Enter a value: ";
   cin >> key;
      
   keyIndex = LinearSearch(numbers, NUMBERS_SIZE, key);
      
   if (keyIndex == key) {
      cout << key << " was not found.";
   } 
   else {
      cout << "Found " << key << " at index " << keyIndex << "." << endl;
   }
}