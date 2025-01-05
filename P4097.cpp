#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n,m;
struct lin
{
    double a=0,b=-1e9;
    int t=0;
    lin() {}
    lin(double a,double b,int t=0):a(a),b(b),t(t) {}
    double operator()(int x)
    {
        return a*x+b;
    }
};
struct tree
{
    int l,r;
    lin s;
}T[N<<2];
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int l,int r,lin k)
{
    if(T[x].l<l||T[x].r>r)
    {
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        return;
    }
    double z1=k(T[x].l)-T[x].s(T[x].l),z2=k(T[x].r)-T[x].s(T[x].r);
    if(z1>0&&z2>0)
    {
        T[x].s=k;
        return;
    }
    if(z1<=0&&z2<=0) return;
    if(fabs(max(z1,z2))>fabs(min(z1,z2))) swap(T[x].s,k);
    if(fabs(z1)<fabs(z2)) add(x<<1,l,r,k);
    else add(x<<1|1,l,r,k);
}
lin sum(int x,int q)
{
    if(T[x].l==T[x].r) return T[x].s;
    int z=T[x].l+T[x].r>>1;
    lin s;
    if(q<=z) s=sum(x<<1,q);
    else s=sum(x<<1|1,q);
    if(T[x].s(q)>s(q)+1e-6||(fabs(T[x].s(q)-s(q))<1e-6&&T[x].s.t<s.t)) s=T[x].s;
    return s;
}
int main()
{
    scanf("%d",&m);
    build(1,1,50000);
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==0)
        {
            int x;
            scanf("%d",&x);
            x=(x+las-1)%39989+1;
            printf("%d\n",las=sum(1,x).t);
        }
        else if(z==1)
        {
            ++n;
            int x1,y1,x2,y2;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            x1=(x1+las-1)%39989+1;
            x2=(x2+las-1)%39989+1;
            y1=(y1+las-1)%1000000000+1;
            y2=(y2+las-1)%1000000000+1;
            lin p;
            p.t=n;
            if(x1!=x2)
            {
                p.a=(double)(y2-y1)/(x2-x1);
                p.b=y1-x1*p.a;
            }
            else
            {
                p.a=0;
                p.b=max(y1,y2);
            }
            add(1,min(x1,x2),max(x1,x2),p);
        }
    }
    return 0;
}