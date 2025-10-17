#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,q,b[N],c[N],p[N];
bool f[N];
vector<int> a[N];
void dfs(int x,int d)
{
    ++b[d];
    for(int i:a[x]) dfs(i,d+1);
    if(a[x].empty()) q=min(q,d);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        q=1e9;
        for(int i=1;i<=n;++i) a[i].clear(),b[i]=c[i]=0;
        for(int i=2;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            a[x].push_back(i);
        }
        dfs(1,1);
        for(int i=1;i<=q;++i) ++c[b[i]];
        for(int i=1;i<=n;++i) f[i]=false;
        f[0]=true;
        for(int i=1;i<=n;++i)
        {
            if(c[i]==0) continue;
            for(int j=0;j<=i-1;++j) p[j]=-1e9;
            p[0]=0;
            for(int j=1;j<=n;++j)
            {
                if(f[j]) p[j%i]=j;
                if(p[j%i]>=j-i*c[i]) f[j]=true;
            }
        }
        int s=0,w=0;
        for(int i=1;i<=q;++i) s+=b[i];
        for(int i=0;i<=m;++i)
        {
            if(f[i]) w=i;
        }
        // printf("%d %d %d\n",q,s,w);
        if(s-w<=n-m) printf("%d\n",q);
        else printf("%d\n",q-1);
    }
    return 0;
}