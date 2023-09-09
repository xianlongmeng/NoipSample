#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
char s[3][6];
char change[11] = {'*','0','1','2','3','4','5','6','7','8','9'};//*指代空格
int len[3],maxd;
int check_result()
{
    char check_str[10];
    char ss[10];
    int t0=0,t1=0,t2;
    for(int i=0;i<len[0];i++)
        t0=t0*10+s[0][i]-'0';
    for(int i=0;i<len[1];i++)
        t1=t1*10+s[1][i]-'0';
    t2=t0*t1;
    for(int i=0;i<len[2];i++)
    {
        check_str[len[2]-i-1]=t2%10+'0';
        t2/=10;
    }
    if(t2!=0||check_str[0]=='0')return 0;//t2不存在或者不满足位数
    for(int i=0;i<len[2];i++)
        if(check_str[i]!=s[2][i]&&s[2][i]!='*')return 0;
    return 1;
}
int check(int a,int b)
{
    int flag=0;
    if(a==2){flag=check_result();return flag;}
    int ta,tb;
    char ch=s[a][b];
    if(b==len[a]-1){
        ta=a+1;
        tb=0;
    }else{
        ta=a;
        tb=b+1;
    }
    if(s[a][b]=='*'){//需要填数的空格
        for(int i=1;i<=10;i++)
        {
            if(b==0&&i==1)continue;
            s[a][b]=change[i];
            flag+=check(ta,tb);
            if(flag>1)break;//多解时直接剪枝
        }
    }else{
        flag+=check(ta,tb);
    }
    s[a][b]=ch;
    return flag;
}
int dfs(int a,int b,int d)
{
    int flag;
    if(d==maxd){
        flag=check(0,0);//解的个数
        if(flag==1)return 1;
        else return 0;
    }
    if(a==3)return 0;
    int ta,tb;
    char tmp=s[a][b];
    if(b==len[a]-1){//当前字符串是否枚举完了
        ta=a+1;
        tb=0;
    }else{
        ta=a;
        tb=b+1;
    }
    for(int i=0;i<=10;i++)
    {
        if(b==0&&i==1)continue;//忽略前导0
        if(tmp==change[i]){
            s[a][b]=tmp;
            flag=dfs(ta,tb,d);//相同不做更改
        }else{
            s[a][b]=change[i];
            flag=dfs(ta,tb,d+1);
        }
        if(flag)break;
    }
    if(!flag)s[a][b]=tmp;//没有找到解，恢复原样。
    return flag;
}
int main()
{
    freopen("UVA12107_in.txt","r",stdin);
    freopen("UVA12107_out.txt","w",stdout);
    int kase=0;
    memset(s,0,sizeof(s));
    while(scanf("%s%s%s",s[0],s[1],s[2])==3)
    {
        for(int i=0;i<3;i++)len[i]=strlen(s[i]);
        printf("Case %d: ",++kase);
        for(int i=0;;i++){
            maxd=i;
            if(dfs(0,0,0)){
                printf("%s %s %s\n",s[0],s[1],s[2]);
                break;
            }
        }
        memset(s,0,sizeof(s));
    }
    return 0;
}
