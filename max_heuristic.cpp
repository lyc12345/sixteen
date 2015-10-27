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
int heuristic(int x[5][5]){
		int mx=-1;
		for(int i=1;i<=4;i++){
				for(int j=1;j<=4;j++){
						int r=(x[i][j]-1)%4;
						int k=(x[i][j]-1)/4;
						k = min(abs(k-i+1),4-abs(k-i+1));
						r = min(abs(r-j+1),4-abs(r-j+1));
						if(mx<k+r) mx=k+r;
				}
		}
		return mx;
}
bool match(){
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					if(board[i][j]!=(i-1)*4+j) return false;
		return true;
}
int rev[5]={0,2,1,4,3};
int bound;
pair<int,int>ans[101];
int now=0;
bool ok;
int go(int bound,int g,int _i,int _j){
		if(match()) {
				printf("match bound: %d\n",bound);
				for(int i=0;i<now;i++) printf("%d %d\n",ans[i].first,ans[i].second);
				ok=true;
		}
		if(ok) return bound;
		int h=heuristic(board);
		int f=g+h;
		if(f>bound) return f;
		int min=1e9+10;
		for(int i=1;i<=4;i++){
				for(int j=1;j<=4;j++){
						if(i==_i&&j==rev[_j]) continue;
						rotate(i,j,board);
						ans[now++]=make_pair(i,j);
						int tmp=go(bound,g+1,i,j);
						if(ok) return tmp;
						if(tmp<min) min=tmp;
						now--;
						rotate(i,rev[j],board);
				}
		}
		return min;
}
int main(){
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++) board[i][j]=4*(i-1)+j;
					//scanf("%d",&board[i][j]);
		board[4][3]=16;
		board[4][4]=15;
		ok=false;
		bound=heuristic(board);
		while(!ok){
				printf("try bound:%d\n",bound);
				int b=go(bound,0,0,0);
				if(ok){
						printf("IDA bound:%d\n",b);
						break;
				}
				bound=b;
		}
}
