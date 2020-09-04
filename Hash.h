// ASU CSE310 Assignment #4
// Name of Author: Alan Griffieth
// ASU ID: 1212575453
// Description: this is where you need to design functions on Hash table,
// such as hashInsert, hashDelete, hashSearch and hashDisplay

#include <iostream>
#include <iomanip>
#include <string>
#include "LinkedList.h"
#include <math.h>

using namespace std;

class Hash
{
 private:
  LinkedList **table;  //hash table is a linked list of linkedlist
  int m;               //number of table slots
 public:
  Hash(int size);
  ~Hash();
  bool hashInsert(string productID, string name, string supplierID, string categoryID, string unit, double price);
  bool hashDelete(string productID, string name, string supplierID, string categoryID);
  bool hashSearch(string productID, string name, string supplierID, string categoryID);
  void hashDisplay();
  int h(string key);

  //you can define your own auxiliary functions if necessary
  //----
};

//constructor
Hash::Hash(int size)
{
  table = new LinkedList*[size];
  m = size;
  for(int i = 0; i < m; i++) {
    table[i] = new LinkedList();//instantiates the linked list in each element of the table
  }
}

//Destructor
Hash::~Hash()
{
  delete[] table;
  table = NULL;
}

//hashInsert inserts a Product with the relevant info. into the hash table.
//(1)First, it need to get the product key, a product key is the combination
//of productID, name, supplierID and categoryID
//(2)Next, run hash function on this key to get its slot index,
//(3)Insert the product into the relevant linked list
//the function returns true if the product is inserted successfully and false otherwise
bool Hash::hashInsert(string productID, string name, string supplierID,
                      string categoryID, string unit, double price)
{
  string productKey = productID + name + supplierID + categoryID;
  int insertionPoint = h(productKey);
  return(table[insertionPoint]->insert(productID, name, supplierID, categoryID, unit, price));//returns true if insertion is successful
}

//hashDelete deletes a Product with the relevant key from the hash table.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of productID, name, supplierID and categoryID
bool Hash::hashDelete(string productID, string name, string supplierID, string categoryID)
{
  string productKey = productID + name + supplierID + categoryID;
  int deletionPoint = h(productKey);
  bool found = hashSearch(productID, name, supplierID, categoryID);
  if(found) {
    bool deleted = table[deletionPoint]->deleteProduct(productID);
    if(deleted) {//if deleted successful, print out the following message on screen
      cout<< setw(5) << productID
	  << setw(35) << name
	  << setw(15) << supplierID
	  << setw(15) << categoryID
	  << " is deleted from hash table." << endl;
    }
  }
 
  else {//if deleted unsuccessful, print out the following message on screen
    cout<< setw(5) << productID
	<< setw(35) << name
	<< setw(15) << supplierID
	<< setw(15) << categoryID
	<< " is NOT found and NOT deleted from hash table." << endl;
  }
  return(found);
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of productID, name, supplierID and categoryID
bool Hash::hashSearch(string productID, string name, string supplierID, string categoryID)
{
  string productKey = productID + name + supplierID + categoryID;
  int searchPoint = h(productKey);
  bool found = table[searchPoint]->search(productID);
  if(found) {//if find it, print out the following message on screen
    cout   << left
	   << setw(5) << productID
	   << setw(35) << name
	   << setw(15) << supplierID
	   << setw(15) << categoryID
	   << " is found in hash table." << endl;
  }
   
  else {//if not find it, print out the following message on screen
    cout<< left
	<< setw(5) << productID
	<< setw(35) << name
	<< setw(15) << supplierID
	<< setw(15) << categoryID
	<< " is NOT found in hash table." << endl;
  }
  return(found);
}

//This function prints all the elements from the hash table.
void Hash::hashDisplay()
{
  //Check the solution output for output format, follow it closely
  for(int i = 0; i < m; i++) {//Follows format specified by output.txt pages
    int size;
    cout << "\nindex: " << i
	 << ", linked list size: " << table[i]->getSize() << endl;
    table[i]->displayList();
  }
}

/*This is the hash function you will design, write and describe it
 clearly here.
 This hash function follow hash by division. It calculates the sum of the ascii values
 of each char in the key string multiplied by 37, a prime number, to avoid any patterns.
 The remainder of this value divided by the size of the table is then taken as the hash 
 value.
*/
int Hash::h(string key)
{
  int hashValue = 0;
  for(int i = 0; i < key.length(); i++) {
    hashValue = 37 * hashValue + key[i];
  }

  hashValue %= m;

  if(hashValue < 0) {//In case the hashValue somehow came out negative
    hashValue += m;
  }

  return(hashValue);
}
