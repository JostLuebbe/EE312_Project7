/*
 * Name: Jost Luebbe
 * EID: jl64249
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */

#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

using namespace std;

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottles in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}
	
	/* NOT REACHED */
	return 0;
}


/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust); 
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}
	
	return result;
}

void processSummarize() {
    cout << "There are " << *selectInventItem("Bottles") << " Bottles, " << *selectInventItem("Diapers") << " Diapers and " << *selectInventItem("Rattles") << " Rattles in inventory\n";
    cout << "we have had a total of " << database.length << " different customers\n";

    if(findMax("Bottles")==0){
        cout << "no one has purchased any Bottles\n";
    }
    else{
        cout << findMax("Bottles")->name.c_str() << " has purchased the most Bottles (" << findMax("Bottles")->bottles << ")\n";
    }
    if(findMax("Diapers")==0){
        cout << "no one has purchased any Diapers\n";
    }
    else{
        cout << findMax("Diapers")->name.c_str() << " has purchased the most Diapers (" << findMax("Diapers")->diapers << ")\n";
    }
    if(findMax("Rattles")==0){
        cout << "no one has purchased any Rattles\n";
    }
    else{
        cout << findMax("Rattles")->name.c_str() << " has purchased the most Rattles (" << findMax("Rattles")->rattles << ")\n";
    }
}

void processPurchase() {
    String cust_name;
    String pur_item_type;
    int pur_item_cnt = 0;

    readString(cust_name);
    readString(pur_item_type);
    readNum(pur_item_cnt);

    if(pur_item_cnt>*selectInventItem(pur_item_type)){
        cout << "Sorry " << cust_name.c_str() << ", we only have " << *selectInventItem(pur_item_type) << " " << pur_item_type.c_str() << "\n";
        return;
    }

    (*selectInventItem(pur_item_type, database[cust_name])) += pur_item_cnt;
    (*selectInventItem(pur_item_type)) -= pur_item_cnt;

}

void processInventory() {
    String inv_item_type;
    int inv_item_cnt;

    readString(inv_item_type);
    readNum(inv_item_cnt);

    (*selectInventItem(inv_item_type)) += inv_item_cnt;
}