#include <iostream>

using namespace std;

int main(){
	
	string id;
	string sifre;
	
	string idKontrol="admin";
	string sifreKontrol="admin0";
	
	cout<<"Id:";
	cin>>id;
	cout<<"Sifre:";
	cin>>sifre;
	
	if(id==idKontrol && sifre==sifreKontrol)
		cout<<"Giris Basarili"<<endl;
	
	else if(id==idKontrol || sifre==sifreKontrol)
		cout<<"Id veya Sifre hatali"<<endl;
	
	else
		cout<<"Id ve Sifre hatali"<<endl;
	
	return 0;
}
