#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;
 
const int maxs = 20;
//((16-2)^2)*0.75
const int maxn = 150;
 
int n,m,cnt,sum;
//G可以定义成G[maxn][5]
//deg(degree) 图论中点连出的边数
int deg[maxn],G[maxn][maxn];
int x[maxn],y[maxn],id[maxn][maxn];
int d[maxn][maxn][maxn];
int s[5],t[5];
int dx[] = {0,0,0,-1,1};
int dy[] = {0,1,-1,0,0};
 
//三个鬼在非墙壁的位置可以用一个int编码
int find_ID(int a,int b,int c){
    return (a<<16)|(b<<8)|c;
}
 
bool conflict(int a,int b,int a2,int b2){
    //两个鬼是exchange位置（违反第2条）
    //两个鬼移动到同一个格子（违反第1条）
    if((a2==b && a==b2) || a2==b2) return true;
    return false;
}
 
//因为要寻找最短路径，所以用bfs
int bfs(){
    queue<int> que;
    //三个鬼初始的位置，对应的步数为0
    d[s[0]][s[1]][s[2]] = 0;
    que.push(find_ID(s[0],s[1],s[2]));
    while(!que.empty()){
        int top = que.front();que.pop();
        //解码，得到三个鬼在非墙壁格子的位置
        int a = (top>>16)&0xff,b = (top>>8)&0xff,c = (top&0xff);
        //找到！此位置等于三个鬼应该在的位置
        if(a==t[0] && b==t[1] && c==t[2]) return d[a][b][c];
        //a鬼可能移动到deg[a]个位置
        for(int i = 0;i < deg[a];i++){
            //a鬼移动到第a2个非墙壁格子
            int a2 = G[a][i];
            for(int j = 0;j < deg[b];j++){
                int b2 = G[b][j];
                if(conflict(a,b,a2,b2)) continue;
                for(int k = 0;k < deg[c];k++){
                    int c2 = G[c][k];
                    //出现过这种情况，成为闭环，遗弃
                    if(d[a2][b2][c2] != -1) continue;
                    if(conflict(a,c,a2,c2)) continue;
                    if(conflict(b,c,b2,c2)) continue;
                    //步数加1
                    d[a2][b2][c2] = d[a][b][c]+1;
                    //编码后，压入堆栈
                    que.push(find_ID(a2,b2,c2));
                }
            }
        }
    }
    return -1;
}
 
int main()
{
    freopen("UVA1601_in.txt","r",stdin);
    freopen("UVA1601_out.txt","w",stdout);
    while(~scanf("%d%d%d\n",&m,&n,&sum) && (m||n||sum)){
        //input map
        char gra[maxs][maxs];
        cnt = 0;
        //三个鬼的位置？
        memset(d,-1,sizeof(d));
        for(int i = 0;i < n;i++) fgets(gra[i],maxs,stdin);
 
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(gra[i][j] != '#'){
                    //x方向 非墙壁（可移动）
                    //y方向 非墙壁
                    //坐标是i，j的格子是第几个非墙壁的格子
                    x[cnt] = i,y[cnt] = j,id[i][j] = cnt;
                    //每个鬼各自初始的位置 source
                    if(islower(gra[i][j])) s[gra[i][j]-'a'] = cnt;
                    //每个鬼各自应该在的位置 target
                    else if(isupper(gra[i][j])) t[gra[i][j]-'A'] = cnt;
                    cnt++;
                }
            }
        }
 
        //每个非墙壁格子，在5种移动之后，成为第id[xx][yy]个非墙格
        for(int i = 0;i < cnt;i++){
            int X = x[i],Y = y[i];
            deg[i] = 0;
            for(int k = 0;k < 5;k++){
                int xx = X+dx[k],yy = Y+dy[k];
                if(gra[xx][yy] != '#') G[i][deg[i]++] = id[xx][yy];
            }
        }
 
        //最多三个鬼，dfs的时候没有三个鬼，也要按三个鬼去计算
        //少于3个鬼
        if(sum <= 2){
            //第2个鬼的初始位置、目标位置、可移动的位置都为cnt
            s[2] = t[2] = G[cnt][0] = cnt;
            //cnt点可移动的位置的个数为1，即只能呆在原地
            deg[cnt++] = 1;
        }
        //少于2个鬼
        if(sum <= 1){
            s[1] = t[1] = G[cnt][0] = cnt;
            deg[cnt++] = 1;
        }
 
        printf("%d\n",bfs());
    }
    return 0;
}