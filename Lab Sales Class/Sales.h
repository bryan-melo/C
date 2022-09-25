/*
 Specification file for the Sales class
 */

#ifndef SALES_H
#define SALES_H
#include <string>

using std:: string;


class Sales
{
    private:
    string id;
    int year;
    string name;
    int amountSold;
    
    public:
    // constructors
    Sales();
    Sales(string userID, int sYear, string userName, int amount);

    // setters
    void setId(string userID);
    void setYear(int sYear);
    void setName(string userName);
    void setAmount(int amount);
    
    // getters
    string getId() const;
    int getYear() const;
    string getName() const;
    int getAmount() const;
    
    // other functions
    void display() const;
    double detAmountEarned() const;
    double detCommissionPercent() const;
};

#endif
