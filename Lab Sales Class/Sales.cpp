/*
  Implementation file for the Sales class.
*/

#include "Sales.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/*~*~*~*~*~*~
 This is the default constructor; it sets everything to 0 or "".
 */
Sales::Sales()
{
   id = "";
   year = 0;
   name = "";
   amountSold = 0;
}

/*~*~*~*~*~*~
This is an overloaded constructor.
 It sets the variables according to the parameters.
*/
Sales::Sales(string userID, int sYear, string userName, int amount)
{
    id = userID;
    year = sYear;
    name = userName;
    amountSold = amount;
}

/*~*~*~*~*~*~
This function displays the member variables,
 the commision percent and amount earned
 in a neat format.
*/
void Sales::display() const
{
    cout << "           ID: " << id << endl;
    cout << "         Year: " << year << endl;
    cout << "         Name: " << name << endl;
    cout << "  Amount Sold: $" << amountSold << endl;
    cout << "   Commission: " << detCommissionPercent() << "%" << endl;
    cout << "Amount Earned: $" << detAmountEarned() << endl;
}
/*~*~*~*~*~*~
 This function determines the commision percent based on the following table:
    Sales        Commission
   $0 - 1000        3%
 1001 - 5000        4.5%
 5001 - 10,000      5.25%
 over 10,000        6%
*/
double Sales::detCommissionPercent() const
{
    double commission = 0;
    
    if ( amountSold > 0) {
        if(amountSold<= 1000) // if amountSold is between [0, 1000]
            commission = 3.0;
        else if(amountSold<=5000)// if amountSold is between [1001, 5000]
            commission = 4.5;
        else if(amountSold<=10000) // if amountSold is between [5001, 10000]
            commission = 5.25;
        else
            commission = 6.0;
    }
    
    return commission;
}

/*~*~*~*~*~*~
 This function determines the amount earned:
 it calls the detCommisionPercent) function.
 */
double Sales::detAmountEarned() const
{
    double amountEarned = 0;
    
    amountEarned = detCommissionPercent() * amountSold / 100;
    
    return amountEarned;
}

// Setters
void Sales::setId(string userID) { id = userID; }
void Sales::setYear(int sYear) { year = sYear; }
void Sales::setName(string userName) { name = userName; }
void Sales::setAmount(int amount) { amountSold = amount; }
    
// Getters
string Sales::getId() const { return id; }
int Sales::getYear() const { return year; }
string Sales::getName() const { return name; }
int Sales::getAmount() const { return amountSold; }
