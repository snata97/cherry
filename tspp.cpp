#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
//GIT2

class Money{//деньги
float quantity;//количество
	public:
		virtual float Get_quantity()=0;
};

class Credit_card: public Money{
	float quantity;//количество
	public:
		Credit_card(float q){
			quantity=q;
		}
		float Get_quantity(){
			return quantity;
		}
		void Plus_money(float m){
			quantity+=m;
		}
		void Minus_money(float m){
			quantity-=m;
		}
};

class Cash: public Money{
	float quantity;//количество
	public:
		Cash(float q){
			quantity=q;
		}
		float Get_quantity(){
			return quantity;
		}
		void Plus_money(float m){
			quantity+=m;
		}
		void Minus_money(float m){
			quantity-=m;
		}
};

class Product{//Товар
	char name[40];//название
	int quantity;//количество
	float value;
	public:
		Product(char* _n, int _q,float _v){
			strcpy(name,_n);
			quantity=_q;
			value=_v;
		}
		int Get_quantity(){//получить количество
			return quantity;
		}
		char* Get_name(){//получить название
			return name;
		}	
		float Get_value(){//получить цену
			return value;
		}	
		void Plus_quantity(){
			quantity++;
		}
		void Minus_quantity(){
			quantity--;
		}	
		bool In_stock(){// в наличии или нет
			if (quantity>0) return true;
			else false;
		}
};

class Stock{//склад
	public:
		vector<Product*> products;//товары
		void Accept(Product *p){//+товар
			p->Plus_quantity();
		}
		void Cancellation(Product *p){//-товар
			p->Minus_quantity();
		}
		Print(Product *p){;//вывод количества товара
			p->Get_quantity();
			p->In_stock();
		}
		void Filling_the_warehouse(){
			Product *smartphone_samsung=new Product("smartphone_samsung",3,15000);
			products.insert(products.end(),smartphone_samsung);
			Product *smartphone_apple=new Product("smartphone_apple",4,30000);
			products.insert(products.end(),smartphone_apple);
			Product *smartphone_nokia=new Product("smartphone_nokia",2,10000);
			products.insert(products.end(),smartphone_nokia);
			
			Product *laptop_samsung=new Product("laptop_samsung",2,30000);
			products.insert(products.end(),laptop_samsung);
			Product *laptop_apple=new Product("laptop_apple",2,100000);
			products.insert(products.end(),laptop_apple);
			Product *laptop_acer=new Product("laptop_acer",3,50000);
			products.insert(products.end(),laptop_acer);
			Product *laptop_asus=new Product("laptop_asus",1,60000);
			products.insert(products.end(),laptop_asus);
			
			Product *computer_mouse_sven=new Product("computer_mouse_sven",5,2000);
			products.insert(products.end(),computer_mouse_sven);
			Product *computer_mouse_logitech=new Product("computer_mouse_logitech",2,1500);
			products.insert(products.end(),computer_mouse_logitech);
			Product *computer_mouse_rapoo=new Product("computer_mouse_rapoo",3,1000);
			products.insert(products.end(),computer_mouse_rapoo);
			
			Product *computer_keyboard_sven=new Product("computer_keyboard_sven",5,3000);
			products.insert(products.end(),computer_keyboard_sven);
			Product *computer_keyboard_logitech=new Product("computer_keyboard_logitech",2,4000);
			products.insert(products.end(),computer_keyboard_logitech);
			Product *computer_keyboard_rapoo=new Product("computer_keyboard_rapoo",3,2500);
			products.insert(products.end(),computer_keyboard_rapoo);
		}	
};	

class Warehouse_worker{//Работник склада
	ofstream report;//файл с отчетом
	public:
		Accept_prod(Product *p){//принять товар на баланс
			p->Plus_quantity();
			cout<<"Warehouse_worker: The goods are accepted"<<endl;
		}
		Cancellation_prod(Product *p){//списать товар со склада
			p->Minus_quantity();
			cout<<"Warehouse_worker: The goods are written off"<<endl;
		}
		Record(Product *p){//провести учет на складе
			p->In_stock();
			if(p->Get_quantity()<2) Accept_prod(p);
		}
		Report(Stock sklad){//сформировать отчет по изменению загруженности склада
			report.open("report.txt");
			for(int i=0;i<sklad.products.size();i++){
				report<<"Количество"<<(sklad.products[i])->Get_name()<<"="<<(sklad.products[i])->Get_quantity();
			}
			report.close();
			cout<<"Warehouse_worker: the report is formed"<<endl;
		}
};

class Customer{//Покупатель
	char FIO[50];
	Cash *cash;
	Credit_card *credit_card;
	char tovar[30];
	bool check;
	public:
		Customer(char *fio,float _cash,float _card, char *_tovar,bool _check){
			strcpy(FIO,fio);
			cash=new Cash(_cash);
			credit_card=new Credit_card(_card);
			strcpy(tovar,_tovar);
			check=_check;
		}
		Get_money(float m){//принять деньги
			cash->Plus_money(m);
			cout<<"Customer: money accepted"<<endl;
		}
		Give_money(float m){//выдать деньги
			if(m>cash->Get_quantity())
				cash->Minus_money(m);
			else credit_card->Minus_money(m);
			cout<<"Customer: money is given away"<<endl;
		}
		char* Get_FIO(){
			return FIO;
		}
		char* Get_tovar(){
			return tovar;
		}
		bool Get_check(){
			return check;
		}
};

class Cashier{//Кассир
	float money;//деньги
	ofstream check;//чек
	public:
		bool Get_money(float m, Customer *c, Product *p){//принять деньги
			if(m<p->Get_value()){
				cout<<"Not enough money!!!"<<endl;
				return false;
			}
			else if(m==p->Get_value()) return true;
			else {
				cout<<"Take change with the purchase"<<endl;
				c->Get_money(m-p->Get_value());
				cout<<"Cashier: money is given out "<<endl;
				return true;
			}
		}
		bool Give_money(Customer *c, Product *p){//выдать деньги
			c->Get_money(p->Get_value());
			cout<<"Cashier: money is given out "<<endl;
			return true;
		}
		void Form_a_check(Product *p){//сформировать чек
			check.open("check.txt");
			check<<"Количество"<<p->Get_name()<<"="<<p->Get_quantity();
			check.close();
			cout<<"Cashier: the check is formed"<<endl;
		}
};

class Seller{//Продавец
	ofstream note;//накладная
	public:
		bool Give_refund(bool check){//оформить возврат
			if(check){
				return true;
			}
			else return false;
		}
		bool Record(Product *p){//проверить наличие
			if(p->In_stock()) {
				cout<<"Seller: Goods in stock. Name: "<<p->Get_name()<<", Total:"<<p->Get_quantity()<<endl;
				return true;
			}
			else {
				cout<<"Seller: The product is out of stock"<<endl;
				return false;
			}
		}
		Consignment_Note(Product *p,Customer *c){//сформировать накладную для покупателя
			note.open("note.txt");
			note<<c->Get_FIO()<<endl;
			note<<"Название товара"<<p->Get_name();
			note.close();
		}
};

class Leadership{//Руководство
	public:
		Order_products();//заказать товары
		View_statistics();//посмотреть статистику по продажам
};

void Buy(Stock *sklad,Customer *customer,Seller *seller,Cashier *cashier,Warehouse_worker *w_w){
	bool flag=false;
	for(int i=0;i<sklad->products.size();i++){
		if(strcmp(customer->Get_tovar(),sklad->products[i]->Get_name())==0) {
			cout<<"Seller: This product is in our store, but you need to see the availability in stock"<<endl;
			flag=seller->Record(sklad->products[i]);			
			seller->Consignment_Note(sklad->products[i],customer);
			cashier->Get_money(customer->Give_money(sklad->products[i]->Get_value()),customer,sklad->products[i]);
			cashier->Form_a_check(sklad->products[i]);
			w_w->Cancellation_prod(sklad->products[i]);
			w_w->Record(sklad->products[i]);
		}
	}
	if(flag==false) {
		cout<<"Seller:"<<customer->Get_tovar()<<" is no longer in our shop"<<endl;
		delete customer;
	}	
	cout<<"Seller: Goodbye"<<endl;
}

void Return(Stock *sklad,Customer *customer,Seller *seller,Cashier *cashier,Warehouse_worker *w_w){
	bool flag=false;
	for(int i=0;i<sklad->products.size();i++){
		if(strcmp(customer->Get_tovar(),sklad->products[i]->Get_name())==0) {
			flag=seller-> Give_refund(customer->Get_check());
			if(flag==true){
				cout<<"Seller:goods "<<customer->Get_tovar()<<" can be returned"<<endl;
				cashier->Give_money(customer,sklad->products[i]);
				w_w->Accept_prod(sklad->products[i]);
			}
		}
	}
	if(flag==false) {
		cout<<"Seller:return of goods "<<customer->Get_tovar()<<" is not possible"<<endl;
		delete customer;
	}
	cout<<"Seller: Goodbye"<<endl;
}

int main(int argc, char** argv) {
	char tovar[40];bool flag=false;
	Stock *sklad=new Stock;
	sklad->Filling_the_warehouse();
	Cashier *cashier=new Cashier;
	Seller *seller=new Seller;
	Warehouse_worker *w_w=new Warehouse_worker;
	cout<<"1.Buyer who wants to buy goods"<<endl<<endl;
	Customer *customer1=new Customer("Ivamov Ivan Ivavnovich",2600,20000,"smartphone_samsung",false);
	Buy(sklad,customer1,seller,cashier,w_w);	
	cout<<endl<<"2.A buyer who wants to buy a product that is not in the store"<<endl<<endl;
	Customer *customer2=new Customer("Petrov Petr Petrovich",3000,100000,"smartphone_sony",false);
	Buy(sklad,customer2,seller,cashier,w_w);	
	cout<<endl<<"3.The buyer who wants to return the goods"<<endl<<endl;
	Customer *customer3=new Customer("Kyrluk Petr Alekseevich",3000,100000,"smartphone_samsung",true);
	Return(sklad,customer3,seller,cashier,w_w);
	cout<<endl<<"4.The buyer who wants to return the goods, but he does not have a receipt"<<endl<<endl;
	Customer *customer4=new Customer("Kyrluk Petr Alekseevich",3000,100000,"smartphone_samsung",false);
	Return(sklad,customer4,seller,cashier,w_w);
	return 0;
}
