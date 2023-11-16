#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=100001;
int n,m,q,b[N],l[N];
bool g[N],h[N];
vector<int> a[N];
bool dfs(int x)
{
    b[++q]=x;
    if(g[x]) return true;
    h[x]=true;
    for(auto i:a[x])
    {
        if(h[i]) continue;
        if(dfs(i)) return true;
    }
    --q;
    return false;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i].clear(),l[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
            ++l[x],++l[y];
        }
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            if(l[i]<4) continue;
            for(int j=1;j<=n;++j) g[j]=h[j]=false;
            h[i]=true;
            for(auto j:a[i]) g[j]=true;
            for(auto j:a[i])
            {
                g[j]=false;
                q=0;
                if(dfs(j))
                {
                    int z1=0,z2=0;
                    for(int k:a[i])
                    {
                        if(k==j||k==b[q]) continue;
                        if(z1==0) z1=k;
                        else if(z2==0) z2=k;
                    }
                    printf("YES\n");
                    printf("%d\n",q+3);
                    b[0]=b[q+1]=i;
                    for(int i=1;i<=q+1;++i)
                    {
                        printf("%d %d\n",b[i-1],b[i]);
                    }
                    printf("%d %d\n",i,z1);
                    printf("%d %d\n",i,z2);
                    u=true;
                    break;
                }
                g[j]=true;
            }
            if(u) break;
        }
        if(!u) printf("NO\n");
    }
    return 0;
}