#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,k,q,p=1,t[N],b[N],d[N],f[N],g[N];
struct road
{
    int m,q;
}a[N];
struct str
{
    int a[31];
    str()
    {
        for(int i=0;i<=30;++i) a[i]=0;
    }
    bool add(int x)
    {
        for(int i=30;i>=0;--i)
        {
            if((x&(1<<i))==0) continue;
            if(a[i]==0)
            {
                a[i]=x;
                return true;
            }
            x^=a[i];
        }
        return false;
    }
};
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    for(int i=t[x];i;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        f[i/2]=g[a[i].m];
        g[x]^=g[a[i].m];
    }
}
ll solve(int x,str t)
{
    if(x==q+1) return 1;
    ll s=solve(x+1,t);
    if(t.add(b[x])) s=(s+solve(x+1,t)*d[x]%P)%P;
    return s;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=k;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        f[n+i-1]=(1<<(i-1));
        g[x]^=f[n+i-1];
        g[y]^=f[n+i-1];
    }
    dfs(1,0);
    sort(f+1,f+n+k);
    for(int i=1;i<=n+k-1;++i)
    {
        int j=i;
        while(j+1<=n+k-1&&f[j+1]==f[i]) ++j;
        b[++q]=f[i];
        d[q]=j-i+1;
        i=j;
    }
    printf("%lld",solve(1,str()));
    return 0;
}