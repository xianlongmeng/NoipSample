#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
#define N (int)(25)

int n,m,k,id,f[N][N][N][N],sum[N][N];
int getsum(int a,int b,int c,int d)
{return sum[c][d]+sum[a-1][b-1]-sum[c][b-1]-sum[a-1][d];}
int dp(int x1,int y1,int x2,int y2)
{
    int t=getsum(x1,y1,x2,y2);
    if(!t)return INF;
    if(t==1)return 0;
    int &d=f[x1][y1][x2][y2];
    if(d!=INF)return d;
    for(int i=x1; i<x2; i++)
        d=min(d,dp(x1,y1,i,y2)+dp(i+1,y1,x2,y2)+y2-y1+1);
    for(int i=y1; i<y2; i++)
        d=min(d,dp(x1,y1,x2,i)+dp(x1,i+1,x2,y2)+x2-x1+1);
    return d;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    // freopen("check.in","r",stdin);
    // freopen("check.out","w",stdout);
    while(cin >> n >> m >> k && n && m)
    {
        memset(sum,0,sizeof(sum));
        memset(f,0x3f,sizeof(f));
        for(int i=1,x,y; i<=k; i++)
            cin >> x >> y,sum[x][y]=1;
        for(int i=1; i<=n; i++) for(int j=1; j<=m; j++)
                sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
        cout << "Case "<< ++id << ": " << dp(1,1,n,m) << '\n';
    }
    return 0;
}
