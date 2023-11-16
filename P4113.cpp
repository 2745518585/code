#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,m,k,a[N],b1[N],b2[N],c[N],T[N];
struct str
{
    int l,r,k;
}d[N];
bool cmp(str a,str b)
{
    return a.r<b.r;
}
void add(int x,int k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&-x);
        T[x]+=k;
    }
}
int sum(int x)
{
    int s=T[x];
    while(x>=1)
    {
        x-=(x&-x);
        s+=T[x];
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
    }
    sort(d+1,d+m+1,cmp);
    for(int i=1;i<=m;++i)
    {
        for(int j=d[i-1].r+1;j<=d[i].r;++j)
        {
            if(b1[a[j]]!=0) add(b1[a[j]],-1);
            if(b2[a[j]]!=0) add(b2[a[j]],1);
            b1[a[j]]=b2[a[j]];
            b2[a[j]]=j;
        }
        c[d[i].k]=sum(d[i].r)-sum(d[i].l-1);
    }
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",c[i]);
    }
    return 0;
}