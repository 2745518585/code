#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int m;
struct line
{
    double a,b;
};
struct tree
{
    int l,r;
    line k;
}T[N<<2];
double num(line k,int x)
{
    return k.a*x+k.b;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k.a=0;
    T[x].k.b=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,line k)
{
    double z1=num(k,T[x].l)-num(T[x].k,T[x].l),z2=num(k,T[x].r)-num(T[x].k,T[x].r);
    if(z1>=0&&z2>=0)
    {
        T[x].k=k;
        return;
    }
    if(z1<=0&&z2<=0) return;
    if(fabs(max(z1,z2))>fabs(min(z1,z2))) swap(T[x].k,k);
    int z=T[x].l+T[x].r>>1;
    if(fabs(z1)<fabs(z2)) add(x<<1,k);
    else add(x<<1|1,k);
}
double sum(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        return num(T[x].k,T[x].l);
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return max(num(T[x].k,q),sum(x<<1,q));
    else return max(num(T[x].k,q),sum(x<<1|1,q));
}
int main()
{
    scanf("%d",&m);
    build(1,1,50000);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='Q')
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",int(sum(1,x)/100));
        }
        else if(z[0]=='P')
        {
            line k;
            scanf("%lf%lf",&k.b,&k.a);
            k.b-=k.a;
            add(1,k);
        }
    }
    return 0;
}