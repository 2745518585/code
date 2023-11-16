#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,b[N],T[N];
ll c[N];
struct str
{
    int k,x,y,z,t;
}a[N],p[N];
void add(int x,int k)
{
    while(x<=n) T[x]+=k,x+=(x&-x);
}
int sum(int x)
{
    int s=0;
    while(x>=1) s+=T[x],x-=(x&-x);
    return s;
}
void solve(int l,int r,ll ml,ll mr)
{
    if(l>r||ml>mr) return;
    if(ml==mr)
    {
        for(int i=l;i<=r;++i) if(a[i].k==1) c[a[i].t]=ml;
        return;
    }
    ll z=ml+mr>>1;
    int p1=l-1,p2=r+1;
    for(int i=l;i<=r;++i)
    {
        if(a[i].k==1)
        {
            int k=sum(a[i].y)-sum(a[i].x-1);
            if(a[i].z<=k) p[++p1]=a[i];
            else a[i].z-=k,p[--p2]=a[i];
        }
        else if(a[i].k==0)
        {
            if(a[i].y<=z)
            {
                add(a[i].x,a[i].z);
                p[++p1]=a[i];
            }
            else p[--p2]=a[i];
        }
    }
    for(int i=l;i<=r;++i) if(a[i].k==0&&a[i].y<=z) add(a[i].x,-a[i].z);
    for(int i=l;i<=p1;++i) a[i]=p[i];
    for(int i=p2;i<=r;++i) a[p2+r-i]=p[i];
    solve(l,p1,ml,z);
    solve(p2,r,z+1,mr);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        a[++q]=(str){0,i,b[i],1,0};
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==0)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            a[++q]=(str){0,x,b[x],-1,0};
            a[++q]=(str){0,x,k,1,0};
            b[x]=k;
        }
        else if(z==1)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            a[++q]=(str){1,x,y,k,i};
        }
    }
    for(int i=1;i<=m;++i) c[i]=-1;
    solve(1,q,-3e9,3e9);
    for(int i=1;i<=m;++i)
    {
        if(c[i]!=-1) printf("%lld\n",c[i]);
    }
    return 0;
}