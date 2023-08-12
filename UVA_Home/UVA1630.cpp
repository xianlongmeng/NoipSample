#include<iostream>
#include<cstdio>
#include<sstream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#define INF 1<<29
#define eps 1e-9
#define LD long double
#define LL long long
const int maxn = 100 + 10;
using namespace std;
int dp[maxn][maxn];//str的i下标开始一直到j下标结束的压缩后的最短串长度
string sub[maxn][maxn];//保存str所有子串，也就是从l到r的子串
string str;
int fold(int l, int r)
{
    //枚举法判断重复的长度，不重复返回0
    for (int i = 1; i <= (r - l + 1) / 2;i++)//枚举长度
    {
        int flag = 1;
        if ((r-l+1)%i) continue;//剪枝
        for (int j = l; j +i<= r; j++)
        {
            if (str[j] != str[j + i])
            {
                flag = 0;
                break;
            }
        }
        if (flag) return i;
    }
    return 0;
}

int dfs(int l, int r)
{
    int & ans = dp[l][r];//引用
    if (ans != -1) return ans;
    if (l == r)
    {
        sub[l][r] = str[l];
        return ans = 1;
    }
    ans = 1;
    int res = INF,k;
    for (int i = l; i < r; ++i)
    {
        int temp1 = dfs(l, i) + dfs(i + 1, r);//状态转移
        if (temp1 < res)
        {
            k = i;
            res = temp1;
        }
    }
    sub[l][r] = sub[l][k] + sub[k + 1][r];
    int len= fold(l, r);
    if (len)
    {
        int rep = (r - l + 1) / len;
        stringstream ss;//类似toString()方法
        ss<< rep;
        string t=ss.str();
        string newstr = t + string("(") + sub[l][l + len-1] + string(")");
        int temp2 = newstr.size();
        if (temp2 < res)
        {
            res = temp2;
            sub[l][r] = newstr;
        }
    }
    return ans = res;
}
int main()
{
    while (cin >> str)
    {
        memset(dp, -1, sizeof(dp));
        int right = str.size() - 1;
        dfs(0, right);
        cout << sub[0][right] << endl;
    }
    return 0;
}
