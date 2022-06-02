#include<iostream>

using namespace std;
 
int main() {

	int sayi1,sayi2,a,b;
	
	cout<<"2 Sayi giriniz.."<<endl;
	cin>>sayi1>>sayi2;
	
	a=sayi1;
	b=sayi2;

	cout<<"A*B:"<<a*b<<endl;
	cout<<"A-B:"<<a-b<<endl;
	cout<<"A+B:"<<a+b<<endl;
	
	if(a>b)
		cout<<"A/B:"<<a/b<<endl;
	else if(b<a)
		cout<<"B/A:"<<b/a<<endl;
	
	return 0;
}
