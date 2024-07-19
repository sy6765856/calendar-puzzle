#include <stdio.h>
#include <string.h>
#include <ctime>
#include <iostream>
using namespace std;
#define PIECES 9
#define L 5
#define MAX 1000
#define H 9
#define W 6
int n=H,m=W;
int a[PIECES][L][L] = {
{
	{1,1,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0}
},
{
	{1,1,0,0,0},
	{0,1,0,0,0},
	{0,1,0,0,0},
	{0,1,0,0,0},
	{0,0,0,0,0}
},
{
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,0,0,0},
	{1,0,0,0,0}
},
{
	{1,0,0,0,0},
	{1,1,0,0,0},
	{0,1,0,0,0},
	{0,1,0,0,0},
	{0,0,0,0,0}
},
{
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,0,0,0}
},
{
	{0,0,1,0,0},
	{1,1,1,0,0},
	{1,0,1,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
},
{
	{0,1,0,0,0},
	{1,1,0,0,0},
	{1,1,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
},
{
	{1,0,0,0,0},
	{1,1,1,0,0},
	{0,1,0,0,0},
	{0,1,0,0,0},
	{0,0,0,0,0}
},
{
	{0,0,1,0,0},
	{0,0,1,0,0},
	{1,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
}};
clock_t start;
int g[H][W];
struct nod{
	int a[8][L][L];
	int x[8],xx[8],y[8],yy[8];
	int h[8],w[8];
} nd[PIECES];
int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};
void out() {
	for(int x=0;x<n;x++) {
		for(int y=0;y<m;y++) printf("%d ", g[x][y]);
		puts("");
	}
	puts("");
	return;
}
int vis[H][W];
int dig(int x, int y) {
	vis[x][y]=1;
	int cnt=1;
	for(int d=0;d<4;d++) {
		int xx=x+dx[d],yy=y+dy[d];
		if(0<=xx&&xx<n&&0<=yy&&yy<m&&g[xx][yy]==-1&&vis[xx][yy]==-1){
			cnt += dig(xx,yy);
		}
	}
	return cnt;
}
bool impossible() {
	memset(vis,-1,sizeof(vis));
	for(int x=0;x<n;x++)
	for(int y=0;y<m;y++) {
		if(~g[x][y])continue;
		if(~vis[x][y])continue;
		if(dig(x,y)<5) return true;
	}
	return false;
}
void dfs(int index) {
	if(impossible())return;
	if(index > PIECES) {
		out();
		cout << "cost " << (double)(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;
		exit(0);
	}
	nod ndd = nd[index-1];
	for(int k=0;k<8;k++)
	for(int x=0;x<n-ndd.h[k]+1;x++)
	for(int y=0;y<m-ndd.w[k]+1;y++) {
		bool flag=true;
		for(int i=ndd.x[k];i<=ndd.xx[k];i++) {
			for(int j=ndd.y[k];j<=ndd.yy[k];j++) {
				if(ndd.a[k][i][j]==0)continue;
				if(~g[x+i-ndd.x[k]][y+j-ndd.y[k]]) {
					flag=false;break;
				}
			}
			if(!flag)break;
		}
		
		if(flag) {
			for(int i=ndd.x[k];i<=ndd.xx[k];i++) 
			for(int j=ndd.y[k];j<=ndd.yy[k];j++) {
				if(ndd.a[k][i][j]) g[x+i-ndd.x[k]][y+j-ndd.y[k]]=index;
			}
			dfs(index+1);
			for(int i=ndd.x[k];i<=ndd.xx[k];i++) 
			for(int j=ndd.y[k];j<=ndd.yy[k];j++) {
				if(ndd.a[k][i][j]) g[x+i-ndd.x[k]][y+j-ndd.y[k]]=-1;
			}
			
		}
	}
	return;
}
void copy(int a[L][L], int b[L][L]) {
	for(int i=0;i<L;i++) for(int j=0;j<L;j++) a[i][j]=b[i][j];
}
void filp(int a[L][L]) {
	int b[L][L];
	for(int i=0;i<L;i++) for(int j=0;j<L;j++) b[i][L-1-j] = a[i][j];
	copy(a, b);
	return;
}
void rotate(int a[L][L]) {
	int b[L][L];
	for(int j=0;j<L;j++) for(int i=L-1;i>=0;i--) b[j][L-1-i] = a[i][j];
	copy(a, b);
	return;
}
int main(){ 
	start = clock();
	memset(g,-1,sizeof(g));
	for(int i=0;i<PIECES;i++)
	for(int k=0;k<8;k++) {
		copy(nd[i].a[k], a[i]);
		rotate(a[i]);
		if(k==4)filp(a[i]);
	}
	for(int k=0;k<PIECES;k++)
	for(int p=0;p<8;p++) {
		nd[k].x[p]=MAX, nd[k].xx[p]=0, nd[k].y[p]=MAX, nd[k].yy[p]=0;
		for(int i=0;i<L;i++) for(int j=0;j<L;j++) {
			if(nd[k].a[p][i][j]) {
				nd[k].x[p] = min(nd[k].x[p], i), nd[k].xx[p] = max(nd[k].xx[p], i);
				nd[k].y[p] = min(nd[k].y[p], j), nd[k].yy[p] = max(nd[k].yy[p], j);
			}
		}
		nd[k].h[p] = nd[k].xx[p]-nd[k].x[p]+1;
		nd[k].w[p] = nd[k].yy[p]-nd[k].y[p]+1;
	}
	
	int month, day, week;
	puts("plz input integers: month day week:");
	scanf("%d %d %d", &month, &day, &week);
	month--,day--;
	g[month/W][month%W]=0; g[day/W+2][day%W]=0;
	if(week<=3) {
		g[H-2][2+week]=0;
	} else {
		g[H-1][week-2]=0;
	}
	dfs(1);
    return 0;
}
