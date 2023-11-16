#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=11;
int n,a[N],f[N][10][2];
int dfs(int x,int k,bool u)
{
    if(x==n+1) return 1;
    int &f0=f[x][k][u];
    if(f0!=-1) return f0;
    f0=0;
    int t=u?a[x]:9;
    for(int i=k;i<=t;++i)
    {
        f0+=dfs(x+1,i,u&&i==t);
    }
    return f0;
}
int main()
{
    int x,y;
    while(scanf("%d%d",&x,&y)!=EOF)
    {
        --x;
        n=0;
        while(x!=0)
        {
            a[++n]=x%10;
            x/=10;
        }
        if(n==0)
        {
            n=1;
            a[1]=0;
        }
        for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
        memset(f,-1,sizeof(f));
        int s1=dfs(1,0,true);
        n=0;
        while(y!=0)
        {
            a[++n]=y%10;
            y/=10;
        }
        for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
        memset(f,-1,sizeof(f));
        int s2=dfs(1,0,true);
        printf("%d\n",s2-s1);
    }
    return 0;
}