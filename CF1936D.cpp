#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001,M=30;
int n,m,v,a[N],b[N];
struct pr
{
    int a=0,b=-1;
    pr() {}
    pr(int a,int b):a(a),b(b) {}
    friend pr operator+(const pr &a,const pr &b)
    {
        return pr(max(a.a,b.a),a.b|b.b);
    }
};
struct str
{
    pr w,l[M+2],r[M+2];
    int s=1e9;
    str() {}
    str(pr x)
    {
        w=l[1]=r[1]=x;
        if(x.b>=v) s=x.a;
        else s=1e9;
    }
    friend str operator+(const str &a,const str &b)
    {
        str c;
        c.w=a.w+b.w;
        c.s=min(a.s,b.s);
        int q=0;
        for(int i=1;q<M&&a.l[i].b!=-1;++i)
        {
            if(a.l[i].b!=c.l[q].b) c.l[++q]=a.l[i];
        }
        for(int i=1;q<M&&b.l[i].b!=-1;++i)
        {
            if((a.w+b.l[i]).b!=c.l[q].b) c.l[++q]=a.w+b.l[i];
        }
        q=0;
        for(int i=1;q<M&&b.r[i].b!=-1;++i)
        {
            if(b.r[i].b!=c.r[q].b) c.r[++q]=b.r[i];
        }
        for(int i=1;q<M&&a.r[i].b!=-1;++i)
        {
            if((b.w+a.r[i]).b!=c.r[q].b) c.r[++q]=b.w+a.r[i];
        }
        int x=1;
        for(int i=M;i>=1;--i)
        {
            if(a.r[i].b==-1) continue;
            while(b.l[x+1].b!=-1&&(a.r[i]+b.l[x]).b<v) ++x;
            if((a.r[i]+b.l[x]).b>=v) c.s=min(c.s,(a.r[i]+b.l[x]).a);
        }
        return c;
    }
};
struct tree
{
    int l,r;
    str s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].s=pr(a[l],b[l]);
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
        T[x].s=pr(a[q],k);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    if(q>z) add(x<<1|1,q,k);
    pushup(x);
}
str sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x].s;
    int z=T[x].l+T[x].r>>1;
    str s;
    if(r<=z) s=sum(x<<1,l,r);
    else if(l>z) s=sum(x<<1|1,l,r);
    else s=sum(x<<1,l,r)+sum(x<<1|1,l,r);
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        build(1,1,n);
        scanf("%d",&m);
        for(int i=1;i<=m;++i)
        {
            int z;
            scanf("%d",&z);
            if(z==1)
            {
                int x,k;
                scanf("%d%d",&x,&k);
                add(1,x,k);
            }
            else if(z==2)
            {
                int x,y;
                scanf("%d%d",&x,&y);
                int s=sum(1,x,y).s;
                printf("%d ",s==1e9?-1:s);
            }
        }
        printf("\n");
    }
    return 0;
}