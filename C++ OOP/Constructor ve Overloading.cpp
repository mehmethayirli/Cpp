#include <iostream>

using namespace std;

class Ogrenci{
	private:
	string isim;
	int no;
	
	public:
    Ogrenci(string girilenIsim,int girilenNo){ //Constructor
		isim=girilenIsim;
		no=girilenNo;
	}	
	
	Ogrenci(string girilenIsim){ //Overloading
		isim=girilenIsim;
		no=0;
	}
	
	void veriler(){ //konsola yazma islemi
		cout<<isim<<" "<<no<<endl;
	}
};

int main(){
	
	Ogrenci ogr1("Mehmet",5010);
	ogr1.veriler();
	Ogrenci ogr2("Furkan");
	ogr2.veriler();
	
	
//Ogr1.isim'e yeni atama icin set fonksiyonlarý yazilmalidir	
	return 0;
}
