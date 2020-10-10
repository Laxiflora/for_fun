#include <iostream>
#include <cstdlib>
using namespace std;
/*
計算電子時鐘特定亮燈數的可能顯示方式: 23:59:59 , 00:01:03  
*/


//3 0~5, others 0~9
struct digitalClock{
	public:
		int* clock;
		digitalClock(); 
};

digitalClock::digitalClock(){
	clock = new int[10];
	clock[1]=2;
	clock[7]=3;
	clock[4]=4;
	clock[2]=5;
	clock[3]=5;
	clock[5]=5;
	clock[0]=6;
	clock[6]=6;
	clock[9]=6;
	clock[8]=7;
}
/*
遞迴版 有不明BUG 
void recursive_call(int& ans,int round,int target,int previous){
//	cout<<"recursive, round="<<round<<"\ttarget = "<<target<<endl;
	digitalClock temp;
	int number_quan;
	if(round==0)
		number_quan=3;
	else if(round==1&&previous==2)
		number_quan=5;
	else if(round%2==0)
		number_quan=6;
	else
		number_quan=10;
	if(target<0) return;
	for(int i=0;i<number_quan;i++){
		if(round==5&&target==temp.clock[i]) ans++;
		if(round<5){
			recursive_call(ans,round+1,target-temp.clock[i],i);
		}
	}
}
*/

int main(void){
	int input,ans=0;
	cin>>input;
	digitalClock alpha;
//	recursive_call(ans,0,input,0);
/*     迴圈版        */
	for(int i=0;i<3;i++){
		int last[6];
		last[0]=input;
		last[1]=last[0]-alpha.clock[i];
		for(int j=0;j<10;j++){
			if(i==2&&j==4) break;
			last[2]=last[1]-alpha.clock[j];
			for(int k=0;k<6;k++){
				last[3]=last[2]-alpha.clock[k];
				for(int l=0;l<10;l++){
					last[4] = last[3]-alpha.clock[l];
					for(int m=0;m<6;m++){
						last[5] = last[4]-alpha.clock[m];
						for(int n=0;n<10;n++){
							if(last[5]==alpha.clock[n]) ans++;
						}
					}
				}
			}
		}
	}
/*        迴圈版           */
	cout<<ans;
	
}



/*
思維1: 從第一位數開始，0~5的loop，接著第二位數，0~9的loop...  可能性有6*10*6*10*6*10=216000/判別式
，作法有遞迴與迴圈，迴圈醜但遞迴燒空間    五個常數迴圈，O(1)

思維2: 窮舉所有的可能時間，可能性有24*60*60=86400，但還需要更多計算(*6)，O(1) 
*/
