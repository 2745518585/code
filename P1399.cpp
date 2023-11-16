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
        s=max(s,dfs2(a[i].m,x)+a[i].w);
    }
    return s;
}
ll dfs3(int x,int fa)
{
    ll s=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        ll z=dfs3(a[i].m,x);
        v=max(v,s+z+a[i].w);
        s=max(s,z+a[i].w);
    }
    return s;
}
struct tree
{
    int l,r;
    ll s1,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s1=max(T[x<<1].s1,T[x<<1|1].s1);
    T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s1=f[l]-c[l];
        T[x].s2=f[l]+c[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
ll sum1(int x,int l,int r)
{
    if(l>r) return -1e18;
    if(T[x].l>=l&&T[x].r<=r) return T[x].s1;
    int z=T[x].l+T[x].r>>1;
    ll s=-1e18;
    if(l<=z) s=max(s,sum1(x<<1,l,r));
    if(r>z) s=max(s,sum1(x<<1|1,l,r));
    return s;
}
ll sum2(int x,int l,int r)
{
    if(l>r) return -1e18;
    if(T[x].l>=l&&T[x].r<=r) return T[x].s2;
    int z=T[x].l+T[x].r>>1;
    ll s=-1e18;
    if(l<=z) s=max(s,sum2(x<<1,l,r));
    if(r>z) s=max(s,sum2(x<<1|1,l,r));
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
    ll w=c[q];
    for(int i=1;i<=q;++i)
    {
        f[q+i]=f[i]=dfs2(b[i],0);
        c[q+i]=c[i]+w;
    }
    build(1,1,q*2);
    int x=1;
    ll s=1e18;
    for(int i=1;i<=q;++i)
    {
        while((c[x+1]-c[i])<=w/2) ++x;
        ll z=max(sum2(1,i+1,x)-c[i],sum1(1,x+1,q+i-1)+c[q+i]);
        v=0;
        v=max(v,dfs3(b[i],0)+z);
        s=min(s,max(z*2,v));
    }
    x=1;
    for(int i=1;i<=q;++i)
    {
        while((c[x+1]-c[i])<=(w-(c[i]-c[i-1]))/2) ++x;
        ll z1=sum2(1,i,x)-c[i],z2=sum1(1,x+1,q+i-1)+c[q+i-1];
        if(abs(z1-z2)<=c[i]-c[i-1]) s=min(s,z1+z2+(c[i]-c[i-1]));
        else s=min(s,max(z1,z2)*2);
    }
    printf("%.1lf",(double)s/2);
    return 0;
}