#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,f[N],g[N];
vector<int> a[N],ans;
void dfs0(int x,int fa)
{
    f[x]=f[fa]+1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs0(i,x);
    }
}
void dfs1(int x,int fa)
{
    f[x]=1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs1(i,x);
        f[x]=max(f[x],f[i]+1);
    }
}
void dfs(int x,int fa)
{
    int z=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(f[i]>f[z]) z=i;
    }
    if(z)
    {
        if(f[z]>2) dfs(z,x);
        else if(f[z]==2) ans.push_back(z);
        ans.push_back(x);
    }
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(f[i]==2&&i!=z)
        {
            ans.push_back(i);
            ans.push_back(x);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    if(n==1)
    {
        printf("YES\n1\n1");
        return 0;
    }
    if(m!=n-1)
    {
        printf("NO");
        return 0;
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs0(1,0);
    int x=0;
    for(int i=1;i<=n;++i)
    {
        if(f[i]>f[x]) x=i;
    }
    for(auto i:a[x])
    {
        if(f[i]<f[x])
        {
            x=i;
            break;
        }
    }
    dfs1(x,0);
    for(int i=1;i<=n;++i)
    {
        int u=0;
        for(auto j:a[i])
        {
            for(auto k:a[j])
            {
                if(k!=i&&a[k].size()>1)
                {
                    ++u;
                    break;
                }
            }
        }
        if(u>=3)
        {
            printf("NO");
            return 0;
        }
    }
    dfs(x,0);
    dfs(ans[0],0);
    printf("YES\n");
    printf("%d\n",ans.size());
    for(auto i:ans) printf("%d ",i);
    return 0;
}