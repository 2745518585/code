#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,q1,q2,a[N];
ll b[N],c[N],m;
void dfs1(int x,ll w)
{
    if(w>m) return;
    if(x==n/2+1)
    {
        b[++q1]=w;
        return;
    }
    for(ll i=a[x];w+i<=m;i*=a[x])
    {
        dfs1(x+1,w+i);
    }
}
void dfs2(int x,ll w)
{
    if(w>m) return;
    if(x==n+1)
    {
        c[++q2]=w;
        return;
    }
    for(ll i=a[x];w+i<=m;i*=a[x])
    {
        dfs2(x+1,w+i);
    }
}
int main()
{
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    dfs1(1,0);
    dfs2(n/2+1,0);
    sort(b+1,b+q1+1);
    sort(c+1,c+q2+1);
    c[++q2]=1e18;
    ll s=0;
    for(int i=1;i<=q1;++i)
    {
        ll z=upper_bound(c+1,c+q2+1,m-b[i])-c-1;
        s+=z;
    }
    printf("%lld",s);
    return 0;
}