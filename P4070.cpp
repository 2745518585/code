#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,q,a[N],b[N];
int sa[N],rk[N],he[N];
ll d[N];
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(int n,int *a)
    {
        int m=n;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
        }
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
        for(int r=1;r<=n;r<<=1)
        {
            int p=0;
            for(int i=n-r+1;i<=n;++i) x2[++p]=i;
            for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
            for(int i=1;i<=m;++i) h[i]=0;
            for(int i=1;i<=n;++i) ++h[x1[i]];
            for(int i=1;i<=m;++i) h[i]+=h[i-1];
            for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
            swap(x1,x2);
            p=0;
            x1[sa[1]]=++p;
            for(int i=2;i<=n;++i)
            {
                if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
                else x1[sa[i]]=++p;
            }
            if(p==n) break;
            m=p;
        }
        for(int i=1;i<=n;++i) rk[sa[i]]=i;
        int p=0;
        for(int i=1;i<=n;++i)
        {
            if(rk[i]==1) continue;
            if(p>=1) --p;
            int j=sa[rk[i]-1];
            while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
            he[rk[i]]=p;
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    for(int i=1;i<=n;++i) b[i]=a[i];
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
    }
    SA::init(n,a);
    map<int,int> Map;
    ll s=0;
    for(int i=1;i<=n;++i) Map[rk[i]]=he[rk[i]],s+=he[rk[i]];
    d[1]=s;
    for(int i=1;i<=n-1;++i)
    {
        map<int,int>::iterator p=Map.find(rk[i]);
        ++p;
        int z1=Map[rk[i]],z2=p->second;
        s=s-z1-z2+min(z1,z2);
        p->second=min(z1,z2);
        Map.erase(rk[i]);
        d[i+1]=s;
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld\n",(ll)i*(i+1)/2-d[n-i+1]);
    }
    return 0;
}