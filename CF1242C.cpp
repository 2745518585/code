#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,a[N],b[N],c[N],d[N],e[N],p1[N],p2[N];
ll o[N];
bool f[N],g[N],h[N],p[N];
vector<int> a2[N];
map<ll,int> Map;
void dfs(int x)
{
    if(h[x]) return;
    h[x]=true;
    for(auto i:a2[x]) dfs(i);
}
void solve(int x)
{
    if(e[x]!=0)
    {
        solve(e[x]);
        solve(x^e[x]);
        return;
    }
    int y=a[d[x]];
    p[d[x]]=true;
    while(y!=d[x]) p[y]=true,y=a[y];
}
int main()
{
    scanf("%d",&n);
    ll w=0;
    for(int i=1;i<=n;++i)
    {
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;++j)
        {
            int x;
            scanf("%d",&x);
            b[++m]=x;
            c[m]=i;
            Map[x]=m;
            w+=x;
            o[i]+=x;
        }
    }
    if(w%n!=0)
    {
        printf("No\n");
        return 0;
    }
    w/=n;
    for(int i=1;i<=m;++i)
    {
        if(Map.count(w-o[c[i]]+b[i]))
        {
            a[i]=Map[w-o[c[i]]+b[i]];
            a2[a[i]].push_back(i);
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(h[i]) continue;
        int x=i;
        while(!g[x]&&a[x]!=0) g[x]=true,x=a[x];
        dfs(x);
        if(a[x]==0) continue;
        bool u=true;
        // printf("%d %d\n",x,c[x]);
        int y=a[x],t=(1<<(c[x]-1));
        while(y!=x)
        {
            if(t&(1<<(c[y]-1))) u=false;
            t|=(1<<(c[y]-1));
            y=a[y];
        }
        if(u)
        {
            // printf("%d\n",t);
            f[t]=true;
            d[t]=x;
        }
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(f[i]) continue;
        for(int j=i;j;j=(j-1)&i)
        {
            if(f[i^j]&&f[j])
            {
                f[i]=true;
                e[i]=j;
                break;
            }
        }
    }
    if(f[(1<<n)-1]==false)
    {
        printf("No\n");
        return 0;
    }
    printf("Yes\n");
    solve((1<<n)-1);
    for(int i=1;i<=m;++i)
    {
        if(p[i])
        {
            p1[c[a[i]]]=b[a[i]];
            p2[c[a[i]]]=c[i];
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d %d\n",p1[i],p2[i]);
    }
    return 0;
}