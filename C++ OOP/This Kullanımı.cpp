#include <iostream>

using namespace std;

class Ogrenci{
	private:
	string isim;
	int no;
	
	public:
    Ogrenci(string isim,int no){ //Constructor
		this->isim=isim;
		this->no=no;
	}	
	 
	void veriler(){ //konsola yazma islemi
		cout<<isim<<" "<<no<<endl;
	}
};

int main(){
	
	Ogrenci ogr1("Mehmet",5010);
	ogr1.veriler();
	
	return 0;
}
