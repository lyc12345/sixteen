#include<cstdio>
using namespace std;
int board[5][5];
int root[5][5];
int tmp[5][5];
int min(int a,int b){return a>b?b:a;}
int abs(int a){return a>0?a:-a;}
int copy(int x[5][5],int y[5][5]){
		for(int i=1;i<=4;i++)
				for(int j=1;j<=4;j++)
							x[i][j]=y[i][j];
}
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
bool match(int x[5][5]){
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					if(x[i][j]!=(i-1)*4+j) return false;
		return true;
}
int heuristic(int x[5][5]){
		int mx=-1;
		for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
						int r=(x[i][j]-1)%4;
						int k=(x[i][j]-1)/4;
						k = min(abs(k-i),4-abs(k-i));
						r = min(abs(r-j),4-abs(r-j));
						if(mx<k+r) mx=k+r;
				}
		}
		return mx;
}
bool ok;
int step;
int search(int x[5][5],int g,int bound){
		/*puts("===============");
		for(int i=1;i<=4;i++)
				for(int j=1;j<=4;j++)
						printf("%d%c",x[i][j],j==4?'\n':' ');
		puts("===============");*/
		int f=g+heuristic(x);
		if(f>bound) return f;
		if(match(x)){
				ok=true;
				step=g;
				return 0;
		}
		int min=2147483647;
		for(int i=1;i<=4;i++){
				for(int j=1;j<=4;j++){
						copy(tmp,x);
						rotate(i,j,tmp);
						int t=search(tmp,g+1,bound);
						if(min>t) min=t;
						if(ok) return 0;
				}
		}
		return min;
}
void ida_star(){
		int bound = heuristic(root);
		while(true){
				int t=search(root,0,bound);
				if(ok) break;
				bound=t;
		}
}
int main(){
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
					scanf("%d",&board[i][j]);
		/*for(int i=1;i<=4;i++)
				for(int j=1;j<=4;j++)
						printf("%d%c",board[i][j],j==4?'\n':' ');*/
		copy(root,board);
		ok=false;
		ida_star();
		printf("step = %d\n",step);
}
