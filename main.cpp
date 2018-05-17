#include <iostream>
#include <list>
#include <string>
using namespace std;

class Score{
	string name;
	string adress;
};

class Warehouse_worker{
	FILE *report;
	public:
		Accept_prod();
		Cancellation_prod();
		Record();
		Report();
};

class Cashier{
	float money;
	FILE *check;
	public:
		Get_money();
		Give_money();
		Change();
};

class Seller{
	FILE *note;
	public:
		Give_refund();
		Record();
		Consignment_Note();
};

class Leadership{
	public:
		Order_products();
		View_statistics();
};

class Product{
	string name;
	int quantity;
	int max_quantity;
	public:
		Get_quantity();
};

class Stock{
	list<Product*> products;
	int max_size;
	int size;
	public:
		Accept();
		Canellation();
		Print();
};

class Money{
	float quantity;
	public:
		virtual void Get_quantity()=0;
};

class Credit_card: public Money{
	float quantity;
	long int number;
	public:
		void Get_quantity(){
			return;
		};
};

class Cash: public Money{
	float quantity;
	public:
		void Get_quantity(){
			return;
		};
};

int main(int argc, char** argv) {
	return 0;
}
