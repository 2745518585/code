#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],g[N];
bool h[N];
bool check()
{
    scanf("%d",&n);
    for(int i=0;i<=n+1;++i) h[i]=false;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(a[i]<=n+1) h[a[i]]=true;
    }
    int q=0;
    while(h[q]) ++q;
    for(int i=0;i<=n+1;++i) g[i]=0;
    int l=1e9,r=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==q+1)
        {
            l=min(l,i);
            r=max(r,i);
        }
    }
    if(r==0)
    {
        for(int i=1;i<=n;++i)
        {
            if(a[i]<=q-1) ++g[a[i]];
        }
    }
    else
    {
        for(int i=1;i<=l-1;++i)
        {
            if(a[i]<=q-1) ++g[a[i]];
        }
        for(int i=r+1;i<=n;++i)
        {
            if(a[i]<=q-1) ++g[a[i]];
        }
    }
    bool u=true;
    for(int i=0;i<=q-1;++i)
    {
        if(g[i]==0) u=false;
    }
    return u&&q<n;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        if(check()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}