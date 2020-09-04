// ASU CSE310 Assignment #4
// Name of Author: Alan Griffieth
// ASU ID: 1212575453
// Description: LinkedList implements a list of Product, we can
// insert, search, delete and display the product list

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Product
{
  string productID, name, supplierID, categoryID, unit;
  double price;
  struct Product *next = NULL;
};

class LinkedList
{
 private:
  struct Product *head;
  int size;
 public:
  LinkedList();
  ~LinkedList();
  bool insert(string productID, string name, string supplierID,
	      string categoryID, string unit, double price);
  bool deleteProduct(string productID);
  bool search(string productID);
  void displayList();
  int getSize();

  //you can define your own auxiliary functions if necessary
  //----
};

//Constructor
LinkedList::LinkedList()
{
  head = NULL;
  size = 0;
}

//Destructor
LinkedList::~LinkedList()
{
  Product* cur = head; 
  Product * next = cur;//keeps track of next item while deleting the current item  
  while(cur != NULL) {//while there is still an item in the list    
    next = cur->next;    
    delete(cur);    
    cur = next;     
  }  
  head = NULL;
  size = 0;
}

//Return number of Products inside the Linked list
int LinkedList::getSize()
{
  return size;
}

//Insert the parameter Product at the head of the linked list.
//return true if it is inserted successfully and false otherwise
//Note: we will do this when a collision happens
bool LinkedList::insert(string productID, string name, string supplierID,
                        string categoryID, string unit, double price)
{
  Product* newProduct = new Product;//initialize the new product
  newProduct->productID = productID;
  newProduct->name = name;
  newProduct->supplierID = supplierID;
  newProduct->categoryID = categoryID;
  newProduct->unit = unit;
  newProduct->price = price;
  newProduct->next = NULL;

  if(head == NULL) {//The list is empty and this is the first item being added to the list
    head = newProduct;
    size++;
    return(true);
  }

  else {//There is already an item in the list
    newProduct->next = head;
    head = newProduct;
    size++;
    return(true);
  }
  return(false);//The product could not be inserted for some reason
}

//Delete the Product with the given productID from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteProduct(string productID)
{
  if(!search(productID)) {//The product doesn't exist
    return(false);
  }

  else {
    Product* cur = head;
    Product* pre = cur;
    while(cur->productID != productID) {//Moves through the list until we're at the item with the Id we want to remove
      pre = cur;
      cur = cur->next;
    }

    if(cur == head) {//Special case when removing head
      head = head->next;
      delete(cur);
      size--;
      return(true);
    }

    else {
      pre->next = cur->next;//Sets next of item before Id we want to remove to item after Id we want to remove
      delete(cur);//Removes the item from the list
      size--;
      return(true);
    }
  }
}

//This function searches the product list with the given productID
//returns true if it is found, otherwise return false.
bool LinkedList::search(string productID)
{
  struct Product* start = head;
  bool found = false;
  while(start != NULL) {//While there is still an item in the list
    if(start->productID == productID) {
      found = true;
      break;//no need to search through the rest of the list
    }

    else {
      start = start->next;
    }
  }
  return(found);
}

//This function displays the contents of the linked list.
void LinkedList::displayList()
{
  struct Product *temp = head;
  if(head == NULL)//There's nothing in the list
    {
      cout << "The list is empty" << endl;
      return;
    }
  while(temp!= NULL)
    {
      cout << left;
      cout<< setw(5) << temp->productID
	  << setw(35) << temp->name
	  << setw(15) << temp->supplierID
	  << setw(15) << temp->categoryID
	  << setw(25) << temp->unit
	  << setw(5) << temp->price << endl;
      temp = temp->next;
    }
}
