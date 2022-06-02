#include <iostream>
#include <fstream>

using namespace std;

int main(){
	
	ifstream dosya("Dosya.txt");
	
	int no[4];
	string isim[4];
	
	int i=0;
	while(dosya){
		dosya>>no[i]>>isim[i];
		i++;
	}
	
	for(i=0;i<4;i++){
		cout<<"No:"<<no[i];
		cout<<" Isim:"<<isim[i]<<endl;
	}
	
	return 0;
}
