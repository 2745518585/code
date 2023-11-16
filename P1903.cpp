#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
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
const int N=1000001,M=1000001;
int n,n1,n2,m,q,a[N],b[M],c[N],s;
struct str
{
    int l,r,k,t;
}d1[N];
struct str2
{
    int x,a;
}d2[N];
bool cmp(str a,str b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    if((a.r-1)/q!=(b.r-1)/q) return a.r<b.r;
    return a.t<b.t;
}
void add(int x)
{
    if(b[x]++==0) ++s;
}
void del(int x)
{
    if(--b[x]==0) --s;
}
void upd(int k,int t)
{
    if(d1[k].l<=d2[t].x&&d1[k].r>=d2[t].x)
    {
        del(a[d2[t].x]);
        add(d2[t].a);
    }
    swap(a[d2[t].x],d2[t].a);
}
int main()
{
    n=read(),m=read();
    q=pow(n,double(2)/3);
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=m;++i)
    {
        char z;
        cin>>z;
        if(z=='Q')
        {
            d1[++n1].l=read(),d1[n1].r=read();
            d1[n1].t=n2,d1[n1].k=n1;
        }
        else d2[++n2].x=read(),d2[n2].a=read();
    }
    sort(d1+1,d1+n1+1,cmp);
    int l=1,r=0,t=0;
    for(int i=1;i<=n1;++i)
    {
        while(d1[i].l<l) add(a[--l]);
        while(d1[i].r>r) add(a[++r]);
        while(d1[i].l>l) del(a[l++]);
        while(d1[i].r<r) del(a[r--]);
        while(d1[i].t>t) upd(i,++t);
        while(d1[i].t<t) upd(i,t--);
        c[d1[i].k]=s;
    }
    for(int i=1;i<=n1;++i)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}