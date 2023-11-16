#include<bits/stdc++.h>
using namespace std;
const int N=5000001;
typedef long long ll;
int n,m,q,tot,b[N];
ll d,a[N],f[N],g[N],T[N],T2[N];
void add(int t,int x,ll k)
{
    if(t<0) return;
    while(x<=q)
    {
        T[x+t*q]=max(T[x+t*q],k);
        x+=(x&-x);
    }
}
void add1(int t,int x,ll k)
{
    if(t<0) return;
    g[x+t*q]=k;
}
void add2(int x,ll k)
{
    while(x<=n)
    {
        T2[x]=max(T2[x],k);
        x+=(x&-x);
    }
}
ll sum(int t,int x)
{
    if(t<0) return -1e18;
    ll s=-1e18;
    while(x>=1)
    {
        s=max(s,T[x+t*q]);
        x-=(x&-x);
    }
    return s;
}
ll sum1(int t,int x)
{
    if(t<0) return -1e18;
    return g[x+t*q];
}
ll sum2(int x)
{
    ll s=-1e18;
    while(x>=1)
    {
        s=max(s,T2[x]);
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d%d%lld",&n,&m,&d);
    q=n/m+1;
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n*2;++i) f[i]=T[i]=g[i]=T2[i]=-1e18;
    for(int i=n;i>=1;--i)
    {
        if(i==n) f[n]=a[n];
        else f[i]=a[i]+(i/m)*d+max(sum2(i+b[i]),max(sum(i%m-1,(i+b[i])/m),sum1(min((i+b[i])%m,i%m-1),(i+b[i])/m+1))+d);
        add2(i,f[i]-(i/m)*d);
        if(i%m==0)
        {
            ll w=-1e18;
            for(int j=i;j<=i+m-1;++j)
            {
                w=max(w,f[j]-(j/m)*d);
                add(j%m,j/m+1,w);
                add1(j%m,j/m+1,w);
            }
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i) s^=(f[i]+i);
    printf("%lld",s);
    return 0;
}