// ASU CSE310 Assignment #4
// Name of Author: Alan Griffieth
// ASU ID: 1212575453
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.

/**************************************************************************
//(1)Describe here what is your hash function? How do you get an input
// oneLine's hash value. I used "Hashing by Division" as my function. I get an
// input by summing up the ascii values multiplied by 37, a prime number.
//(2)What is the number of collisions you expected?
//(3)Did your hash function work well? Using the test cases, what's your hash
//   table's load factor? The load factor is around n/m. The highest I encountered was
//   9 from input4.txt 
//(4)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
//   If I wanted to reduce the number of collisions, I would use open addressing
//   to insert into my hashtable, but this would make other operations, like deletion,
//   harder.
***************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include "Hash.h"

using namespace std;

//This function extracts tokens from oneLine and get all info. of a Product
void getProductInfo(string oneLine, string& productID, string& name, string& supplierID,
                    string& categoryID, string& unit, double& price);

//This function extracts tokens from onLine and get a Product key which is
//the combination of productID, name, supplierID and categoryID
void getKey(string oneLine, string& productID, string& name,
            string& supplierID, string& categoryID);

int main()
{
  //a variable represents the number of hash table slots
  int count;

  //a variable represents the number of commands inside the input file
  int numOfCommand;

  //a variable represents the actual command name inside the input file
  string command;

  string productID, name, supplierID, categoryID, unit;
  double price;
  char delimiter = ',';

  //declare any other necessary variables here
  string oneLine;

  //get the first line which is a number and store it inside count
  cin >> count;
  cin.ignore(20, '\n');

  //create the hash table with the relevant number of slots
  Hash* hashTable = new Hash(count);

  do {
    getline(cin, oneLine);
    if(oneLine.compare("InsertionEnd") == 0) {
      break;
    }

    //if command is not InsertionEnd
    //Get one line, call getProductInfo(), then
    //insert the new product inside the hash table
    else {
      getProductInfo(oneLine, productID, name, supplierID, categoryID, unit, price);//gets product into
      hashTable->hashInsert(productID, name, supplierID, categoryID, unit, price);//inserts into the hash table
    }
  } while(true);

  cin >> numOfCommand;
  cin.ignore(20, '\n');

  for(int i= 0; i < numOfCommand; i++)
    {
      //get one line from the input file and extract the first token,
      getline(cin, oneLine);
      istringstream iss(oneLine);//allows for getline to be used on string of oneLine
      getline(iss, command, delimiter);
      //if the token is hashDisplay, call the relevant function in Hash.h
      if(command.compare("hashDisplay") == 0) {
	hashTable->hashDisplay();
      }

      //if the token is hashSearch, call the relevant function in Hash.h
      else if(command.compare("hashSearch") == 0) {
	getline(iss, oneLine);//We need the rest of the string
	getKey(oneLine, productID, name, supplierID, categoryID);//get the key
	hashTable->hashSearch(productID, name, supplierID, categoryID);//search with the key
      }
      //if the token is hashDelete, call the relevant function in Hash.h
      else if(command.compare("hashDelete") == 0) {
	getline(iss, oneLine);//We need the rest of the string
	getKey(oneLine, productID, name, supplierID, categoryID);//get the key
	hashTable->hashDelete(productID, name, supplierID, categoryID);//try to delete with the key
      }

      else {//for all other cases, show the following message
	cout << "Invalid command" << endl;
      }
    } //end for loop

  return 0;
} //end main

//*******************************************************************
//This function extract the tokens from one line and
//get all product info.
//*******************************************************************
void getProductInfo(string oneLine, string& productID, string& name, string& supplierID,
                    string& categoryID, string& unit, double& price)
{
  char delimiter = ',';
  string stringPrice;
  
  istringstream iss(oneLine);//allows getline to be used on oneLine
  
  getline(iss, productID, delimiter);
  getline(iss, name, delimiter);
  getline(iss, supplierID, delimiter);
  getline(iss, categoryID, delimiter);
  getline(iss, unit, delimiter);
  getline(iss, stringPrice);

  price = stod(stringPrice);//converts a string to a double
  //Note: you can use stod to convert a string into double
  //but you will need c++11 compiler to achieve this
  //for example: price = stod(token);
}

//********************************************************************
//This function extracts the productID, name, supplierID and categoryID
//from a given oneLine. These info. forms the key of a Product.
//********************************************************************
void getKey(string oneLine, string& productID, string& name,
            string& supplierID, string& categoryID)
{
  char delimiter = ',';

  istringstream iss(oneLine);//allows getline to be used on oneLine
  
  getline(iss, productID, delimiter);
  getline(iss, name, delimiter);
  getline(iss, supplierID, delimiter);
  getline(iss, categoryID, delimiter);
  
  //Note: the code is very similar to above getProductInfo()
}
