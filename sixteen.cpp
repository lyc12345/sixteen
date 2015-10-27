#include<bits/stdc++.h>
using namespace std;
int board[5][5];
int tmp[5][5];
const long long mod=1e18+7;
void rotate(int i,int t,int x[5][5]){
		if(t==1) {
				int tmp=x[i][1];
				for(int j=1;j<4;j++) x[i][j]=x[i][j+1];
				x[i][4]=tmp;
		}
		else if(t==2){
				int tmp=x[i][4];
				for(int j=4;j>1;j--) x[i][j]=x[i][j-1];
				x[i][1]=tmp;
		}
		else if(t==3){
				int tmp=x[1][i];
				for(int j=1;j<4;j++) x[j][i]=x[j+1][i];
				x[4][i]=tmp;
		}
		else if(t==4){
				int tmp=x[4][i];
				for(int j=4;j>1;j--) x[j][i]=x[j-1][i];
				x[1][i]=tmp;
		}
}
bool match(){
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					if(board[i][j]!=(i-1)*4+j) return false;
		return true;
}
int rev[5]={0,2,1,4,3};
int thresold;
pair<int,int>ans[101];
int now=0;
bool ok;
void go(int n,int _i,int _j){
		if(match()) {
				printf("match: %d\n",n);
				for(int i=0;i<now;i++) printf("%d %d\n",ans[i].first,ans[i].second);
				ok=true;
		}
		if(ok) return;
		if(n==thresold) return;
		for(int i=1;i<=4;i++){
				for(int j=1;j<=4;j++){
						if(i==_i&&j==rev[_j]) continue;
						rotate(i,j,board);
						ans[now++]=make_pair(i,j);
						go(n+1,i,j);
						if(ok) return;
						now--;
						rotate(i,rev[j],board);
				}
		}
}
int main(){
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					scanf("%d",&board[i][j]);
		ok=false;
		thresold=1;
		while(!ok){
				printf("try thresold:%d\n",thresold);
				go(0,0,0);
				if(ok){
						printf("ID:%d\n",thresold);
						break;
				}
				thresold++;
		}
}
