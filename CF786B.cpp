#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=200001,M=10000001;
int n,m,q,s1,p=1,t[N<<2];
ll f[N<<2];
bool h[N<<2];
struct tree
{
    int l,r,q1,q2;
}T[N<<2];
struct road
{
    int m,q;
    ll w;
}a[M];
void road(int x,int y,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].q1=T[x].q2=l;
        return;
    }
    T[x].q1=++q;
    T[x].q2=++q;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    road(T[x].q1,T[x<<1].q1,0);
    road(T[x].q1,T[x<<1|1].q1,0);
    road(T[x<<1].q2,T[x].q2,0);
    road(T[x<<1|1].q2,T[x].q2,0);
}
void add1(int x,int l,int r,int k,ll w)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        road(k,T[x].q1,w);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add1(x<<1,l,r,k,w);
    if(r>z) add1(x<<1|1,l,r,k,w);
}
void add2(int x,int l,int r,int k,ll w)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        road(T[x].q2,k,w);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add2(x<<1,l,r,k,w);
    if(r>z) add2(x<<1|1,l,r,k,w);
}
int main()
{
    scanf("%d%d%d",&n,&m,&s1);
    q=n;
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            ll w;
            scanf("%d%d%lld",&x,&y,&w);
            road(x,y,w);
        }
        else if(z==2)
        {
            int x,l,r;
            ll w;
            scanf("%d%d%d%lld",&x,&l,&r,&w);
            add1(1,l,r,x,w);
        }
        else if(z==3)
        {
            int x,l,r;
            ll w;
            scanf("%d%d%d%lld",&x,&l,&r,&w);
            add2(1,l,r,x,w);
        }
    }
    queue<int> Q;
    for(int i=1;i<=q;++i) f[i]=1e18;
    f[s1]=0;
    h[s1]=true;
    Q.push(s1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",f[i]==1e18?-1:f[i]);
    }
    return 0;
}