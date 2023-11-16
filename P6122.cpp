#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N],f[N],g[N];
int up(int x)
{
    if(g[x]>0) return -1;
    return 1;
}
int down(int x)
{
    if(g[x]<0) return -1;
    return 1;
}
void pushup(int x)
{
    f[x]=min(a[x]?0:(int)1e9,min(f[x<<1]+down(x<<1),f[x<<1|1]+down(x<<1|1)));
}
void dfs(int x)
{
    if(x>n) return;
    dfs(x<<1);
    dfs(x<<1|1);
    pushup(x);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n*4;++i) f[i]=1e9;
    dfs(1);
    int s=0;
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        int z=x,p=x,q=f[x],w=0;
        while(z!=1)
        {
            if((z^1)<=n)
            {
                if(f[z^1]+w+up(z)+down(z^1)<q)
                {
                    p=z^1;
                    q=f[z^1]+w+up(z)+down(z^1);
                }
            }
            w+=up(z);
            z>>=1;
            if(a[z])
            {
                if(w<q) p=z,q=w;
            }
        }
        s+=q;
        z=x;
        while(z!=p&&z!=p/2)
        {
            --g[z];
            z>>=1;
        }
        while(true)
        {
            if(a[z]&&f[z<<1]+down(z<<1)>=0&&f[z<<1|1]+down(z<<1|1)>=0) break;
            if(f[z<<1]+down(z<<1)<=f[z<<1|1]+down(z<<1|1)) z=z<<1;
            else z=z<<1|1;
            ++g[z];
        }
        --a[z];
        while(z!=0)
        {
            pushup(z);
            z>>=1;
        }
        z=x;
        while(z!=0)
        {
            pushup(z);
            z>>=1;
        }
        printf("%d ",s);
    }
    return 0;
}