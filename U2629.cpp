#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10000001;
const double eps=0.1;
ll n;
double p,q,f[N];
double check(int m)
{
    f[(n+1)%m]=0;
    for(ll i=n;i>=1;--i)
    {
        int t1=i%m,t2=(i+1)%m;
        if(i+m-1<=n) f[t1]=p*(f[t1]+1)+(1-p)*f[t2];
        else f[t1]=f[t2];
        if(n-i+1>=2.5e7) break;
    }
    return f[1%m];
}
int main()
{
    scanf("%lld%lf%lf",&n,&p,&q);
    int l=1,r=min(sqrt(n),5e9/n);
    while(l<r)
    {
        int z=l+r>>1;
        double k=check(z);
        if(abs(k-q)<=eps)
        {
            l=z;
            break;
        }
        if(k>q) l=z+1;
        else r=z-1;
    }
    printf("%d",l);
    return 0;
}