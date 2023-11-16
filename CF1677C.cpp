#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N],f[N],fa[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=1;i<=n;++i) fa[i]=i,f[i]=0;
        for(int i=1;i<=n;++i)
        {
            fa[find(a[i])]=find(b[i]);
        }
        for(int i=1;i<=n;++i) ++f[find(i)];
        ll w=0;
        for(int i=1;i<=n;++i)
        {
            if(fa[i]==i) w+=f[i]/2;
        }
        printf("%lld\n",w*(n*2-w+1)-w*(w+1));
    }
    return 0;
}