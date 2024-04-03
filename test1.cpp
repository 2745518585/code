#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+50,inf=1e18;

int f[N],mp[N],sum[N],n,a[N],c[N],m,st[N],ans,mx,fir[N],p[N],vis[N],qu[N],top;

main()
{
    cin>>n;vis[0]=1;
    for(int i=1;i<=n;i++)cin>>a[i],mp[max(0ll,a[i])]=1,fir[i]=fir[i-1]+(a[i]==-1);
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++)if(!mp[i])st[++m]=i,sum[m]=sum[m-1]+c[i];
    qu[top=1]=0;
    for(int i=1;i<=n;i++)
    {
        mx=max(mx,st[fir[i]]);int x;f[i]=-inf;
        if(a[i]!=-1&&a[i]>mx)mx=a[i],vis[i]=1,x=lower_bound(st+1,st+1+m,a[i])-st-1;p[i]=x;
        if(a[i]==-1)x=m;
        for(int k=top;k>=max(1ll,top-2000);k--)
        {
            int j=qu[k];
            int d=fir[i]-fir[j],to=max(p[j]+1,x-d+1);
            f[i]=max(f[i],f[j]+sum[x]-sum[to-1]);
            if(x-d+1!=to)break;
        }
        if(vis[i])f[i]+=c[a[i]];
        ans=max(ans,f[i]);
        cout<<ans<<' ';
        if(vis[i]&&f[i]>0)qu[++top]=i;
        // return 0;
    }
}
