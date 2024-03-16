#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;
const int N=1000001,M=31;
int n,m,k,sa[N],rk[N],he[N],*f[M<<1],g[M];
char a[N],b[N];
namespace SA
{
    char a[N];
    int h[N],x1[N],x2[N];
    void init()
    {
        int n=strlen(a+1),m=128;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
        }
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
        for(int r=1;r<=n;r<<=1)
        {
            int p=0;
            for(int i=n-r+1;i<=n;++i) x2[++p]=i;
            for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
            for(int i=1;i<=m;++i) h[i]=0;
            for(int i=1;i<=n;++i) ++h[x1[i]];
            for(int i=1;i<=m;++i) h[i]+=h[i-1];
            for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
            swap(x1,x2);
            p=0;
            x1[sa[1]]=++p;
            for(int i=2;i<=n;++i)
            {
                if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
                else x1[sa[i]]=++p;
            }
            if(p==n) break;
            m=p;
        }
        for(int i=1;i<=n;++i) rk[sa[i]]=i;
        int p=0;
        for(int i=1;i<=n;++i)
        {
            if(rk[i]==1) continue;
            if(p>=1) --p;
            int j=sa[rk[i]-1];
            while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
            he[rk[i]]=p;
        }
    }
}
namespace ST
{
    int b[N][M],lg[N];
    void init()
    {
        for(int i=0;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n+m+1);++j) lg[j]=i;
        }
        for(int i=1;i<=n+m+1;++i) b[i][0]=he[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n+m+1;++j)
            {
                if(j+(1<<i)-1<=n+m+1) b[j][i]=min(b[j][i-1],b[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        if(x>y) swap(x,y);
        ++x;
        return min(b[x][lg[y-x+1]],b[y-(1<<lg[y-x+1])+1][lg[y-x+1]]);
    }
}
int sum(int x,int y)
{
    if(x>n||y>m) return 0;
    return ST::sum(rk[x],rk[n+1+y]);
}
void solve(int x)
{
    for(int i=0;i<=k;++i)
    {
        for(int j=-k;j<=k;++j) f[i][j]=-1;
    }
    f[0][0]=sum(1,x);
    for(int i=0;i<=k-1;++i)
    {
        for(int j=-k;j<=k;++j)
        {
            if(f[i][j]==-1) continue;
            if(f[i][j]<n&&x+f[i][j]+j-1<m)
            {
                f[i+1][j]=max(f[i+1][j],f[i][j]+sum(f[i][j]+2,x+f[i][j]+j+1)+1);
            }
            if(f[i][j]<n)
            {
                f[i+1][j-1]=max(f[i+1][j-1],f[i][j]+sum(f[i][j]+2,x+f[i][j]+j)+1);
            }
            else f[i+1][j-1]=max(f[i+1][j-1],f[i][j]);
            if(x+f[i][j]+j-1<m)
            {
                f[i+1][j+1]=max(f[i+1][j+1],f[i][j]+sum(f[i][j]+1,x+f[i][j]+j+1));
            }
            else f[i+1][j+1]=max(f[i+1][j+1],f[i][j]);
        }
    }
    for(int i=-k;i<=k;++i)
    {
        for(int j=0;j<=k;++j)
        {
            if(n+i>=1&&x+n+i-1<=m&&f[j][i]==n)
            {
                ++g[j];
                break;
            }
        }
    }
}
int main()
{
    scanf("%d%s%s",&k,a+1,b+1);
    n=strlen(a+1),m=strlen(b+1);
    for(int i=1;i<=n;++i) SA::a[i]=a[i];
    SA::a[n+1]='*';
    for(int i=1;i<=m;++i) SA::a[n+1+i]=b[i];
    SA::init();
    ST::init();
    for(int i=0;i<=k;++i) f[i]=new int[k*2+10],f[i]+=k+5;
    for(int i=1;i<=m;++i) solve(i);
    for(int i=0;i<=k;++i)
    {
        printf("%d\n",g[i]);
    }
    return 0;
}