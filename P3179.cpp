#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n,q,m,f1[N],f2[N],h[N];
int sum(int x)
{
    if(x<=q) return f1[x];
    else return f2[n/x];
}
int solve(int x)
{
    int s=0;
    for(int i=1;i<=n/x;++i)
    {
        int j=(n/x)/((n/x)/i);
        h[s^sum(i*x)]=x;
        if((j-i+1)%2==1) s^=sum(i*x);
        i=j;
    }
    int z=0;
    while(h[z]==x) ++z;
    return z;
}
int main()
{
    scanf("%d%d",&n,&m);
    q=sqrt(n);
    for(int i=n;i>=1;--i)
    {
        int j=n/(n/i+1)+1;
        int z=solve(i);
        for(int l=j;l<=min(i,q);++l) f1[l]=z;
        if(i>q) f2[n/i]=z;
        i=j;
    }
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        int s=0;
        for(int j=1;j<=k;++j)
        {
            int x;
            scanf("%d",&x);
            s^=sum(x);
        }
        if(s) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}