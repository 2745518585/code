#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=6001;
int n,a[N],b[N][N],d[N],g[N];
bool h[N];
vector<int> c[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++a[x];
    }
    for(int i=1;i<=5000;++i)
    {
        int x=i;
        for(int j=2;j<=5000;++j)
        {
            while(x%j==0) c[i].push_back(j),x/=j;
        }
    }
    for(int i=1;i<=5000;++i)
    {
        for(int j=1;j<=i;++j)
        {
            for(auto k:c[j]) ++b[i][k];
        }
    }
    ll s=0;
    for(int i=1;i<=5000;++i)
    {
        ll w=0;
        for(int j=1;j<=5000;++j) w+=b[i][j];
        s+=w*a[i];
    }
    for(int i=1;i<=5000;++i) d[i]=5000;
    for(int i=1;i<=5000;++i)
    {
        if(a[i]!=0) h[i]=true;
    }
    while(true)
    {
        for(int i=1;i<=5000;++i) g[i]=0;
        for(int i=1;i<=5000;++i)
        {
            if(!h[i]) continue;
            while(d[i]>0&&b[i][d[i]]==0) --d[i];
            g[d[i]]+=a[i];
        }
        int x=0;
        for(int i=1;i<=5000;++i)
        {
            if(g[i]>n/2)
            {
                x=i;
                break;
            }
        }
        if(x==0) break;
        for(int i=1;i<=5000;++i)
        {
            if(!h[i]) continue;
            if(d[i]==x)
            {
                h[i]=true;
                --b[i][d[i]];
            }
            else h[i]=false;
        }
        s+=n-g[x]*2;
    }
    printf("%lld",s);
    return 0;
}