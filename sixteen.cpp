#include<bits/stdc++.h>
using namespace std;
int board[5][5];
int tmp[5][5];
vector<int>rec;
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
int thresold;
bool ok;
void go(int n){/*
		puts("===============");
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					printf("%d%c",board[i][j],j==4?'\n':' ');
		puts("===============");*/
		if(match()) printf("match: %d\n",n),ok=true;
		if(n==thresold) return;
		for(int i=1;i<=4;i++){
				rotate(i,1,board);
				go(n+1);
				rotate(i,2,board);
				rotate(i,2,board);
				go(n+1);
				rotate(i,1,board);
				rotate(i,3,board);
				go(n+1);
				rotate(i,4,board);
				rotate(i,4,board);
				go(n+1);
				rotate(i,3,board);
		}
}
int main(){
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					board[i][j]=(i-1)*4+j;
		board[1][1]=2;
		board[1][2]=1;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					printf("%d%c",board[i][j],j==4?'\n':' ');
		ok=false;
		thresold=1;
		while(!ok){
				go(0);
				if(ok){
						printf("ID:%d\n",thresold);
						break;
				}
				thresold++;
		}
		puts("QQ");
		int size=rec.size();
		for(int i=0;i<size;i++) printf("%d ",rec[i]);
		puts("");
}
