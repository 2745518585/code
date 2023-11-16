#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,c[N],d[N];
ll a[N],b[N],f[N],T[N];
set<int> Set;
struct str
{
    int x,u,t;
};
vector<str> e[N];
bool cmp(int x,int y)
{
    return c[x]>c[y];
}
void add(int x,ll k)
{
    while(x<=n+1)
    {
        T[x]+=k;
        x+=(x&-x);
    }
}
ll sum(int x)
{
    ll s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    c[n+1]=1e9;
    for(int i=n;i>=1;--i)
    {
        int x=i+1;
        while(c[x]<=c[i]) x=d[x];
        d[i]=x;
    }
    Set.insert(1);
    Set.insert(n+1);
    e[1].push_back((str){n+1,1,0});
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        if(x==1) continue;
        if(Set.count(x))
        {
            int z1=*(--Set.find(x)),z2=*(++Set.find(x));
            e[z1].push_back((str){x,-1,i});
            e[x].push_back((str){z2,-1,i});
            e[z1].push_back((str){z2,1,i});
            Set.erase(x);
        }
        else
        {
            Set.insert(x);
            int z1=*(--Set.find(x)),z2=*(++Set.find(x));
            e[z1].push_back((str){x,1,i});
            e[x].push_back((str){z2,1,i});
            e[z1].push_back((str){z2,-1,i});
        }
    }
    for(int i=n+1;i>=1;--i)
    {
        if(i<=n)
        {
            add(i+1,a[i]);
            ll z=sum(d[i]);
            if(b[i]<z) add(d[i],b[i]-z);
        }
        for(int j=0;j<e[i].size();++j)
        {
            f[e[i][j].t]+=e[i][j].u*sum(e[i][j].x);
        }
    }
    for(int i=1;i<=m;++i) f[i]+=f[i-1];
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",f[i]);
    }
    return 0;
}