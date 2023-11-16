#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n,m;
struct line
{
    double a,b;
}a[N];
struct tree
{
    int l,r,k;
}T[N<<2];
double num(int k,int x)
{
    if(a[k].a==1e9) return a[k].b;
    return a[k].a*x+a[k].b;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int l,int r,int k)
{
    if(T[x].l<l||T[x].r>r)
    {
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        return;
    }
    double z1=num(k,T[x].l)-num(T[x].k,T[x].l),z2=num(k,T[x].r)-num(T[x].k,T[x].r);
    if(z1>=0&&z2>=0)
    {
        T[x].k=k;
        return;
    }
    if(z1<=0&&z2<=0) return;
    if(fabs(max(z1,z2))>fabs(min(z1,z2))) swap(T[x].k,k);
    int z=T[x].l+T[x].r>>1;
    if(fabs(z1)<fabs(z2)) add(x<<1,l,r,k);
    else add(x<<1|1,l,r,k);
}
int sum(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        return T[x].k;
    }
    int z=T[x].l+T[x].r>>1,s;
    if(q<=z) s=sum(x<<1,q);
    else s=sum(x<<1|1,q);
    if(num(s,q)>num(T[x].k,q)||(num(s,q)==num(T[x].k,q)&&s<T[x].k)) return s;
    return T[x].k;
}
int main()
{
    scanf("%d",&m);
    build(1,1,50000);
    a[0].a=0;
    a[0].b=-1e9;
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
            printf("%d\n",las=sum(1,x));
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
            if(x1!=x2)
            {
                a[n].a=(double)(y2-y1)/(x2-x1);
                a[n].b=y1-x1*a[n].a;
            }
            else
            {
                a[n].a=1e9;
                a[n].b=max(y1,y2);
            }
            add(1,min(x1,x2),max(x1,x2),n);
        }
    }
    return 0;
}