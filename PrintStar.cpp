#include <iostream>
#include <cstdlib>
using namespace std;

int main(void){
	int number;
	cin>>number;
	for(int i=number;i>0;i--){
		for(int j=number-i;j>0;j--){
			cout<<"*";
		}
		cout<<"-";
		for(int j=0;j<i;j++){
			cout<<"*";
		}
		cout<<endl;
	}
}
