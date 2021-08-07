#include<iostream>
#include <sstream>
#include<string>
#include<vector>
using namespace std;

#define MAX_INPUT_LEN 60
#define ORDER_CAPACITY 10

struct RepairOrder
{
	string sName;
	short iYear;	
	short ticket;
	int iPriority;
};

class TransactionPQueue
{
	RepairOrder orders[10];
	int size;
	int ticket;
	

	void tokenize(std::string const &str, const char* delim,
            std::vector<std::string> &out)
	{
		std::string::size_type beg = 0;
		for (auto end = 0; (end = str.find(delim, end)) != std::string::npos; ++end)
		{
			out.push_back(str.substr(beg, end - beg));
			beg = end + 1;
		}
 
		out.push_back(str.substr(beg));
	}

	void Enqueue(RepairOrder order)
	{
		if(size >= ORDER_CAPACITY)
		{
			cout << "Queue is full"<<endl;
			return;
		}
		//Increase the size
		size++;
		ticket++;

		//Insert the element
		orders[size].sName = order.sName;
		orders[size].iYear = order.iYear;
		orders[size].iPriority = order.iPriority;
		orders[size].ticket = ticket;		
	}

	// Function to check the top element
	int peek()
	{
		int highestPriority = INT_MIN;
		int ind = -1;
 
		// Check for the element with
		// highest priority
		for (int i = 0; i <= size; i++) {
 
			// If priority is same choose
			// the element with the
			// highest ticket value
			if (highestPriority
				== orders[i].iPriority
				&& ind > -1
				&& orders[ind].ticket
					   > orders[i].ticket) {
				highestPriority = orders[i].iPriority;
				ind = i;
			}
			else if (highestPriority
				< orders[i].iPriority) {
					highestPriority = orders[i].iPriority;
				ind = i;
			}
		} 
		// Return position of the element
		return ind;
	}

	// Function to remove the element with
	// the highest priority
	void dequeue()
	{
		if(size < 0)
		{
			cout<<"Queue is Empty"<<endl;
			return;
		}

		// Find the position of the element
		// with highest priority
		int ind = peek();
 
		// Shift the element one index before
		// from the position of the element
		// with highest priortity is found
		cout<<" (output:"<<orders[ind].sName<<")"<<endl;
		for (int i = ind; i < size; i++) {
			orders[i] = orders[i + 1];
		}
 
		// Decrease the size of the
		// priority queue by one
		size--;
		ticket--;
	}
	public:
	TransactionPQueue()
	{
		size = -1;
	}
		
	void ProcessTransaction()
	{
		//Get the user input
		string inputTrans;
		getline(cin, inputTrans);
		if(inputTrans.compare("service") == 0)
			dequeue();
		else if(inputTrans.compare("end-of-file") == 0)
			cout<<"(output: There are " <<std::to_string(size + 1) <<" remaining repair orders in the queue.)" << endl;
		else
		{
			std::vector<string> out;
			RepairOrder order;
			tokenize(inputTrans, "-", out);
			if(out.size() < 3)
			{
				cout<<"Invalid Input"<<endl;
				return;
			}

			if(out[2] == "y")
				order.iPriority = 3;
			else
			{
				int year =std::stoi(out[1]);
				if(year > 2021)
					cout<<"Invalid Input"<<endl;

				if((2021 - year) < 6)
					order.iPriority = 2;
				else
					order.iPriority = 1;
			}

			order.sName = out[0];
			order.iYear = std::stoi(out[1]);
			order.ticket = ticket;
			Enqueue(order);
		}
	}
};

int main()
{
	TransactionPQueue t;
	while(1)
	{
		t.ProcessTransaction();
	}
	return 0;
}