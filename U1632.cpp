#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
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
int main()
{
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(r);
    dfs2(r,r);
    for(int i=1;i<=n;++i)
    {
        add(T1,T[i].b,b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            ll k;
            scanf("%d%d%lld",&x,&y,&k);
            int z=LCA(x,y);
            add(T2,T[x].b,k);
            add(T3,T[x].b,k*T[x].d);
            add(T2,T[y].b,k);
            add(T3,T[y].b,k*T[y].d);
            add(T2,T[z].b,-k);
            add(T3,T[z].b,-k*T[z].d);
            add(T2,T[T[z].f].b,-k);
            add(T3,T[T[z].f].b,-k*T[T[z].f].d);
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            printf("%lld\n",b[x]+sum(T2,T[x].bm)-sum(T2,T[x].b-1));
        }
        else if(z==3)
        {
            int x;
            scanf("%d",&x);
            printf("%lld\n",(sum(T1,T[x].bm)-sum(T1,T[x].b-1))+(sum(T3,T[x].bm)-sum(T3,T[x].b-1))-((ll)(T[x].d-1)*(sum(T2,T[x].bm)-sum(T2,T[x].b-1))));
        }
    }
    return 0;
}