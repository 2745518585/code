#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,tot=0,a[N<<6][2],g[N<<6][2],rt[N];
ll b[N];
struct str
{
    int x,t;
    ll s;
    friend bool operator <(str a,str b)
    {
        return a.s<b.s;
    }
};
void add(ll x,int k,int k2)
{
    for(int i=32;i>=0;--i)
    {
        int z=(x&(1ll<<i))!=0;
        if(k2!=0) a[k][z^1]=a[k2][z^1],g[k][z^1]=g[k2][z^1];
        a[k][z]=++tot;
        g[k][z]=g[k2][z]+1;
        k=a[k][z];
        if(k2!=0&&a[k2][z]) k2=a[k2][z];
        else k2=0;
    }
}
ll find(ll x,int k,int t)
{
    if(k==0||t>g[k][0]+g[k][1]) return x;
    ll s=0;
    for(int i=32;i>=0;--i)
    {
        int z=(x&(1ll<<i))==0;
        if(a[k][z]!=0&&t<=g[k][z]) k=a[k][z],s=s*2+z;
        else t-=g[k][z],k=a[k][z^1],s=s*2+(z^1);
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    rt[0]=++tot;
    add(0,rt[0],0);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
        b[i]^=b[i-1];
        rt[i]=++tot;
        add(b[i],rt[i],rt[i-1]);
    }
    priority_queue<str> Q;
    for(int i=1;i<=n;++i)
    {
        Q.push((str){i,1,find(b[i],rt[i-1],1)^b[i]});
    }
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        str k=Q.top();
        Q.pop();
        s+=k.s;
        Q.push((str){k.x,k.t+1,find(b[k.x],rt[k.x-1],k.t+1)^b[k.x]});
    }
    printf("%lld",s);
    return 0;
}