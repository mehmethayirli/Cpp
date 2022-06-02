#include <iostream>

using namespace std;

int main(){
	
	float kenar;
	float hacim,yanal;
	
	cout<<"Kupun kenari:";
	cin>>kenar;
	
	yanal=6*kenar*kenar;
	hacim=kenar*kenar*kenar;
	
	cout<<"Yanal Alan:"<<yanal<<endl; //cout<<"Yanal Alan:"<<6*kenar*kenar<<endl;
	cout<<"Hacim:"<<hacim<<endl;	  //cout<<"Hacim:"<<kenar*kenar*kenar<<endl;
	
	return 0;
}
