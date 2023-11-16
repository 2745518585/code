#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1001;
int m,n,b,a[N],f[N][20][2];
int dfs(int x,int k,bool u)
{
    if(x==n+1) return k==m;
    int &f0=f[x][k][u];
    if(f0!=-1) return f0;
    f0=0;
    if((a[x]>=1||u==false)&&k<m) f0+=dfs(x+1,k+1,a[x]==1&&u);
    f0+=dfs(x+1,k,a[x]==0&&u);
    return f0;
}
int main()
{
    int x,y;
    scanf("%d%d%d%d",&x,&y,&m,&b);
    --x;
    n=0;
    while(x!=0)
    {
        a[++n]=x%b;
        x/=b;
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
        a[++n]=y%b;
        y/=b;
    }
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    memset(f,-1,sizeof(f));
    int s2=dfs(1,0,true);
    printf("%d",s2-s1);
    return 0;
}