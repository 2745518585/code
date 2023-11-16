#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline
void read(T& x)
{
    T f=1,b=0;char ch=gc();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=gc();}
    while(ch>='0'&&ch<='9') b*=10,b+=ch-'0',ch=gc();
    x=f*b;return;
}
template<typename T> inline
void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int st[129]={0},k=0;
    while(x) st[++k]=x%10,x/=10;
    for(int i=k;i;i--) putchar(st[i]+'0');
}
const int N=2000001;
int n,m,r,p=1,tot,t[N],b[N];
ll T1[N],T2[N],T3[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
void add(ll T[],int x,ll k)
{
    if(x<1) return;
    while(x<=n)
    {
        T[x]+=k;
        x+=(x&-x);
    }
}
ll sum(ll T[],int x)
{
    if(x<1) return 0;
    ll s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].t=k;
    T[x].b=++tot;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
    T[x].bm=tot;
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
ll num(int x)
{
    return sum(T1,T[x].b)+sum(T2,T[x].b)*T[x].d-sum(T3,T[x].b);
}
int main()
{
    read(n),read(m),read(r);
    for(int i=1;i<=n;++i) read(b[i]);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        read(x),read(y);
        road(x,y);
        road(y,x);
    }
    dfs1(r);
    dfs2(r,r);
    for(int i=1;i<=n;++i)
    {
        add(T1,T[i].b,b[i]);
        add(T1,T[i].bm+1,-b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        read(z);
        if(z==1)
        {
            int x;
            ll k;
            read(x),read(k);
            add(T1,T[x].b,k);
            add(T1,T[x].bm+1,-k);
        }
        else if(z==2)
        {
            int x;
            ll k;
            read(x),read(k);
            add(T2,T[x].b,k);
            add(T2,T[x].bm+1,-k);
            add(T3,T[x].b,k*(T[x].d-1));
            add(T3,T[x].bm+1,-k*(T[x].d-1));
        }
        else if(z==3)
        {
            int x,y;
            read(x),read(y);
            int z=LCA(x,y);
            printf("%lld\n",num(x)+num(y)-num(z)-num(T[z].f));
        }
    }
    return 0;
}