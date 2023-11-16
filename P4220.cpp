#include<cstdio>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;
typedef long long ll;
const int N=100001;
int n;
ll f[3][N];
bool h[N];
vector<pair<int,ll>> a[3][N];
void dfs(int x,int fa,int t)
{
    for(auto i:a[t][x])
    {
        if(i.first==fa) continue;
        f[t][i.first]=f[t][x]+i.second;
        dfs(i.first,x,t);
    }
}
int main()
{
    srand(time(NULL));
    scanf("%d",&n);
    for(int i=0;i<=2;++i)
    {
        for(int j=1;j<=n-1;++j)
        {
            int x,y;
            ll w;
            scanf("%d%d%lld",&x,&y,&w);
            a[i][x].push_back(make_pair(y,w));
            a[i][y].push_back(make_pair(x,w));
        }
    }
    int x=1;
    ll s=0;
    while((double)clock()/CLOCKS_PER_SEC<3.5)
    {
        if(h[x])
        {
            x=rand()*rand()%n+1;
            continue;
        }
        h[x]=true;
        f[0][x]=f[1][x]=f[2][x]=0;
        dfs(x,0,0);
        dfs(x,0,1);
        dfs(x,0,2);
        int z=0;
        for(int i=1;i<=n;++i)
        {
            if(f[0][i]+f[1][i]+f[2][i]>f[0][z]+f[1][z]+f[2][z]) z=i;
        }
        s=max(s,f[0][z]+f[1][z]+f[2][z]);
        x=z;
    }
    printf("%lld",s);
    return 0;
}