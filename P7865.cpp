#include<cstdio>
using namespace std;
int m,n;
struct tree
{
    int l,r,s;
    bool k;
}T[3001][12001];
void pushup(int q,int x)
{
    T[q][x].s=T[q][x<<1].s+T[q][x<<1|1].s;
}
void pushdown(int q,int x)
{
    if(T[q][x].k==false) return;
    tree t=T[q][x],l=T[q][x<<1],r=T[q][x<<1|1];
    l.s=l.r-l.l+1;
    r.s=r.r-r.l+1;
    l.k=r.k=true;
    t.k=false; 
}
void build(int q,int x,int l,int r)
{
    T[q][x].l=l;
    T[q][x].r=r;
    T[q][x].s=0;
    if(l==r)  return;
    int z=l+r>>1;
    build(q,x<<1,l,z);
    build(q,x<<1|1,z+1,r);
}
void add(int q,int x,int l,int r)
{
    if(T[q][x].l>=l&&T[q][x].r<=r)
    {
        T[q][x].s=T[q][x].r-T[q][x].l+1;
        T[q][x].k=true;
        return;
    }
    pushdown(q,x);
    int z=T[q][x].l+T[q][x].r>>1;
    if(l<=z) add(q,x<<1,l,r);
    if(r>z) add(q,x<<1|1,l,r);
    pushup(q,x);
}
bool sum(int q,int x,int l,int r)
{
    if(T[q][x].s==T[q][x].r-T[q][x].l+1) return true;
    if(T[q][x].l>=l&&T[q][x].r<=r) return false;
    pushdown(q,x);
    int z=T[q][x].l+T[q][x].r>>1;
    bool s=true;
    if(l<=z) s=sum(q,x<<1,l,r);
    if(s==false) return false;
    if(r>z) s=sum(q,x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        build(i,1,1,n);
    }
    int w;
    scanf("%d",&w);
    for(int i=1;i<=w;++i)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        for(int j=x1;j<=x2;++j)
        {
            add(j,1,y1,y2);
        }
    }
    scanf("%d",&w);
    for(int i=1;i<=w;++i)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        bool s;
        for(int j=x1;j<=x2;++j)
        {
            s=sum(j,1,y1,y2);
            if(s==false) break;
        }
        if(s==true) printf("Yes\n");
        else printf("No\n");
    }
}
