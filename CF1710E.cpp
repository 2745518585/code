#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,n,sx,sy,a1[N],a2[N],b1[N],b2[N];
bool check(int x)
{
    b1[0]=n;
    for(int i=1;i<=m;++i)
    {
        b1[i]=b1[i-1];
        while(b1[i]>0&&a1[i]+a2[b1[i]]>x) --b1[i];
    }
    b2[0]=m;
    for(int i=1;i<=n;++i)
    {
        b2[i]=b2[i-1];
        while(b2[i]>0&&a1[b2[i]]+a2[i]>x) --b2[i];
    }
    ll w=0,s1=0,s2=0;
    for(int i=1;i<=m;++i) w+=(n-b1[i]);
    s1=w;
    {
        int t=0;
        for(int i=1;i<=m;++i)
        {
            w+=min(b1[i],t)-(n-max(b1[i],t));
            int z=0;
            while(t<n&&(z=(min(b2[t+1],i)-(m-max(b2[t+1],i))))>0) w+=z,++t;
            s1=max(s1,w);
        }
    }
    w=-(sy>b1[sx]);
    for(int i=1;i<=m;++i) w+=(n-b1[i]);
    s2=w;
    {
        int t=0;
        for(int i=1;i<=m;++i)
        {
            w+=(min(b1[i],t)-(sx==i&&sy<=min(b1[i],t)))-((n-max(b1[i],t))-(sx==i&&sy>max(b1[i],t)));
            int z=0;
            while(t<n&&(z=(min(b2[t+1],i)-(sy==t+1&&sx<=min(b2[t+1],i)))-((m-max(b2[t+1],i))-(sy==t+1&&sx>max(b2[t+1],i))))>0) w+=z,++t;
            s2=max(s2,w);
        }
    }
    return s1!=s2+1;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a1[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a2[i]);
    }
    int z1=a1[1],z2=a2[1];
    sort(a1+1,a1+m+1);
    sort(a2+1,a2+n+1);
    for(int i=1;i<=m;++i)
    {
        if(a1[i]==z1)
        {
            sx=i;
            break;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(a2[i]==z2)
        {
            sy=i;
            break;
        }
    }
    int l=0,r=a1[sx]+a2[sy];
    while(l<r)
    {
        int z=l+r>>1;
        if(check(z)) r=z;
        else l=z+1;
    }
    printf("%d",l);
    return 0;
}