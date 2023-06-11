/* *uva690. 暴力搜索版本
 *TLE版本 + 小剪枝 = 过了?
 */
#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
using namespace std;

const int maxn = 21;// 样例最大19
const int INF = 220;// 最大是 maxd * n - 1, 反正空间不值钱
int table[5][INF]; //暴力模拟·保留表·
int minstep, n, maxd,best;
vector<int> pos[maxn];// 一个时间片可能使用多个单元部件

void print_t()//调试用打印保留表
{
    for(int i = 0;  i < 5; ++i)
    {
        for(int j = 0; j < 49; ++j) printf("%d ",table[i][j]); putchar('\n');
    }
    putchar('\n');
}

bool check(int cur)//检查该个时间片内能不能放指令, 可以使用二进制位表示用到的单元
{
    for(int i = cur; i < cur + n; ++i)
        for(const auto now: pos[i-cur]) if(table[now][i] != 0){ /*cout<<"false\n";*/ return false; } 
    return true;
}

void go(int cur,int val)// 放入指令更改保留表,val为0时回溯
{
     for(int i = cur; i < cur + n; ++i)
        for(const auto now: pos[i-cur]) table[now][i] = val;
}
void dfs(int d,int cur)
{
    if(d == maxd + 1 ) { best = min(cur - 1,best); /*printf("best:%d\n",best);*/ return ; }
    for(int i = cur; i <= best; ++i)
    {
        if(i + (maxd - d) * minstep >= best) return;// 小剪枝，
        if(!check(i)) continue;
        go(i,d);
        dfs(d + 1,i + 1);
        go(i,0);
    }
}

int main(){
    freopen("UVA690_in.txt","r",stdin);
    freopen("UVA690_out.txt","w",stdout);
    while(scanf("%d",&n) == 1  && n)
    {
        getchar();
        memset(table,0,sizeof(table));
        for(auto && temp: pos) temp.clear();
        for(int i = 0; i < 5; ++i)
        {
            for(int j = 0; j < n; ++j) 
            {
                char temp; scanf("%c",&temp);
                if(temp == 'X')  { table[i][j] = 1; pos[j].push_back(i); }// 储存单个时间片用到的所有单元
            }
            getchar();
        }
        // 最后一段坐标范围 [(maxd - 1) * n, maxd * n -1]
        for(int i = 1; i <= n; ++i) if(check(i)) { minstep = i; break; } //找到最小步长f(1)
        best = 9 * n , maxd = 10;        
        dfs(2,1);
        printf("%d\n",best + n );
    } 
    return 0;
}