#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=200001;
int n,m,a[N],b[N];
ull k1,k2,k3,T1[N],T2[N],T3[N],T4[N];
void add(ull T[],int x,ull k)
{
    while(x<=1e5)
    {
        T[x]+=k;
        x+=(x&-x);
    }
}
ull sum(ull T[],int x)
{
    ull s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%lld%lld%lld%d%d",&k1,&k2,&k3,&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        add(T1,a[i],1);
        add(T2,a[i],a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
        add(T3,b[i],1);
        add(T4,b[i],b[i]);
    }
    ull s=1e18;
    for(int i=1;i<=1e5;++i)
    {
        ull x=sum(T4,1e5)-sum(T4,i)-(sum(T3,1e5)-sum(T3,i))*i;
        if(k2<=k1) x=x*k2;
        else
        {
            ull z=sum(T3,i-1)*i-sum(T4,i-1);
            if(x<=z) x=x*k1;
            else x=z*k1+(x-z)*k2;
        }
        s=min(s,x+(sum(T1,i-1)*i-sum(T2,i-1))*k3);
    }
    printf("%lld",s);
    return 0;
}