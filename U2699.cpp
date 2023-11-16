#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100001,M=26;
int n,m,b[1<<M];
ll f[1<<M],h[1<<M];
struct str
{
    int x;
    ll s;
}a[N][M];
bool cmp(str a,str b)
{
    return a.s<b.s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            scanf("%lld",&a[i][j].s);
            a[i][j].x=j;
        }
        sort(a[i]+1,a[i]+m+1,cmp);
        a[i][0].s=0;
        ll w=0;
        for(int j=1;j<=m;++j)
        {
            f[w]+=a[i][j].s-a[i][j-1].s;
            w|=(1<<(a[i][j].x-1));
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=0;j<=(1<<m)-1;++j)
        {
            if(j&(1<<(i-1))) f[j]+=f[j^(1<<(i-1))];
        }
    }
    for(int i=1;i<=m;++i)
    {
        ll x;
        scanf("%lld",&x);
        b[1<<(i-1)]=x;
    }
    for(int i=1;i<=(1<<m)-1;++i)
    {
        h[i]+=h[i^(i&-i)]+b[i&-i];
    }
    ll s=1e18;
    for(int i=1;i<=(1<<m)-1;++i)
    {
        s=min(s,f[((1<<m)-1)^i]+h[i]);
    }
    printf("%lld",s);
    return 0;
}