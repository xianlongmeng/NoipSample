#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
 
using namespace std;
 
struct cube {
    char v;
    char x;// 知道两个方向的颜色，第三个方向的颜色就知道了,故忽略y
};
 
struct State {
    vector<cube> cubes;
    int d;// 步数
};
 
int x, y;// 初始空格位置
int des_x, des_y;// 目标空格位置
 
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
 
char ans[9];
 
bool vst[4999][5987];
 
// 双hash
void Hash(const State& st,int(&hash) [2]){
    hash[0]=hash[1]=0;
    const int Base1=11,Mod1=4999;
    const int Base2=13,Mod2=5987;
    for(int i=0;i<9;i++){
        hash[0]=(hash[0]*Base1+(st.cubes[i].v-'0'))%Mod1;
        if(st.cubes[i].v=='E') continue;
        hash[1]=(hash[1]*Base2+(st.cubes[i].x-'0'))%Mod2;
    }
}
 
bool flip(State &v, const int &xx, const int &yy, const int &dir) {
    int xxx = xx + dx[dir], yyy = yy + dy[dir];// 移动后坐标
    // 越界
    if (xxx > 2 || xxx < 0 || yyy > 2 || yyy < 0) return false;
    int idx1 = xx * 3 + yy, idx2 = xxx * 3 + yyy;// 坐标对应的数组下标,分别为空格和翻转的立方体
    v.cubes[9].x = '0' + xxx, v.cubes[9].v = '0' + yyy;// 保存空格位置
    // 朝哪个方向翻转，就会交换z的颜色和那个方向的颜色
    // 只将空格位置改成立方体的颜色即可，新空格位置只要v改成'E'即可
    if (dx[dir]) {
        v.cubes[idx1].v = v.cubes[idx2].x;
        v.cubes[idx1].x = v.cubes[idx2].v;
    } else {
        char str[] = {'B', 'W', 'R'};// 根据两个x和z确定y的颜色
        char y2;
        for (int i = 0; i < 3; i++) {
            if (v.cubes[idx2].v != str[i] && v.cubes[idx2].x != str[i]) y2 = str[i];
        }
        v.cubes[idx1].v = y2;
        v.cubes[idx1].x = v.cubes[idx2].x;
    }
    v.cubes[idx2].v = 'E';
    return true;
}
 
// 计算搜索的盘面和目标盘面的差异数
int diff(const State &cubes) {
    int d = 0;
    for (int i = 0; i < 9; i++) {
        if (cubes.cubes[i].v != ans[i]) ++d;
    }
    return d;
}
 
int bfs() {
    memset(vst, 0, sizeof(vst));
    queue<State> q;
    State begin;
    begin.d = 0, begin.cubes = vector<cube>(9, {'W', 'B'});
    begin.cubes[x * 3 + y].v = 'E';// 起点
    cube loc;
    loc.x = '0' + x, loc.v = '0' + y;// 数组尾记录空格位置
    begin.cubes.push_back(loc);
    q.push(begin);
    int hashB[2];
    Hash(begin,hashB);
    vst[hashB[0]][hashB[1]] = true;
    while (!q.empty()) {
        State u = q.front();q.pop();
        int xx = u.cubes[9].x - '0', yy = u.cubes[9].v - '0';// 空格位置
        for (int i = 0; i < 4; i++) {
            State cp = u;
            if (flip(cp, xx, yy, i)) {// 移动cube
                // 判重
                int hash[2];
                Hash(cp,hash);
                if (vst[hash[0]][hash[1]]) continue;
                vst[hash[0]][hash[1]] = true;
                int dif = diff(cp);// 与目标有几个方块的差异
                cp.d = u.d + 1;
                if (dif == 0) return cp.d;
                    // 剪枝：n个差异最少需要n-1次移动，steps+dif-1小于等于30
                else if (dif + cp.d > 31) continue;
                q.push(cp);
            }
        }
    }
    return -1;
}
 
#define TEST
 
int main() {
    freopen("UVA1604_in.txt","r",stdin);
    freopen("UVA1604_out.txt","w",stdout);
    while (scanf("%d%d", &x, &y) == 2 && x) {
        getchar();// 清除换行符
        char buf[3][3];
        // 按题目所给的坐标顺序读入
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%c", &buf[j][i]);
                if (buf[j][i] == 'E') {
                    des_x = j, des_y = i;// 初始空格位置
                }
                getchar();// 清除字母间空格
            }
        }
        // 转成一维保存
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ans[i * 3 + j] = buf[i][j];
            }
        }
        // 先判断是否已经满足目标状态
        if (x == des_x + 1 && y == des_y + 1) {
            bool all_w = true;
            for (int i = 0; i < 9; i++) {
                if (ans[i] != 'W' && ans[i] != 'E') {
                    all_w = false;
                    break;
                }
            }
            if (all_w) {
                printf("0\n");
                continue;
            }
        }
        x -= 1, y -= 1;// 转为(0,0)为起点
        printf("%d\n", bfs());
    }
    return 0;
}
	