#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int m;
struct line
{
    double a,b;
    line(){}
    line(double a,double b):a(a),b(b){}
    double s(int x)
    {
        return a*x+b;
    }
};
struct tree
{
    int l,r;
    line s;
}T[N<<2];
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=line(0,0);
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,line k)
{
    double z1=k.s(T[x].l)-T[x].s.s(T[x].l),z2=k.s(T[x].r)-T[x].s.s(T[x].r);
    if(z1>=0&&z2>=0)
    {
        T[x].s=k;
        return;
    }
    if(z1<=0&&z2<=0) return;
    if(z1+z2>0) swap(T[x].s,k);
    if(fabs(z1)<fabs(z2)) add(x<<1,k);
    else add(x<<1|1,k);
}
double sum(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        return T[x].s.s(q);
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return max(sum(x<<1,q),T[x].s.s(q));
    else return max(sum(x<<1|1,q),T[x].s.s(q));
}
int main()
{
    scanf("%d",&m);
    build(1,1,50000);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='P')
        {
            double x,y;
            scanf("%lf%lf",&x,&y);
            add(1,line(y,x-y));
        }
        else if(z[0]=='Q')
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",(int)(sum(1,x)/100));
        }
    }
    return 0;
}