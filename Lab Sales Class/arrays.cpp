/*
 Test Driver for the Sales class using an array of Sales objects
*/

#include <iostream>
#include <string>
#include <iomanip>
#include "Sales.h"
using namespace std;

void printList(Sales listA[], int num);

int main()
{
    Sales listA[3] =
    {
        Sales("20192785", 2017, "Jane North", 10000),
        Sales("19278520", 2012, "Tim South", 12000),
        Sales("92374042", 2020, "Linda East",5600)
    };
    
    printList(listA, 3);
  
    return 0;
}

/* Write your code here: define the printList function */

void printList(Sales listA[], int num) {
    for (int i = 0; i < num; i++) {
        listA[i].display();
    }
}
