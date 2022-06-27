#include<iostream>
 
using namespace std;
 
int main()
{
  int sayi;
  int sayac=0;
  cout<<"Bir Sayi Giriniz: ";
 
  cin>>sayi;
 
 for(int j=2; j<sayi; j++)
     {
      if(sayi % j == 0)
         {
          sayac++;
          break;
         }
     }
  if(sayac == 0)
     {
      cout<<"Sayi Asaldir"<<endl;
     }
 else
      cout<<"Sayi Asal Degildir"<<endl;

	return 0;
 }
 
