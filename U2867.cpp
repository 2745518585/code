#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,tot,b[N],rt[N];
struct point
{
    int x,y,t;
}a[N];
struct str
{
    int x;
    ll s;
    str(){}
    str(int x,ll s):x(x),s(s){}
    friend str operator +(str a,ll b)
    {
        return str(a.x,a.s+b);
    }
    friend str operator +(ll b,str a)
    {
        return str(a.x,a.s+b);
    }
    friend str min(str a,str b)
    {
        return a.s<b.s?a:b;
    }
};
struct str2
{
    int x;
    str s;
    str2(){}
    str2(int x,str s):x(x),s(s){}
    friend bool operator <(str2 a,str2 b)
    {
        return a.s.s>b.s.s;
    }
};
struct tree
{
    int l,r;
    str s1,s2;
}T[N<<4];
bool cmp(point a,point b)
{
    return a.x<b.x;
}
bool cmp2(int x,int y)
{
    return a[x].y<a[y].y;
}
void pushup(int x)
{
    T[x].s1=min(T[T[x].l].s1,T[T[x].r].s1);
    T[x].s2=min(T[T[x].l].s2,T[T[x].r].s2);
}
void add(int &x,int ls,int rs,int q,ll k1,ll k2)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s1=str(ls,k1);
        T[x].s2=str(ls,k2);
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k1,k2);
    else add(T[x].r,z+1,rs,q,k1,k2);
    pushup(x);
}
str sum1(int x,int ls,int rs,int l,int r)
{
    if(x==0||l>r) return str(0,1e18);
    if(ls>=l&rs<=r)
    {
        return T[x].s1;
    }
    int z=ls+rs>>1;
    str s=str(0,1e18);
    if(l<=z) s=min(s,sum1(T[x].l,ls,z,l,r));
    if(r>z) s=min(s,sum1(T[x].r,z+1,rs,l,r));
    return s;
}
str sum2(int x,int ls,int rs,int l,int r)
{
    if(x==0||l>r) return str(0,1e18);
    if(ls>=l&rs<=r)
    {
        return T[x].s2;
    }
    int z=ls+rs>>1;
    str s=str(0,1e18);
    if(l<=z) s=min(s,sum2(T[x].l,ls,z,l,r));
    if(r>z) s=min(s,sum2(T[x].r,z+1,rs,l,r));
    return s;
}
int main()
{
    T[0].s1=T[0].s2=str(0,1e18);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) b[i]=i;
    sort(b+1,b+n+1,cmp2);
    for(int i=1;i<=n;++i) a[b[i]].t=i;
    priority_queue<str2> Q;
    for(int i=1;i<=n;++i)
    {
        rt[i]=rt[i-1];
        if(i!=1) add(rt[i],1,n,a[i-1].t,-a[i-1].x-a[i-1].y,-a[i-1].x+a[i-1].y);
        // printf("%d %d\n",i,min(a[i].x+a[i].y+sum1(rt[i],1,n,1,a[i].t),a[i].x-a[i].y+sum2(rt[i],1,n,a[i].t+1,n)).s);
        Q.push(str2(i,min(a[i].x+a[i].y+sum1(rt[i],1,n,1,a[i].t),a[i].x-a[i].y+sum2(rt[i],1,n,a[i].t+1,n))));
    }
    for(int i=1;i<=m;++i)
    {
        str2 k=Q.top();
        Q.pop();
        printf("%lld\n",k.s.s);
        T[++tot]=T[rt[k.x]];
        rt[k.x]=tot;
        add(rt[k.x],1,n,k.s.x,1e18,1e18);
        // printf("%d %d %d\n",k.x,min(a[k.x].x+a[k.x].y+sum1(rt[k.x],1,n,1,a[k.x].t),a[k.x].x-a[k.x].y+sum2(rt[k.x],1,n,a[k.x].t+1,n)).x,min(a[k.x].x+a[k.x].y+sum1(rt[k.x],1,n,1,a[k.x].t),a[k.x].x-a[k.x].y+sum2(rt[k.x],1,n,a[k.x].t+1,n)).s);
        Q.push(str2(k.x,min(a[k.x].x+a[k.x].y+sum1(rt[k.x],1,n,1,a[k.x].t),a[k.x].x-a[k.x].y+sum2(rt[k.x],1,n,a[k.x].t+1,n))));
    }
    return 0;
}