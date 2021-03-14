#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int findScareCrowAmount(string describe,int length){
	int ans=0;
	for(int i = 0;i<length;i++){
		if(describe[i]=='.'){
			ans+=1;
			i+=2;
		}
	}
	return ans;
}


int main(void){
	int rows;
	cin>>rows;
	for(int i=0;i<rows;i++){
		string describe;
		int length;
		cin>>length>>describe;
		cout<<findScareCrowAmount(describe,length)<<endl;
	}

}
