#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,p=1,t[N],b[N];
ll c[N],f[N],v;
bool g[N],h[N],u=true;
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x,int fa)
{
    if(u) b[++q]=x;
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(h[a[i].m])
        {
            if(u)
            {
                int z=0;
                for(int j=1;j<=q;++j) if(b[j]==a[i].m) z=j;
                for(int j=1;j<=q-z+1;++j) b[j]=b[j+z-1],c[j]=c[j+z-1];
                q-=z-1;
                c[1]=a[i].w;
            }
            u=false;
            break;
        }
        if(u) c[q+1]=a[i].w;
        dfs(a[i].m,x);
    }
    if(u) --q;
}
ll dfs2(int x,int fa)
{
    ll s=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        ll z=dfs2(a[i].m,x);
        v=max(v,s+z+a[i].w);
        s=max(s,z+a[i].w);
    }
    return s;
}
struct tree
{
    int l,r;
    ll s1,s2,s;
}T[N<<2];
void pushup(tree &T,tree T1,tree T2)
{
    T.s=max(max(T1.s,T2.s),T1.s1+T2.s2);
    T.s1=max(T1.s1,T2.s1);
    T.s2=max(T1.s2,T2.s2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=0;
        T[x].s1=f[l]-c[l];
        T[x].s2=f[l]+c[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
tree sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x];
    int z=T[x].l+T[x].r>>1;
    tree s;
    if(l<=z&&!(r>z)) s=sum(x<<1,l,r);
    else if(!(l<=z)&&r>z) s=sum(x<<1|1,l,r);
    else pushup(s,sum(x<<1,l,r),sum(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs(1,0);
    for(int i=1;i<=q;++i) g[b[i]]=true,c[i]+=c[i-1];
    for(int i=1;i<=q;++i)
    {
        f[q+i]=f[i]=dfs2(b[i],0);
        c[q+i]=c[i]+c[q];
    }
    build(1,1,q*2);
    ll s=1e18;
    for(int i=1;i<=q;++i)
    {
        s=min(s,sum(1,i,q+i-1).s);
    }
    printf("%lld",max(s,v));
    return 0;
}