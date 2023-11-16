#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,m;
ll T[N],T2[N],a[N];
void add(ll T[],int x,ll k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&(-x));
        T[x]+=k;
    }
}
ll sum(ll T[],int x)
{
    ll s=T[x];
    while(x!=0)
    {
        x-=(x&(-x));
        s+=T[x];
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        add(T,i,a[i]-a[i-1]);
        add(T2,i,(a[i]-a[i-1])*(n-i+1));
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            ll k;
            scanf("%d%d%lld",&x,&y,&k);
            add(T,x,k);
            add(T2,x,k*(n-x+1));
            add(T,y+1,-k);
            add(T2,y+1,-k*(n-y));
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",sum(T2,y)-sum(T2,x-1)+sum(T,x-1)*(n-x+1)-(n-y)*(sum(T,y)));
        }
    }
    return 0;
}