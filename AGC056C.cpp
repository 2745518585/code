#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=2000001;
int n,m,fa[N],f[N],b[N];
vector<int> a[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        fa[find(y)]=find(x-1);
    }
    for(int i=0;i<=n-1;++i)
    {
        a[find(i)].push_back(find(i+1));
        a[find(i+1)].push_back(find(i));
    }
    for(int i=0;i<=n;++i) f[i]=-1;
    f[find(0)]=0;
    queue<int> Q;
    Q.push(find(0));
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(auto i:a[k])
        {
            if(f[i]==-1)
            {
                f[i]=f[k]+1;
                Q.push(i);
            }
        }
    }
    int x=0;
    for(int i=1;i<=n;++i)
    {
        if(x+1<=f[find(i)]) ++x,b[i]=0;
        else --x,b[i]=1;
    }
    for(int i=1;i<=n;++i) printf("%d",b[i]);
    return 0;
}