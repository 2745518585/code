#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,s=1e9,a[N],b[N],c[N],d[N],e[N];
bool h[N];
void check()
{
    d[1]=0;
    for(int i=2;i<=n;++i)
    {
        int t=(1<<(c[i]-1));
        d[i]=0;
        for(int j=i-1;j>=1;--j)
        {
            t|=(1<<(c[j]-1));
            d[i]=max(d[i],d[j]+b[t]);
        }
    }
    s=min(s,d[n]);
}
void dfs(int x)
{
    if(x==n+1)
    {
        check();
        return;
    }
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        c[x]=i;
        h[i]=true;
        dfs(x+1);
        h[i]=false;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    int z=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        z=max(z,a[i]);
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i&(1<<(j-1))) e[i]+=a[j];
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x,w;
        scanf("%d%d",&x,&w);
        if(z>w)
        {
            printf("-1");
            return 0;
        }
        for(int j=0;j<=(1<<n)-1;++j)
        {
            if(w<e[j]) b[j]=max(b[j],x);
        }
    }
    dfs(1);
    printf("%d",s);
    return 0;
}