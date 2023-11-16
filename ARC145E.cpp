#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,f[N],g[N];
ll a[N],b[N],c[N],h[N];
vector<int> ans;
void add(int x)
{
    for(int i=1;i<=x;++i) b[i]^=b[i-1];
    for(int i=1;i<=x;++i) c[i]^=c[i-1];
    ans.push_back(x);
}
ll add(ll x,int t)
{
    ll s=0;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=0;j<=60;++j) h[j]=0;
        q=0;
        for(int j=1;j<=i;++j)
        {
            ll x=b[j];
            c[j]=0;
            for(int k=60;k>=0;--k)
            {
                if(!(x&(1ll<<k))) continue;
                c[j]^=(1ll<<k);
                if(h[k]==0)
                {
                    g[++q]=k;
                    f[k]=j;
                    h[k]=x;
                    break;
                }
                x^=h[k];
            }
        }
        ll x=a[i],w=0;
        for(int j=60;j>=0;--j)
        {
            if(x&(1ll<<j))
            {
                w^=(1ll<<j);
                x^=h[j];
            }
        }
        for(int j=q;j>=1;--j)
        {
            ll p=0;
            for(int k=1;k<=i;++k) p^=c[k];
            if(((w^p)&(1ll<<g[j]))) add(f[g[j]]+1);
        }
        add(i);
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]!=b[i])
        {
            printf("No");
            return 0;
        }
    }
    printf("Yes\n%d\n",ans.size());
    while(!ans.empty()) printf("%d ",ans.back()),ans.pop_back();
    return 0;
}