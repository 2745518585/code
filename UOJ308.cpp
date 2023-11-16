#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,k,f[N];
vector<int> a[N];
void dfs(int x)
{
    for(auto i:a[x])
    {
        if(f[i]) continue;
        f[i]=-f[x];
        dfs(i);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;++i) a[i].clear(),f[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        if(m==0)
        {
            printf("%d\n",k%6);
            continue;
        }
        if(k==1)
        {
            printf("0\n");
            continue;
        }
        int s=1;
        for(int i=1;i<=n;++i)
        {
            if(f[i]==0)
            {
                f[i]=1;
                dfs(i);
                s=s*2%6;
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(auto j:a[i])
            {
                if(f[i]==f[j]) s=0;
            }
        }
        printf("%d\n",s*(k*(k-1)/2%6)%6);
    }
    return 0;
}