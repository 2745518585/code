#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,b[N],c[N],d[N];
bool f[N],g[N];
vector<int> a[N],ans;
void dfs(int x,int fa)
{
    g[x]=true;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        f[x]|=f[i]^1;
        if(f[i]==0) ans.push_back(i);
    }
}
void dfs2(int x,int k)
{
    if(f[x]) return;
    if(k==0) ans.push_back(x);
    dfs2(b[x],k^1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x].push_back(i);
        b[i]=x;
    }
    for(int i=1;i<=n;++i)
    {
        if(g[i]) continue;
        int x=i;
        while(!g[x]) g[x]=true,x=b[x];
        q=0;
        c[++q]=x;
        x=b[x];
        while(x!=c[1]) c[++q]=x,x=b[x];
        c[0]=c[q];
        c[q+1]=c[1];
        bool u=false;
        for(int j=1;j<=q;++j)
        {
            dfs(c[j],c[j-1]);
            if(f[c[j]]) u=true;
        }
        if(u==false)
        {
            if(q%2==1)
            {
                printf("-1");
                return 0;
            }
            for(int j=1;j<=q;++j)
            {
                if(j%2==1) ans.push_back(c[j]);
            }
            continue;
        }
        for(int j=1;j<=q;++j)
        {
            if(f[c[j]]) dfs2(b[c[j]],0);
        }
    }
    sort(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    for(auto i:ans) printf("%d ",b[i]);
    return 0;
}