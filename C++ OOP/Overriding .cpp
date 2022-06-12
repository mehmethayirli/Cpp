#include <iostream>

using namespace std;

class kitap{
	public:
		string isim;
	void bilgiSoyle(){
		cout<<isim<<endl;
	}
};

class roman: public kitap{
	public:
		string rTip; //kisa orta uzun
		
	roman(string isim,string rTip){ //kurucu cons.
		this->isim=isim;
		this->rTip=rTip;
	}
	
	void bilgiSoyle(){
		cout<<"Roman ismi:"<<isim<<" Roman tipi:"<<rTip<<endl;
	}
};

int main(){
		
	roman r1("Sefiller","Uzun");
	r1.bilgiSoyle();
	
	kitap *r1Ebeveyn; //Overriding 
	r1Ebeveyn=&r1;
	r1Ebeveyn->bilgiSoyle();
	
	return 0;
}
