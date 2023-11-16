#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],f[N],g[N],h[N],T[N];
void add(int x,int k)
{
    while(x<=n) T[x]=max(T[x],k),x+=x&-x;
}
int sum(int x)
{
    int s=0;
    while(x>=1) s=max(s,T[x]),x-=x&-x;
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i) T[i]=0;
        for(int i=1;i<=n;++i)
        {
            f[i]=sum(a[i]-1)+1;
            add(a[i],f[i]);
        }
        for(int i=1;i<=n;++i) T[i]=0;
        for(int i=n;i>=1;--i)
        {
            g[i]=sum(n-a[i])+1;
            add(n-a[i]+1,g[i]);
        }
        int s=0;
        for(int i=1;i<=n;++i) s=max(s,f[i]);
        if(s%2==0)
        {
            printf("YES\n");
            continue;
        }
        for(int i=1;i<=n;++i) h[i]=0;
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            if(f[i]+g[i]-1==s) ++h[f[i]];
            else if(f[i]+g[i]-1>=s/2+1)
            {
                u=true;
                break;
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(h[i]>=2) u=true;
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}