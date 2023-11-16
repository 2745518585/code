#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,q,tot,tot,f[N],rt1[N],rt2[N];
char a[N];
struct tree
{
    int l,r,t;
    ll s,k;
}T[N<<5];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void pushdown(int x,int ls,int rs)
{
    if(T[x].k==0) return;
    int z=ls+rs>>1;
    if(T[T[x].l].t!=T[x].t)
    {
        T[++tot]=T[T[x].l];
        T[tot].t=T[x].t;
        T[x].l=tot;
    }
    T[T[x].l].s+=T[x].k*(z-ls+1);
    T[T[x].l].k+=T[x].k;
    if(T[T[x].r].t!=T[x].t)
    {
        T[++tot]=T[T[x].r];
        T[tot].t=T[x].t;
        T[x].r=tot;
    }
    T[T[x].r].s+=T[x].k*(rs-z);
    T[T[x].r].k+=T[x].k;
    T[x].k=0;
}
void add(int &x,int t,int ls,int rs,int l,int r,ll k)
{
    if(l>r) return;
    if(x==0||T[x].t!=t)
    {
        T[++tot]=T[x];
        T[tot].t=t;
        x=tot;
    }
    if(ls>=l&&rs<=r)
    {
        T[x].s+=k*(rs-ls+1);
        T[x].k+=k;
        return;
    }
    pushdown(x,ls,rs);
    int z=ls+rs>>1;
    if(l<=z) add(T[x].l,t,ls,z,l,r,k);
    if(r>z) add(T[x].r,t,z+1,rs,l,r,k);
    pushup(x);
}
ll sum(int &x,int ls,int rs,int l,int r)
{
    if(l>r) return 0;
    if(x==0) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    pushdown(x,ls,rs);
    int z=ls+rs>>1;
    ll s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
int main()
{
    scanf("%d%d%s",&n,&tot,a+1);
    for(int i=n;i>=1;--i)
    {
        a[i*2]=a[i];
        a[i*2-1]='#';
    }
    q=n*2+1;
    a[q]='#';
    a[0]='~';
    a[q+1]='@';
    int x=1;
    for(int i=1;i<=q;++i)
    {
        if(i<x+f[x]) f[i]=min(x+f[x]-i,f[x*2-i]);
        else f[i]=1;
        while(a[i-f[i]]==a[i+f[i]]) ++f[i];
        if(i+f[i]>x+f[x]) x=i;
    }
    for(int i=1;i<=q;++i) f[i]=((f[i]*2-1)/2+1)/2;
    for(int i=1;i<=n;++i)
    {
        rt1[i]=rt1[i-1];
        add(rt1[i],i,1,n,i-f[i*2]+1,i,1);
        add(rt1[i],i,1,n,i-f[i*2+1]+1,i,1);
    }
    for(int i=n;i>=1;--i)
    {
        rt2[i]=rt2[i+1];
        add(rt2[i],i,1,n,i,i+f[i*2]-1,1);
        add(rt2[i],i,1,n,i,i+f[i*2-1]-1,1);
    }
    scanf("%d",&m);
    ll las=0;
    for(int i=1;i<=m;++i)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        if(tot==1) x^=las,y^=las;
        int z1,z2;
        if((y-x+1)%2==0) z1=(x+y)/2,z2=(x+y)/2+1;
        else z1=(x+y)/2-1,z2=(x+y)/2+1;
        ll s=0;
        s+=sum(rt1[z1],1,n,x,z1)+sum(rt2[z2],1,n,z2,y);
        if((y-x+1)%2==0) s-=min((y-x+1)/2,(ll)f[x+y]);
        else s+=min((y-x+1)/2+1,(ll)f[x+y]);
        printf("%lld\n",las=s);
    }
    return 0;
}