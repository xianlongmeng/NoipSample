#include<cstdio>
#define ri register int
using namespace std;
int a[8][8];
int n[25],tong[10];
char ans[100];
char c[9]={'\0','A','B','C','D','E','F','G','H'};
int fan[9]={0,6,5,8,7,2,1,4,3};//逆操作 
int k,f;
int read(){//快读 
	int x=0;char c=getchar();
	while(c>'9'||c<'0') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
void cz(int x){//模拟 
	int t;
	if(x==1){
		t=a[1][3];
		for(ri i=1;i<=6;++i) a[i][3]=a[i+1][3];
		a[7][3]=t;
	}
	if(x==2){
		t=a[1][5];
		for(ri i=1;i<=6;++i) a[i][5]=a[i+1][5];
		a[7][5]=t;
	}
	if(x==3){
		t=a[3][7];
		for(ri i=7;i>=2;--i) a[3][i]=a[3][i-1];//注意倒序 
		a[3][1]=t;
	}
	if(x==4){
		t=a[5][7];
		for(ri i=7;i>=2;--i) a[5][i]=a[5][i-1];
		a[5][1]=t;
	}
	if(x==5){
		t=a[7][5];
		for(ri i=7;i>=2;--i) a[i][5]=a[i-1][5];
		a[1][5]=t;
	}
	if(x==6){
		t=a[7][3];
		for(ri i=7;i>=2;--i) a[i][3]=a[i-1][3];
		a[1][3]=t;
	}
	if(x==7){
		t=a[5][1];
		for(ri i=1;i<=6;++i) a[5][i]=a[5][i+1];//注意是从1到6 
		a[5][7]=t;
	}
	if(x==8){
		t=a[3][1];
		for(ri i=1;i<=6;++i) a[3][i]=a[3][i+1];
		a[3][7]=t;
	}
}
void pre(){//预处理a 
	a[1][3]=n[1],a[1][5]=n[2];
	a[2][3]=n[3],a[2][5]=n[4];
	for(ri i=1;i<=7;++i) a[3][i]=n[i+4];
	a[4][3]=n[12],a[4][5]=n[13];
	for(ri i=1;i<=7;++i) a[5][i]=n[i+13];
	a[6][3]=n[21],a[6][5]=n[22];
	a[7][3]=n[23],a[7][5]=n[24];
}
bool pd(){//判断是否符合题意 
	int k=a[3][3];
	for(ri i=3;i<=5;++i)
		for(ri j=3;j<=5;++j)
		{
			if(i==4&&j==4) continue;
			if(a[i][j]!=k) return 0;
		}
	return 1;
}
int max(int x,int y,int z){//三个数比较大小 
	if(y>x) x=y;
	if(z>x) x=z;
	return x;
}
int js(){//预估函数 
	tong[1]=tong[2]=tong[3]=0;
	for(ri i=3;i<=5;++i)
		for(ri j=3;j<=5;++j)
		{
			if(i==4&&j==4) continue;//4,4是空的 
			tong[a[i][j]]++;
		}
	return 8-max(tong[1],tong[2],tong[3]);//即剩下多少个不同的 
}
void dfs(int s,int la){//IDA* 
	if(s>=k) return;
	for(ri i=1;i<=8;++i)
	{
		if(i==fan[la]) continue;//如果是上一次操作的逆过程，那么显然无异议，剪枝 
		cz(i);//操作 
		ans[s]=c[i];//记录操作 
		int tmp=js()+s;//预估 
		if(pd())//判断是否到达目标态 
		{
			f=1;
			return;
		}
		if(tmp<=k) dfs(s+1,i);//剪枝 
		if(f) return;
		cz(fan[i]);//复原操作 
		ans[s]=c[0];//可有可无 
	}
}
void solve(){
	for(ri i=1;i<=24;++i)
	{
		n[i]=read();
		if(n[i]==0) return;
	}
	pre();k=f=0;
	if(pd())//特判 
	{
		printf("No moves needed\n");
		printf("%d\n",a[3][3]);//注意输出这个，注意不要打多了\n 
		return;
	}
	while(++k)//限定搜索深度，迭代加深 
	{
		dfs(0,0);
		if(f)//找到答案 
		{
			for(ri i=0;i<k;++i) printf("%c",ans[i]);
			printf("\n%d\n",a[3][3]);
			break;//退出 
		}
	}
}
int main(){
    freopen("UVA1343_in.txt","r",stdin);
    freopen("UVA1343_out.txt","w",stdout);
	n[1]=1;
	while(n[1]) solve();
	return 0;
}
