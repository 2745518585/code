#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=100001;
int n,m,a[N];
struct num
{
    int l,r,w;
    num() {}
    num(int l,int r,int w):l(l),r(r),w(w) {}
    friend bool operator<(num a,num b)
    {
        return a.w<b.w;
    }
    friend num operator+(num a,num b)
    {
        return num(min(a.l,b.l),max(a.r,b.r),a.w+b.w);
    }
    friend num operator-(num a)
    {
        return num(a.l,a.r,-a.w);
    }
};
template<num (*check)(num,num)>
struct str
{
    num s,ls,rs,t;
    str() {}
    str(num x) {s=ls=rs=check(x,num(0,0,0)),t=x;}
    str(num s,num ls,num rs,num t):s(s),ls(ls),rs(rs),t(t) {}
    friend str operator+(str a,str b)
    {
        str c;
        c.s=check(check(a.s,b.s),a.rs+b.ls);
        c.ls=check(a.ls,a.t+b.ls);
        c.rs=check(b.rs,b.t+a.rs);
        c.t=a.t+b.t;
        return c;
    }
};
num dmin(num x,num y)
{
    return min(x,y);
}
num dmax(num x,num y)
{
    return max(x,y);
}
struct tree
{
    int l,r,k;
    str<dmax> s1;
    str<dmin> s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s1=T[x<<1].s1+T[x<<1|1].s1;
    T[x].s2=T[x<<1].s2+T[x<<1|1].s2;
}
void maketag(int x)
{
    auto z1=T[x].s1;
    auto z2=T[x].s2;
    T[x].s1=str<dmax>(-z2.s,-z2.ls,-z2.rs,-z2.t);
    T[x].s2=str<dmin>(-z1.s,-z1.ls,-z1.rs,-z1.t);
    T[x].k^=1;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    maketag(x<<1);
    maketag(x<<1|1);
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=0;
    if(l==r)
    {
        T[x].s1=str<dmax>(num(l,l,a[l]));
        T[x].s2=str<dmin>(num(l,l,a[l]));
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s1=str<dmax>(num(q,q,k));
        T[x].s2=str<dmin>(num(q,q,k));
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
void add2(int x,int l,int r)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        maketag(x);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add2(x<<1,l,r);
    if(r>z) add2(x<<1|1,l,r);
    pushup(x);
}
str<dmax> sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s1;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    str<dmax> s;
    if(r<=z) s=sum(x<<1,l,r);
    else if(l>z) s=sum(x<<1|1,l,r);
    else s=sum(x<<1,l,r)+sum(x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==0)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            add(1,x,k);
        }
        else
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            int s=0;
            vector<num> p;
            for(int j=1;j<=k;++j)
            {
                auto z=sum(1,x,y).s;
                if(z.w==0) continue;
                s+=z.w;
                add2(1,z.l,z.r);
                p.push_back(z);
            }
            printf("%d\n",s);
            for(auto j:p) add2(1,j.l,j.r);
        }
    }
    return 0;
}