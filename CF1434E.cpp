#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int N=110001,M=451;
int n,m,q,a[N],f[N],g[N];
bool h[M][N],e[N];
vector<pair<int,int>> c[N];
priority_queue<int> Q[M];
int solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    if(n==1) return 1;
    m=min((int)sqrt(a[n])*2+10,450);
    for(int i=0;i<=m;++i)
    {
        f[i]=g[i]=e[i]=0;
        while(!Q[i].empty()) Q[i].pop();
        for(int j=0;j<=n;++j) h[i][j]=false;
    }
    for(int i=0;i<=n;++i) vector<pair<int,int>>().swap(c[i]);
    c[n-1].push_back(make_pair(0,n));
    e[0]=true;
    for(int i=n-1;i>=0;--i)
    {
        for(auto j:c[i])
        {
            h[j.first][j.second]^=1;
            if(h[j.first][j.second]) Q[j.first].push(j.second);
        }
        vector<pair<int,int>>().swap(c[i]);
        for(int j=0;j<=m;++j) f[j]=g[j]=0;
        for(int j=0;j<=m;++j)
        {
            while(!Q[j].empty()&&h[j][Q[j].top()]==false) Q[j].pop();
            if(!Q[j].empty())
            {
                g[j]=Q[j].top();
            }
        }
        int x=n+1;
        for(int j=1;j<=m;++j)
        {
            x=min(x,g[j-1]);
            f[j]=x;
        }
        int z=i;
        for(int j=m;j>=0;--j)
        {
            if(f[j]==0) continue;
            e[j]=true;
            int p=lower_bound(a+1,a+n+1,a[i]-(a[f[j]]-a[i])+1)-a;
            if(p<i)
            {
                c[p-1].push_back(make_pair(j,i));
                c[z-1].push_back(make_pair(j,i));
                z=p;
            }
        }
    }
    int x=0;
    while(e[x]) ++x;
    return x;
}
int main()
{
    scanf("%d",&q);
    int s=0;
    for(int i=1;i<=q;++i) s^=solve();
    // printf("%d\n",s);
    if(s) printf("YES\n");
    else printf("NO\n");
    return 0;
}