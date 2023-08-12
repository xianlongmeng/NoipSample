#include<iostream>
#include<cstdio>
#include<sstream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>

using namespace std;
const int N = 110;
char a[N];
int num[N];
int f[N][N];
int p[N][N];
bool fold[N][N];

inline bool check(int l, int r, int len) // 判断 [l,r] 能否折成每段 len 个字符
{
    for (int i = l; i <= r - len; i++)
        if (a[i] != a[i + len]) return false;
    return true;
}

inline void print(int l, int r)
{
    if (l == r)
    {
        putchar(a[l]);
        return;
    }
    if (!fold[l][r])
    {
        print(l, p[l][r]);
        print(p[l][r] + 1, r);
        return;
    }
    else
    {
        printf("%d(", (r - l + 1) / (p[l][r] - l + 1));
        print(l, p[l][r]);
        putchar(')');
        return;
    }
}

int main()
{
    for (int i = 1; i <= 100; i++)
        num[i] = num[i / 10] + 1; // 预处理num[i]
    while (cin >> a + 1)
    {
        int n = strlen(a + 1);
        memset(f, 0x3f, sizeof f);
        memset(p, 0, sizeof p);
        memset(fold, 0, sizeof fold);
        for (int i = 1; i <= n; i++)
            f[i][i] = 1;
        for (int len = 2; len <= n; len++)
            for (int l = 1; l + len - 1 <= n; l++)
            {
                int r = l + len - 1;
                for (int k = l; k < r; k++)
                {
                    if (f[l][r] > f[l][k] + f[k + 1][r])
                    {
                        f[l][r] = f[l][k] + f[k + 1][r];
                        p[l][r] = k;
                    }
                }
                for (int k = l; k < r; k++)
                {
                    int a = k - l + 1;
                    if (len % a) continue;
                    if (check(l, r, a) && f[l][r] > f[l][k] + num[len / a] + 2)
                    {
                        f[l][r] = f[l][k] + num[len / a] + 2;
                        fold[l][r] = true;
                        p[l][r] = k;
                    }
                }
            }
        print(1, n);
        puts("");
    }
    return 0;
}