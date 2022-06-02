#include <iostream>

using namespace std;

int main(){
	
	int sayi,sonuc=1;
	
	cout<<"Kac faktoriyel:";
	cin>>sayi;
	
	while(sayi>0){
		sonuc*=sayi;
		sayi--;
	}
	
	cout<<"Faktoriyel:"<<sonuc<<endl;
	
	return 0;
}
