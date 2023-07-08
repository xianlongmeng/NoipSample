#include<iostream>

using namespace std;
// 1 white 2 red 3 blue
int f[4][4];
struct cub{
    int up,front;
    cub(int _u=1,int _f=2):up(_u),front(_f){}
    void UD(){swap(up,front);}
    void LR(){up^=front;}
}c[4][4];
inline char read(){
    char ch=getchar();
    while(ch==' '||ch=='\n')ch=getchar();
    return ch;
}
inline int h(){
    int res=0;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            if(c[j][i].up!=f[j][i])res++;
    return res;
}
const int dir[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
bool ida(int row,int col,int bf,int now,int maxd){
    int t=h(); 
    if(t>maxd-now+1)return false;
    if(!t)return true;
    for(int i=0;i<4;i++){
        if(i+bf==3)continue;
        int row2=row+dir[i][0];
        int col2=col+dir[i][1];
        if(row2<1||row2>3||col2<1||col2>3)continue;
        cub tmp=c[col2][row2];
        c[col][row]=c[col2][row2];
        c[col2][row2].up=0;
        if(i==1||i==2) c[col][row].UD();
        else c[col][row].LR();
        if(ida(row2,col2,i,now+1,maxd))return true;
        c[col2][row2]=tmp;
        c[col][row].up=0;
    }
    return false;
}
int main(void){
    freopen("UVA1604_in.txt","r",stdin);
    freopen("UVA1604_out.txt","w",stdout);
    int x,y;
    while(~scanf("%d %d",&x,&y)&&x){
        for(int i=1;i<=3;i++)
            for(int j=1;j<=3;j++){
                c[j][i]=cub();
                char ch=read();
                switch (ch){
                    case 'E':f[j][i]=0;break;
                    case 'W':f[j][i]=1;break;
                    case 'R':f[j][i]=2;break;
                    case 'B':f[j][i]=3;break;
                }
            }
        int maxd=0; c[x][y].up=0;
        while(maxd<=30&&!ida(y,x,-1,0,maxd))maxd++;
        printf("%d\n",maxd>30?-1:maxd);      
    }
    return 0;
}
   