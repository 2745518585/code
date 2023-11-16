#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=10000001,M=10000001;
int n,m,p=0,b[M],rt[N];
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void build(int &x,int l,int r)
{
    x=++p;
    if(l==r) return;
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
}
void modify(int &x,int l,int r,int q,int k)
{
    T[++p]=T[x];
    T[p].s+=k;
    x=p;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) modify(T[x].l,l,z,q,k);
    else modify(T[x].r,z+1,r,q,k);
}
int sum(int x,int l,int r,int q)
{
    if(l>=q) return T[x].s;
    int z=l+r>>1;
    if(q<=z) return T[T[x].r].s+sum(T[x].l,l,z,q);
    else return sum(T[x].r,z+1,r,q);
}
int main()
{
    scanf("%d",&n);
    build(rt[0],1,n);
    for(int i=1;i<=n;++i)
    {
        int x=read();
        rt[i]=rt[i-1];
        modify(rt[i],1,n,i,1);
        if(b[x]!=0) modify(rt[i],1,n,b[x],-1);
        b[x]=i;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int l=read(),r=read();
        printf("%d\n",sum(rt[r],1,n,l));
    }
    return 0;
}