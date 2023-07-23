#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef double db;
typedef pair <int, int> pii;
#define x first
#define y second
const int N = 55;

int n;
pii a[N];
namespace calc {
    db dis(int i, int j) //a[i] 到 a[j] 的距离
    {
        db dx = a[i].x - a[j].x, dy = a[i].y - a[j].y;
        return sqrt(dx * dx + dy * dy);
    }
    db area(int i, int j, int k) //三角形 a[i],a[j],a[k] 的面积
    {
        db a = dis(i, j), b = dis(i, k), c = dis(j, k);
        db s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    bool all_out_triangle(int a, int b, int c) //是否其余的全部点均在 三角形a[i],a[j],a[k] 外面
    {
        for (int i = 1; i <= n; i++)
            if (i != a && i != b && i != c)
            {
                db x = area(a, b, c);
                db y = area(a, b, i) + area(a, i, c) + area(i, b, c);
                if (fabs(x - y) < 1e-5) return false; //即：x不等于y。这样写是防止精度丢失
            }
        return true;
    }
};

db dp[N][N];
db MAX(db x, db y, db z) {return max(x, max(y, z));} //取 max(x, y, z)
void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);

    memset(dp, 127, sizeof dp); //double 初始化要用 127 而不是 0x3f
    for (int i = 1; i < n; i++) dp[i][i + 1] = 0; //只有两个点
    for (int i = 1; i <= n - 2; i++) dp[i][i + 2] = calc::area(i, i + 1, i + 2); //有三个点，答案就是这个三角形的面积

    for (int len = 3; len <= n; len++) //区间 DP
        for (int i = 1, j = len; j <= n; i++, j++)
            for (int k = i + 1; k < j; k++)
                if (calc::all_out_triangle(i, j, k))
                    dp[i][j] = min(dp[i][j], MAX(dp[i][k], dp[k][j], calc::area(i, j, k)) );
    printf("%.1lf\n", dp[1][n]);
}
int main()
{
    ios::sync_with_stdio(false);
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
