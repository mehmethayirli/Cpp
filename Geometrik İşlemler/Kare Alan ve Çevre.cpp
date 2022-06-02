#include <iostream>

using namespace std;

int main(){
	
	float kenar;
	float cevre,alan;
	
	cout<<"Karenin bir kenari:";
	cin>>kenar;
	
	cevre=kenar*4;
	alan=kenar*kenar;
	
	cout<<"Cevre:"<<cevre<<endl; //cout<<"Cevre:"<<kenar*4<<endl;
	cout<<"Alan:"<<alan<<endl;   //cout<<"Alan:"<<kenar*kenar<<endl;
	
	return 0;
}
