
/*
Name:  Thomas Wozniak      Z#: 23392227
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date:  07/20/2021           
Total Points: 10
Assignment #: Assignment 8

Description:

*/

//Include the following

#include <iostream>
#include <string>
#include <fstream>  
#include <iomanip>
using namespace std;


class order_record
{
public:
	string pname;
	string cname;
	double plant_cost;
	int quantity;
	double net_cost;
	double tax_rate;
	double purchase_tax;
	double discount;
	double discount_rate;
	double total_cost;
};


//Prototypes for your functions 

void initialize(order_record*& STR, int& count, int& size);
bool is_Empty(int count);
bool is_Full(int count, int size);
int search(order_record* STR, int  count, string key);
void add(order_record*& STR, int& count, int& size);
void remove(order_record* STR, int& count, string key);
void double_size(order_record*& STR, int  count, int& size);
void process(order_record* STR, int count);
void print(const order_record* STR, const int  count);
void destory_STR(order_record* STR, int& count, int& size);


void initialize(order_record*& STR, int& count, int& size)
{
	ifstream infile;
	infile.open("nursery_stock.txt");
	count = 0;

	size = std::count(std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>(), '\n');
	infile.seekg(0, ios::beg);
	
	STR = new order_record[size];
	while (!infile.eof())
	{
		if (count < size) {
			infile >> STR[count].pname >> STR[count].cname >> STR[count].quantity >> STR[count].plant_cost;
			count++;
		}
		else {
			double_size(STR, count, size);
			infile >> STR[count].pname >> STR[count].cname >> STR[count].quantity >> STR[count].plant_cost;
			count++;
		}
	}
	infile.close();

}


bool is_Empty(int count)
{
	return count == 0;
}


bool is_Full(int count, int size)
{
	return count == size;
}



int search(order_record* STR, int  count, string key)
{
	for (int i = 0; i < count; i++) {
		if (STR[i].pname == key) {
			return i;
		}
	}
	return -1;
}



void add(order_record*& STR, int& count, int& size)
{
	if (count < size) {
		cout << "Enter plant name: ";
		cin >> STR[count].pname;
		cout << "Enter county name: ";
		cin >> STR[count].cname;
		cout << "Enter quantity of plants: ";
		cin >> STR[count].quantity;
		cout << "Enter price of plant: ";
		cin >> STR[count].plant_cost;
		count++;
	}
	else {
		double_size(STR, count, size);
		cout << "Enter plant name: ";
		cin >> STR[count].pname;
		cout << "Enter county name: ";
		cin >> STR[count].cname;
		cout << "Enter quantity of plants: ";
		cin >> STR[count].quantity;
		cout << "Enter price of plant: ";
		cin >> STR[count].plant_cost;
		count++;
	}
	process(STR, count);
}


void remove(order_record* STR, int& count, string key)
{
	for (int i = 0; i < count; i++) {
		if (STR[i].pname == key) {
			for (int j = i; j < count - 1; j++) {
				STR[j] = STR[j + 1];
			}
			count--;
		}
	}
	//Put the code here to remove ALL the records in STR that have a pname equal to key
	//If you find the item(s), you must shift and decrement count. Hint see program "dynamic_array_example8.cpp"
}


void double_size(order_record*& STR, int  count, int& size)
{
	order_record*temp = new order_record[2 * size];
	for (int i = 0; i < size; i++) {
		temp[i] = STR[i];
	}
	size = 2 * size;
	delete[] STR;
	STR = new order_record[size];
	for (int i = 0; i < count; i++) {
		STR[i] = temp[i];
	}
	//Put the code here to double the size (amount of memory allocated to the array) of the dynamic array.
	//You must allocate memory using new. Hint see program "dynamic_array_example8.cpp"
}


void process(order_record* STR, int count)
{
	for (int i = 0; i < count; i++) {
		if (STR[i].cname == "dade"){
			STR[i].tax_rate = 6.5;
		}
		else if (STR[i].cname==("broward")) {
			STR[i].tax_rate = 6;
		}
		else if (STR[i].cname == ("palm")) {
			STR[i].tax_rate = 7;
		}
		
		STR[i].net_cost = STR[i].quantity*STR[i].plant_cost;

		if (STR[i].quantity = 0) {
			STR[i].discount_rate = 0;
		}
		else if (STR[i].quantity >= 1 || STR[i].quantity <= 5) {
			STR[i].discount_rate = 1;
		}
		else if (STR[i].quantity >= 6 || STR[i].quantity <= 11) {
			STR[i].discount_rate = 3;
		}
		else if (STR[i].quantity >= 12 || STR[i].quantity <= 20) {
			STR[i].discount_rate = 5;
		}
		else if (STR[i].quantity >= 21 || STR[i].quantity <= 50) {
			STR[i].discount_rate = 8;
		}
		else {
			STR[i].discount_rate = 12;
		}
		STR[i].discount = STR[i].net_cost*(STR[i].discount_rate) / 100;
		STR[i].purchase_tax = STR[i].net_cost*STR[i].tax_rate / 100;
		STR[i].total_cost = STR[i].net_cost + STR[i].purchase_tax - STR[i].discount;
	}
	//Put the code here for the loop to process the data stored in the array.
}


void print(const order_record* STR, const int  count)
{
	ofstream outfile;
	outfile.open("nursery_result20.txt", fstream::app);
	static int run = 1;

	//put code here for the loop to print the data in the array to the stream out.
	for (int i = 0; i < count; i++) {
		outfile << STR[i].pname << "\t" << STR[i].cname << "\t" << STR[i].plant_cost << "\t" << STR[i].quantity << "\t" << STR[i].net_cost << "\t" <<
			STR[i].tax_rate << "\t" << STR[i].purchase_tax << "\t" << STR[i].discount << "\t" << STR[i].total_cost << "\t" << endl;
	}
	
	run++;
	outfile.close();
}




void destory_STR(order_record* STR, int& count, int& size)
{
	delete[]STR;
	size = 0;
	count = 0;
}

//Here is your driver to test the program
int main()
{
	int count = 0; //intializating count
	int size = 1;
	order_record* STR = 0;//declaring the dynamic array

	cout << "**********************************************************************\n";
	cout << "Test 1: Testing initialize, double_size, process, is_full and print " << endl;
	initialize(STR, count, size);
	process(STR, count);
	print(STR, count);
	cout << "End of Test 1" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	////Test 2:
	void add(order_record * & STR, int & count, int & size);
	cout << "Test 2: Testing add, double_size, process, is_full, and print " << endl;
	add(STR, count, size);
	print(STR, count);
	cout << "End of Test 2" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	////Test 3:
	void remove(order_record * STR, int & count, string key);
	cout << "Test 3: Testing remove, is_Empty, search and print " << endl;
	cout << "Removing rose\n";
	remove(STR, count, "rose");
	print(STR, count);
	cout << "Removing rose\n";
	remove(STR, count, "owl");
	print(STR, count);
	cout << "End of Test 3" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	////Test 4:
	void add(order_record * & STR, int & count, int & size);
	cout << "Test 4: Testing add, double_size, process, is_full, and print " << endl;
	add(STR, count, size);
	print(STR, count);
	cout << "End of Test 4" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	void destroy_STR(order_record  * STR, int & count, int & size);
	cout << "Test 5: destroy_STR and print " << endl;
	destory_STR(STR, count, size);
	cout << "size = " << size << endl;
	cout << "count = " << count << endl;
	cout << "End of Test 5" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";
	return 0;
}