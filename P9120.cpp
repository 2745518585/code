#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,k,q,mx,mn,a[N][4],e[N];
struct node
{
    int x1,x2,y1,y2;
    node() {}
    node(int x1,int x2,int y1,int y2):x1(x1),x2(x2),y1(y1),y2(y2) {}
}b[N][4];
struct line
{
    int x1,x2,h,u;
    line() {}
    line(int x1,int x2,int h,int u):x1(x1),x2(x2),h(h),u(u) {}
}c[N<<5];
bool cmp(line a,line b)
{
    return a.h<b.h;
}
struct tree
{
    int l,r,s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
void add_node(int u,node p1=node(1,3e4,1,3e4),node p2=node(1,3e4,1,3e4),node p3=node(1,3e4,1,3e4),node p4=node(1,3e4,1,3e4))
{
    int x1=max(max(p1.x1,p2.x1),max(p3.x1,p4.x1));
    int x2=min(min(p1.x2,p2.x2),min(p3.x2,p4.x2));
    int y1=max(max(p1.y1,p2.y1),max(p3.y1,p4.y1));
    int y2=min(min(p1.y2,p2.y2),min(p3.y2,p4.y2));
    if(x1<=x2&&y1<=y2)
    {
        c[++q]=line(x1,x2,y1,u);
        c[++q]=line(x1,x2,y2+1,-u);
    }
}
bool check()
{
    q=0;
    for(int i=1;i<=n;++i)
    {
        add_node(1,b[i][0]);
        add_node(1,b[i][1]);
        add_node(1,b[i][2]);
        add_node(1,b[i][3]);
        add_node(-1,b[i][0],b[i][1]);
        add_node(-1,b[i][0],b[i][2]);
        add_node(-1,b[i][0],b[i][3]);
        add_node(-1,b[i][1],b[i][2]);
        add_node(-1,b[i][1],b[i][3]);
        add_node(-1,b[i][2],b[i][3]);
        add_node(1,b[i][0],b[i][1],b[i][2]);
        add_node(1,b[i][0],b[i][1],b[i][3]);
        add_node(1,b[i][0],b[i][2],b[i][3]);
        add_node(1,b[i][1],b[i][2],b[i][3]);
        add_node(-1,b[i][0],b[i][1],b[i][2],b[i][3]);
    }
    sort(c+1,c+q+1,cmp);
    build(1,1,m);
    int x=1;
    for(int i=1;i<=m;++i)
    {
        while(x<=q&&c[x].h==i)
        {
            add(1,c[x].x1,c[x].x2,c[x].u);
            ++x;
        }
        if(T[1].s==n) return true;
    }
    return false;
}
int find(int x)
{
    return lower_bound(e+1,e+m+1,x)-e;
}
bool solve(int x)
{
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<=3;++k) b[j][k]=node(1,1,0,0);
        }
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<=3;++k)
            {
                if(mx-a[j][k]>x||a[j][(k+i)%4]-mn>x) continue;
                int z1=0,z2=0;
                if(i==1) z1=a[j][(k+2)%4],z2=a[j][(k+3)%4];
                if(i==2) z1=a[j][(k+1)%4],z2=a[j][(k+3)%4];
                if(i==3) z1=a[j][(k+1)%4],z2=a[j][(k+2)%4];
                b[j][k]=node(find(max(1,z1-x)),find(z1),find(max(1,z2-x)),find(z2));
            }
        }
        if(check()) return true;
    }
    return false;
}
namespace Solve2
{
    bool solve(int x)
    {
        for(int i=1;i<=n;++i)
        {
            bool u=false;
            for(int j=0;j<=1;++j)
            {
                if(mx-a[i][j]>x||a[i][(j+1)%2]-mn>x) continue;
                u=true;
            }
            if(!u) return false;
        }
        return true;
    }
}
namespace Solve3
{
    int c[N],q;
    struct str
    {
        int x,h,u;
        str() {}
        str(int x,int h,int u):x(x),h(h),u(u) {}
    }b[N];
    bool cmp(str a,str b)
    {
        return a.h<b.h;
    }
    bool check()
    {
        sort(b+1,b+q+1,cmp);
        for(int i=1;i<=n;++i) c[i]=0;
        int x=1,s=0;
        for(int i=1;i<=m;++i)
        {
            while(x<=q&&b[x].h==i)
            {
                if(c[b[x].x]==0) ++s;
                c[b[x].x]+=b[x].u;
                if(c[b[x].x]==0) --s;
                ++x;
            }
            if(s==n) return true;
        }
        return false;
    }
    bool solve(int x)
    {
        for(int i=1;i<=2;++i)
        {
            q=0;
            for(int j=1;j<=n;++j)
            {
                for(int k=0;k<=2;++k)
                {
                    if(mx-a[j][k]>x||a[j][(k+i)%3]-mn>x) continue;
                    int z=0;
                    if(i==1) z=a[j][(k+2)%3];
                    if(i==2) z=a[j][(k+1)%3];
                    b[++q]=str(j,find(max(1,z-x)),1);
                    b[++q]=str(j,find(z+1),-1);
                }
            }
            if(check()) return true;
        }
        return false;
    }
}
void abc()
{
    scanf("%d",&n);
    mx=1,mn=3e4;
    m=0;
    for(int i=0;i<=k-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[j][i]);
            e[++m]=a[j][i];
            mx=max(mx,a[j][i]);
            mn=min(mn,a[j][i]);
        }
    }
    if(k==1)
    {
        printf("%d\n",mx-mn);
        return;
    }
    sort(e+1,e+m+1);
    m=unique(e+1,e+m+1)-e-1;
    auto chk=[&](int x)
    {
        if(k==2) return Solve2::solve(x);
        if(k==3) return Solve3::solve(x);
        if(k==4) return solve(x);
        return false;
    };
    int l=0,r=3e4;
    while(l<r)
    {
        int z=l+r>>1;
        if(chk(z)) r=z;
        else l=z+1;
    }
    printf("%d\n",l);
}
int main()
{
    int T;
    scanf("%d%d",&T,&k);
    while(T--) abc();
    return 0;
}