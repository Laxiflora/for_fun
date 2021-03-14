#include <iostream>
#include <cstdlib>
#define T 45
using namespace std;

/**************************
Q5: 輸入一數n(n>=0), 求第n階的帕斯卡三角型組合共最少可換成多少硬幣
硬幣有1,5,10,50,100,500,1000,2000,5000,10000 

ex. 
n= 3 
1 3 3 1
1+3+3+1 = 8 

n=4
1 4 6 4 1
1+4+2+4+1 = 12



***************************/




void bascar_rec(long long n,long long round,long long* array){
	if(round<=n){
		long long* temp = new long long[round+1];
		temp[0]=1;
		for(long long i=1;i<round;i++){
			temp[i] = array[i]+array[i-1];
		}
		temp[round]=1;
		
		//copy
		for(long long i=0;i<=round;i++){
			array[i]=temp[i];
		}
		free(temp);
		bascar_rec(n,round+1,array);
	}
}

int main(void){
	long long n=T;
	long long* array= new long long[T+1];
	
	bascar_rec(n,0,array);
/*	for(long long i=0;i<=T;i++){
		cout<<array[i]<<" ";
	}
*/
	long long sum = 0;
	for(int i=0;i<=T;i++){
		sum=sum+(array[i]/10000);
		array[i]%=10000;
		
		sum=sum+(array[i]/5000);
		array[i]%=5000;
		
		sum=sum+(array[i]/2000);
		array[i]%=2000;
		
		sum=sum+(array[i]/1000);
		array[i]%=1000;
		
		sum=sum+(array[i]/500);
		array[i]%=500;
		
		sum=sum+(array[i]/100);
		array[i]%=100;
		
		sum=sum+(array[i]/50);
		array[i]%=50;
		
		sum=sum+(array[i]/10);
		array[i]%=10;
		
		sum=sum+(array[i]/5);
		array[i]%=5;
		
		sum+=array[i];
	}
	
	cout<<"Ans: "<<sum<<"枚硬幣";
	
	
	
	
	
	
	
	
	
}
