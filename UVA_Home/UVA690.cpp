//#include<bits/stdc++.h>
#include <cstdio>
#include<iostream>
using namespace std;
const int inf=0x3f3f3f3f;
int n,uni[5],skip[25],ans,cnt;

char read(){
    char ch=getchar();
    while(ch==' '||ch=='\n')ch=getchar();
    return ch;
}

bool check(int *s,int stp){//s为上一次的状态,stp表示位移量
    for(int i=0;i<5;i++)
        if((s[i]>>stp)&uni[i])return false;
    return true;
}

void dfs(int *s,int id,int bfst){
    if(id==10){ans=min(ans,bfst+n-1);return;}
    if((10-id)*skip[0]+bfst+n-1>ans)return;
    for(int i=0;i<cnt;i++){
        if(check(s,skip[i])){
            int tmp[5];
            for(int j=0;j<5;j++)
                tmp[j]=(s[j]>>skip[i])|uni[j];//当前状态与上一次状态结合
            dfs(tmp,id+1,bfst+skip[i]);
        }
    }
}

int main(void){
    freopen("UVA690_in.txt","r",stdin);
    freopen("UVA690_out.txt","w",stdout);
    while(~scanf("%d",&n)&&n){ 
        memset(uni,0,sizeof(uni));
        for(int i=0;i<5;i++)
            for(int j=0;j<n;j++){
                char ch=read();
                if(ch=='X')uni[i]|=1<<j;
            }
        cnt=0;
        for(int i=0;i<=n;i++)
            if(check(uni,i))skip[cnt++]=i;
        ans=inf;
        dfs(uni,1,1);
        printf("%d\n",ans);
    } 
    return 0;
}

