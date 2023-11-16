#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000001;
int n;
ll ls,rs,a[N],b[N],c[N];
struct str
{
    str(){}
    str(ll l,ll r,ll k,ll w):l(l),r(r),k(k),w(w){}
    ll l,r,k,w;
    friend bool operator <(str a,str b)
    {
        return a.r<b.r;
    }
};
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    scanf("%lld%lld",&ls,&rs);
    priority_queue<str> Q;
    queue<str> Q2;
    Q.push(str(ls,rs,0,0));
    for(int i=1;i<=n;++i)
    {
        while(!Q.empty())
        {
            str k=Q.top();
            if(k.r<a[i]) break;
            Q.pop();
            if(k.l<a[i]) Q2.push(str(k.l,min(a[i]-1,k.r),k.k,k.w));
            Q2.push(str(max(0ll,k.l-a[i]),k.r-a[i],k.k+a[i],k.w+b[i]));
        }
        while(!Q2.empty())
        {
            Q.push(Q2.front());
            Q2.pop();
        }
    }
    while(!Q.empty())
    {
        str k=Q.top();
        Q.pop();
        for(ll i=k.l+k.k;i<=k.r+k.k;++i) c[i-ls+1]=k.w;
    }
    for(int i=1;i<=rs-ls+1;++i)
    {
        printf("%lld ",c[i]);
    }
    return 0;
}