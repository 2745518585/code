#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=500001,B=500;
int n,a[N],b[N],f[N/B][B],f1[N/B],f2[N/B],h1[N/B],h2[N/B];
ll e[N];
bool d[N];
vector<int> c[N];
struct str
{
    int w;
    ll s;
    str() {}
    str(int w,ll s):w(w),s(s) {}
    friend bool operator<(const str &a,const str &b)
    {
        return a.w<b.w;
    }
};
vector<str> g1[N/B],g2[N/B];
namespace sgt
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
void rebuild(int x)
{
    f1[x]=f2[x]=-1e9;
    g1[x].clear(),g2[x].clear();
    for(int i=0;i<=B-1;++i)
    {
        if(!d[x*B+i]) continue;
        f[x][i]=min(f[x][i]+h1[x],h2[x]);
        if(f[x][i]>f1[x]) f2[x]=f1[x],f1[x]=f[x][i];
        else if(f[x][i]!=f1[x]&&f[x][i]>f2[x]) f2[x]=f[x][i];
    }
    for(int i=0;i<=B-1;++i)
    {
        if(!d[x*B+i]) continue;
        if(f[x][i]==f1[x]) g2[x].push_back(str(-sgt::sum(x*B+i),0));
        else g1[x].push_back(str(f[x][i]-sgt::sum(x*B+i),0));
    }
    h1[x]=0;
    h2[x]=1e9;
    sort(g1[x].begin(),g1[x].end());
    sort(g2[x].begin(),g2[x].end());
    ll s=0;
    for(auto &i:g1[x]) s+=i.w,i.s=s;
    s=0;
    for(auto &i:g2[x]) s+=i.w,i.s=s;
}
void add1(int x)
{
    ++h1[x],++h2[x],++f1[x],++f2[x];
}
void add2(int x,int k)
{
    h2[x]=min(h2[x],k);
    if(k<=f2[x]) rebuild(x);
    else f1[x]=min(f1[x],k);
}
ll sum(int x,int k)
{
    ll s=0;
    auto p=upper_bound(g1[x].begin(),g1[x].end(),str(k,0ll));
    if(p!=g1[x].begin()) s+=prev(p)->s+(ll)(p-g1[x].begin())*(-k);
    p=upper_bound(g2[x].begin(),g2[x].end(),str(k-(f1[x]-h1[x]),0ll));
    if(p!=g2[x].begin()) s+=prev(p)->s+(ll)(p-g2[x].begin())*(f1[x]-h1[x]-k);
    return s;
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
            b[a[i]]=i;
        }
        int q=0;
        for(int i=1;i<=n;++i)
        {
            c[i].clear();
            int k;
            scanf("%d",&k);
            for(int j=1;j<=k;++j)
            {
                int x;
                scanf("%d",&x);
                c[i].push_back(x);
                e[++q]=0;
            }
        }
        auto solve=[&]()
        {
            int q=0;
            for(int i=1;i<=n;++i) sgt::T[i]=d[i]=0;
            for(int i=0;i<=n/B;++i) rebuild(i);
            for(int i=1;i<=n;++i)
            {
                sgt::add(b[i],1);
                d[b[i]]=true;
                int p=sgt::sum(b[i]),t=b[i]/B;
                for(int j=0;j<=b[i]%B-1;++j) if(d[t*B+j]) f[t][j]=min(min(f[t][j]+h1[t],h2[t]),p);
                for(int j=b[i]%B+1;j<=B-1;++j) if(d[t*B+j]) f[t][j]=min(f[t][j]+h1[t],h2[t])+1;
                f[t][b[i]%B]=1e9;
                h1[t]=0,h2[t]=1e9;
                rebuild(t);
                for(int j=0;j<=t-1;++j) add2(j,p);
                for(int j=t+1;j<=n/B;++j) add1(j);
                for(auto j:c[i])
                {
                    ll s=(ll)i*j;
                    for(int k=0;k<=n/B;++k)
                    {
                        s+=sum(k,j);
                    }
                    e[++q]+=s;
                }
            }
        };
        solve();
        for(int i=1;i<=n;++i) swap(a[i],a[n-i+1]);
        for(int i=1;i<=n;++i) b[i]=n-b[i]+1;
        solve();
        q=0;
        for(int i=1;i<=n;++i)
        {
            for(auto j:c[i])
            {
                printf("%lld\n",e[++q]-(i+j-1));
            }
        }
    }
    return 0;
}