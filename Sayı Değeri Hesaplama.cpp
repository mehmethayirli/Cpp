#include <iostream>

using namespace std;

int main(){
	
	int sayi,toplam=0,yuzbinler,onbinler,binler,yuzler,onlar,birler;
	
	cout<<"6 basamakli bir sayi giriniz: ";
	cin>>sayi;
	
	yuzbinler=sayi/100000;
	onbinler=(sayi%100000)/10000;
	binler=(sayi%10000)/1000;
	yuzler=(sayi%1000)/100;
	onlar=(sayi%100)/10;
	birler=sayi%10;
	toplam=yuzbinler+onbinler+binler+yuzler+onlar+birler;
	
	cout<<yuzbinler<<" "<<onbinler<<" "<<binler<<" "<<yuzler<<" "<<onlar<<" "<<birler<<" "<<endl;
	cout<<"Basamak Degerleri Toplami:"<<toplam;
	
	return 0;
}
