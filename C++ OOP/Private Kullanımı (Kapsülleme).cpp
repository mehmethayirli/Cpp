#include <iostream>

using namespace std;

class Ogrenci{
	private:
	string isim;
	int no;
	
	public:
	void setIsim(string girilenIsim){
		isim=girilenIsim;
	}
		
	void setNo(int girilenNo){
		no=girilenNo;
	}
	
	void veriler(){ //konsola yazma islemi
		cout<<isim<<" "<<no<<endl;
	}
};

int main(){
	
	Ogrenci ogr1;
	ogr1.setIsim("Mehmet");
	ogr1.setNo(5010);
	ogr1.veriler();	//konsola yazdýr
	
	return 0;
}
