#include <iostream>

using namespace std;

class Insan{
	public:
	string isim;
	int yas;
};

int main(){
	
	Insan insan1,insan2;
	insan1.isim="Mehmet";
	insan1.yas=20;
	insan2.isim="Furkan";
	insan2.yas=13;
	
	cout<<insan1.isim<<" "<<insan1.yas<<endl;
	cout<<insan2.isim<<" "<<insan2.yas<<endl;
	
	return 0;
}
