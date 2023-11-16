#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
int n,q1,q2,tot,rt[N],c[N],c2[N],b1[N],b2[N],d1[N],d2[N],d3[N],d4[N];
bool h[N];
struct point
{
    int x,y;
}a[N];
struct tree
{
    int l,r,s;
}T[N<<4];
bool cmp(point a,point b)
{
    return a.x<b.x;
}
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void build(int &x,int l,int r)
{
    x=++tot;
    if(l==r) return;
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
}
void add(int &x,int ls,int rs,int q)
{
    T[++tot]=T[x];
    ++T[tot].s;
    x=tot;
    if(ls==rs) return;
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q);
    else add(T[x].r,z+1,rs,q);
}
int sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
bool check2(int x1,int x2,int y1,int y2)
{
    int x;
    x=sum(rt[x1],1,q2,1,y1);
    if(x!=c2[1]) return false;
    x=sum(rt[x1],1,q2,y1+1,y2-1);
    if(x!=c2[2]) return false;
    x=sum(rt[x1],1,q2,y2,q2);
    if(x!=c2[3]) return false;
    x=sum(rt[x2-1],1,q2,1,y1)-sum(rt[x1],1,q2,1,y1);
    if(x!=c2[4]) return false;
    x=sum(rt[x2-1],1,q2,y1+1,y2-1)-sum(rt[x1],1,q2,y1+1,y2-1);
    if(x!=c2[5]) return false;
    x=sum(rt[x2-1],1,q2,y2,q2)-sum(rt[x1],1,q2,y2,q2);
    if(x!=c2[6]) return false;
    x=sum(rt[q1],1,q2,1,y1)-sum(rt[x2-1],1,q2,1,y1);
    if(x!=c2[7]) return false;
    x=sum(rt[q1],1,q2,y1+1,y2-1)-sum(rt[x2-1],1,q2,y1+1,y2-1);
    if(x!=c2[8]) return false;
    x=sum(rt[q1],1,q2,y2,q2)-sum(rt[x2-1],1,q2,y2,q2);
    if(x!=c2[9]) return false;
    return true;
}
void check()
{
    int x1,x2,y1,y2;
    x1=lower_bound(d1+1,d1+q1+1,c2[1]+c2[2]+c2[3])-d1;
    if(c2[1]+c2[2]+c2[3]!=d1[x1]) return;
    x2=q1-(lower_bound(d2+1,d2+q1+1,c2[7]+c2[8]+c2[9])-d2)+1;
    if(c2[7]+c2[8]+c2[9]!=d2[q1-x2+1]) return;
    y1=lower_bound(d3+1,d3+q2+1,c2[1]+c2[4]+c2[7])-d3;
    if(c2[1]+c2[4]+c2[7]!=d3[y1]) return;
    y2=q2-(lower_bound(d4+1,d4+q2+1,c2[3]+c2[6]+c2[9])-d4)+1;
    if(c2[3]+c2[6]+c2[9]!=d4[q2-y2+1]) return;
    if(check2(x1,x2,y1,y2))
    {
        printf("%.2lf %.2lf\n%.2lf %.2lf",b1[x1]+0.5,b1[x2]-0.5,b2[y1]+0.5,b2[y2]-0.5);
        exit(0);
    }
}
void dfs(int x)
{
    if(x==10)
    {
        check();
        return;
    }
    for(int i=1;i<=9;++i)
    {
        if(h[i]) continue;
        c2[x]=c[i];
        h[i]=true;
        dfs(x+1);
        h[i]=false;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        b1[i]=a[i].x;
        b2[i]=a[i].y;
    }
    for(int i=1;i<=9;++i) scanf("%d",&c[i]);
    sort(b1+1,b1+n+1);
    q1=unique(b1,b1+n+1)-b1-1;
    sort(b2+1,b2+n+1);
    q2=unique(b2,b2+n+1)-b2-1;
    for(int i=1;i<=n;++i)
    {
        a[i].x=lower_bound(b1+1,b1+q1+1,a[i].x)-b1;
        a[i].y=lower_bound(b2+1,b2+q2+1,a[i].y)-b2;
    }
    sort(a+1,a+n+1,cmp);
    build(rt[0],1,q2);
    for(int i=1;i<=n;++i)
    {
        if(a[i-1].x!=a[i].x) rt[a[i].x]=rt[a[i-1].x];
        add(rt[a[i].x],1,q2,a[i].y);
    }
    for(int i=1;i<=n;++i) ++d1[a[i].x],++d2[a[i].x];
    for(int i=1;i<=n;++i) ++d3[a[i].y],++d4[a[i].y];
    for(int i=1;i<=q1;++i) d1[i]+=d1[i-1];
    for(int i=q1;i>=1;--i) d2[i]+=d2[i+1];
    for(int i=1;i<=q1/2;++i) swap(d2[i],d2[q1-i+1]);
    for(int i=1;i<=q2;++i) d3[i]+=d3[i-1];
    for(int i=q2;i>=1;--i) d4[i]+=d4[i+1];
    for(int i=1;i<=q2/2;++i) swap(d4[i],d4[q2-i+1]);
    dfs(1);
    printf("-1");
    return 0;
}