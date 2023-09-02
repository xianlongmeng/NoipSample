//#define LOCAL
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

const int maxn = 10000000 + 10;
const int MOD = 100000007;

int vis[maxn];    // 记录是否是素数，素数记 0 ，合数记 1
int phifac[maxn]; // 不超过 i!且与 i!互素的整数个数

// 筛法求素数
void get_primes(int n)
{
    int m = (int)sqrt(n + 0.5);
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= m; i++)
    {
        //如果 i 是素数
        if (!vis[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                vis[j] = 1;
            }
        }
    }
}

int main()
{
    freopen("UVA11440_in.txt", "r", stdin);
    freopen("UVA11440_out.txt", "w", stdout);
    get_primes(10000000);
    phifac[1] = phifac[2] = 1;
    for (int i = 3; i <= 10000000; i++)
    {
        phifac[i] = (long long)phifac[i - 1] * (vis[i] ? i : i - 1) % MOD;
    }

    int n, m;
    while (cin >> n >> m && n && m)
    {
        int ans = phifac[m];
        for (int i = m + 1; i <= n; i++)
        {
            ans = (long long)ans * i % MOD;
        }
        cout << (ans - 1 + MOD) % MOD << endl;
    }
    return 0;
}

