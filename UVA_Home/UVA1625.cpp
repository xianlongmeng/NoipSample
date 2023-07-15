//
// Created by long meng on 2023/7/15.
//
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;

const int maxn = 5000 + 5;
const int INF = 10000000;

char p[maxn], q[maxn];
int sp[26], sq[26], ep[26], eq[26];
int d[maxn][maxn], c[maxn][maxn];

int main()
{
    //freopen("D:\\txt.txt", "r", stdin);
    int T, n, m;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s%s", p + 1, q + 1);
        //cout << p + 1 << " " << q + 1 << endl;
        n = strlen(p + 1);
        m = strlen(q + 1);

        //将字母转化成数字
        for (int i = 1; i <= n; i++)  p[i] -= 'A';
        for (int i = 1; i <= m; i++)  q[i] -= 'A';

        //预处理
        for (int i = 0; i < 26; i++)
        {
            sp[i] = sq[i] = INF;
            ep[i] = eq[i] = 0;
        }

        //预处理，计算出序列1中每个字符的开始位置和结束位置
        for (int i = 1; i <= n; i++)
        {
            sp[p[i]] = min(sp[p[i]], i);
            ep[p[i]] = i;
        }

        //预处理序列2
        for (int i = 1; i <= m; i++)
        {
            sq[q[i]] = min(sq[q[i]], i);
            eq[q[i]] = i;
        }

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if (!i && !j)  continue;
                int v1 = INF, v2 = INF;
                if (i)  v1 = d[i-1][j] + c[i-1][j];        //从p中取颜色
                if (j)  v2 = d[i][j - 1] + c[i][j - 1];    //从q中取颜色
                d[i][j] = min(v1, v2);

                //更新c数组
                if (i)
                {
                    c[i][j] = c[i - 1][j];
                    if (sp[p[i]] == i && sq[p[i]] > j)  c[i][j]++;
                    if (ep[p[i]] == i && eq[p[i]] <= j) c[i][j]--;
                }

                else if (j)
                {
                    c[i][j] = c[i][j - 1];
                    if (sq[q[j]] == j && sp[q[j]] > i)  c[i][j]++;
                    if (eq[q[j]] == j && ep[q[j]] <= i) c[i][j]--;
                }
            }
        }
        cout << d[n][m] << endl;
    }
    return 0;
}