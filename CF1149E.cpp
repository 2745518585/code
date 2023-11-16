#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,t[N],t2[N],f[N],l[N],h[N];
ll b[N],g[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road2(int x,int y)
{
    a[++p].m=y;
    a[p].q=t2[x];
    t2[x]=p;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road2(y,x);
        ++l[x];
    }
    queue<int> Q;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q) h[f[a[i].m]]=k;
        for(int i=0;i<=n;++i)
        {
            if(h[i]!=k)
            {
                f[k]=i;
                break;
            }
        }
        for(int i=t2[k];i!=0;i=a[i].q)
        {
            --l[a[i].m];
            if(l[a[i].m]==0) Q.push(a[i].m);
        }
    }
    for(int i=1;i<=n;++i) g[f[i]]^=b[i];
    int z=-1;
    for(int i=0;i<=n;++i)
    {
        if(g[i]!=0) z=i;
    }
    if(z==-1)
    {
        printf("LOSE");
        return 0;
    }
    printf("WIN\n");
    int x=0;
    for(int i=1;i<=n;++i)
    {
        if(f[i]==z&&(b[i]^g[z])<b[i])
        {
            x=i;
            break;
        }
    }
    b[x]^=g[z];
    g[z]=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        b[a[i].m]^=g[f[a[i].m]];
        g[f[a[i].m]]=0;
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",b[i]);
    }
    return 0;
}