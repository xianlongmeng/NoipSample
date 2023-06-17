#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define INF 0x3f3f3f3f

using namespace std;

const int maxn = 20;
int n;
int gra[maxn][maxn];
int vis[maxn];

bool dfs(const int sit,int fa,int u){
    vis[u] = -1;
    for(int v = 0;v < n;v++){
        if(!gra[u][v] || vis[v]==1 || v==fa || !(sit&(1<<v))) continue;
        if(vis[v] < 0) return false;
        if(!vis[v] && !dfs(sit,u,v)) return false;
    }
    vis[u] = 1;
    return true;
}

bool check(const int sit,int &res){
    memset(vis,0,sizeof(vis));
    for(int u = 0;u < n;u++){
        if(!(sit&(1<<u))) continue;
        if(!vis[u]){
            if(!dfs(sit,u,u)) return false;
            res++;
        }
    }

    for(int u = 0;u < n;u++){
        if(!(sit&(1<<u))) continue;
        int cnt = 0;
        for(int v = 0;v < n;v++){
            if(gra[u][v] && sit&(1<<v)) cnt++;
            if(cnt > 2) return false;
        }
    }
    return true;
}

int iCase = 1;

int main()
{
    freopen("UVA818_in.txt","r",stdin);
    freopen("UVA818_out.txt","w",stdout);
    while(~scanf("%d",&n) && n){
        int x,y;
        memset(gra,0,sizeof(gra));
        while(scanf("%d%d",&x,&y) && (x!=-1 && y!=-1)){
            x--,y--;
            gra[x][y] = gra[y][x] = 1;
        }
        int Min = INF;
        for(int i = (1<<n)-1;i >= 0;i--){
            int res = 0;
            if(check(i,res)){
                int cnt = 0;
                for(int j = 0;j < n;j++){
                    if(!(i&(1<<j))) cnt++;
                }
                if(res-1 <= cnt) Min = min(Min,cnt);
                if(Min == 0) break;
            }
        }
        printf("Set %d: Minimum links to open is %d\n",iCase++,Min);
    }
    return 0;
}