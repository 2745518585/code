#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=11;
const ll P=998244353;
int n,m,q,b1[1<<N],b2[1<<N];
ll a1[1<<N],a2[1<<N];
vector<int> d1[1<<N],d2[1<<N];
struct pr
{
    int a,b;
}p[N<<2];
struct str
{
    ll s,w;
    str() {}
    str(ll s,ll w):s(s),w(w) {}
    friend str min(const str &a,const str &b)
    {
        if(a.s!=b.s) return a.s<b.s?a:b;
        else return str(a.s,(a.w+b.w)%P);
    }
    friend str operator+(const str &a,ll b)
    {
        return str(a.s+b,a.w);
    }
}f[1<<N][1<<N];
bool cmp(pr a,pr b)
{
    return a.b>b.b;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&p[i].a,&p[i].b);
    }
    sort(p+1,p+n+1,cmp);
    m=n/2;
    n-=m;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=(1<<n)-1;++j)
        {
            if(j&(1<<(i-1))) a1[j]+=p[i].a,b1[j]=max(b1[j],p[i].b);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=0;j<=(1<<m)-1;++j)
        {
            if(j&(1<<(i-1))) a2[j]+=p[n+i].a,b2[j]=max(b2[j],p[n+i].b);
        }
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        d1[i].push_back(i&-i);
        for(int j=(i^(i&-i));j;j=(j-1)&(i^(i&-i))) d1[i].push_back(j|(i&-i));
        sort(d1[i].begin(),d1[i].end(),[&](int x,int y){return a1[x]<a1[y];});
    }
    for(int i=0;i<=(1<<m)-1;++i)
    {
        d2[i].push_back(0);
        for(int j=((1<<m)-1)^i;j;j=(j-1)&(((1<<m)-1)^i)) d2[i].push_back(j);
        sort(d2[i].begin(),d2[i].end(),[&](int x,int y){return a2[x]>a2[y];});
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=0;j<=(1<<m)-1;++j) f[i][j]=str(1e18,0);
    }
    f[0][0]=str(0,1);
    for(int i=0;i<=(1<<m)-1;++i)
    {
        for(int j=i;j;j=(j-1)&i)
        {
            if((j&(i&-i))&&a2[j]<=q) f[0][i]=min(f[0][i],f[0][i^j]+b2[j]);
        }
    }
    for(int i=1;i<=(1<<n)-1;++i)
    {
        for(int j=0;j<=(1<<m)-1;++j)
        {
            auto x=d2[j].begin();
            while(x!=d2[j].end()&&a1[i&-i]+a2[*x]>q) ++x;
            str w=str(1e18,0);
            for(auto k:d1[i])
            {
                while(x!=d2[j].end()&&a1[k]+a2[*x]>q)
                {
                    f[i][j^(*x)]=min(f[i][j^(*x)],w);
                    ++x;
                }
                w=min(w,f[i^k][j]+b1[k]);
            }
            while(x!=d2[j].end())
            {
                f[i][j^(*x)]=min(f[i][j^(*x)],w);
                ++x;
            }
        }
    }
    printf("%lld %lld\n",f[(1<<n)-1][(1<<m)-1].s,(f[(1<<n)-1][(1<<m)-1].w%P+P)%P);
    return 0;
}