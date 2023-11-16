#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b1[N],b2[N],b3[N],c1[N],c2[N],c3[N];
ll k1,k2;
char a[N];
int main()
{
    scanf("%s%lld%lld",a+1,&k1,&k2);
    n=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        b1[i]=b1[i-1];
        b2[i]=b2[i-1];
        b3[i]=b3[i-1];
        if(a[i]=='0') ++b1[i];
        if(a[i]=='1') ++b2[i];
        if(a[i]=='?') ++b3[i];
    }
    for(int i=n;i>=1;--i)
    {
        c1[i]=c1[i+1];
        c2[i]=c2[i+1];
        c3[i]=c3[i+1];
        if(a[i]=='0') ++c1[i];
        if(a[i]=='1') ++c2[i];
        if(a[i]=='?') ++c3[i];
    }
    ll w=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='0') w+=(b2[i-1]+b3[i-1])*k2;
        else w+=b1[i-1]*k1;
    }
    ll s=w;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='?')
        {
            w-=(b1[i-1]+b3[i-1])*k1+c1[i+1]*k2;
            w+=b2[i-1]*k2+(c2[i+1]+c3[i+1])*k1;
        }
        s=min(s,w);
    }
    w=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='0'||a[i]=='?') w+=b2[i-1]*k2;
        else w+=(b1[i-1]+b3[i-1])*k1;
    }
    s=min(s,w);
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='?')
        {
            w-=(b2[i-1]+b3[i-1])*k2+c2[i+1]*k1;
            w+=b1[i-1]*k1+(c1[i+1]+c3[i+1])*k2;
        }
        s=min(s,w);
    }
    printf("%lld",s);
    return 0;
}