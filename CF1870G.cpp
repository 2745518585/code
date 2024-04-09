#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
struct tree
{
    int l,r,s,t;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].t=min(T[x<<1].t,T[x<<1|1].t);
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    T[x].s=T[x].t=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s+=k;
        T[x].t+=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x].s;
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
void solve(int x,int l,int r,int &k,int &t)
{
    if(k>n) return;
    if(T[x].l>=l&&T[x].r<=r&&T[x].t>=k)
    {
        t+=T[x].s-(T[x].r-T[x].l+1)*k;
        return;
    }
    if(T[x].l==T[x].r)
    {
        k+=k-T[x].s;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(r>z) solve(x<<1|1,l,r,k,t);
    if(l<=z) solve(x<<1,l,r,k,t);
}
bool check(int x,int t)
{
    int k=1;
    t+=sum(1,x,n);
    solve(1,1,x-1,k,t);
    return t>=k;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            if(i==1) printf("%d ",max(a[1],1));
            if(a[i]>n) a[i]=0;
        }
        build(1,1,n);
        int x=1,t=0;
        if(a[1]==0) ++t;
        else add(1,a[1],1);
        for(int i=2;i<=n;++i)
        {
            if(a[i]==0) ++t;
            else add(1,a[i],1);
            while(x+1<=n&&check(x+1,t)) ++x;
            printf("%d ",x);
        }
        printf("\n");
    }
    return 0;
}