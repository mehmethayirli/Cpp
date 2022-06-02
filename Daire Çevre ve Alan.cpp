#include <iostream>

using namespace std;

int main(){
	
	float yaricap;
	float cevre,alan;
	
	cout<<"Yari cap: ";
	cin>>yaricap;
	
	cevre=2*yaricap*3.14;
	alan=3.14*yaricap*yaricap;
	
	cout<<"Cevre:"<<cevre<<endl; //cout<<"Cevre:"<<2*yaricap*3.14<<endl;
	cout<<"Alan:"<<alan<<endl;	 //cout<<"Alan:"<<3.14*yaricap*yaricap<<endl;
	
	return 0;
}
