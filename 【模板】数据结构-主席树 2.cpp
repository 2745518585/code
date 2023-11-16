#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,q,tot,rt[N];
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
    return 0;
}