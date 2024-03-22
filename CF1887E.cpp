#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2001;
int n,q,a1[N],a2[N],b[N][N];
bool h[N];
vector<int> a[N],p;
int query(int x,int y)
{
    if(x>y) swap(x,y);
    printf("? %d %d\n",x,y-n);
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
bool dfs(int x,int fa)
{
    if(h[x])
    {
        vector<int> z;
        while(p.back()!=x) z.push_back(p.back()),p.pop_back();
        z.push_back(x);
        swap(p,z);
        return true;
    }
    h[x]=true;
    p.push_back(x);
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(dfs(i,x)) return true;
    }
    p.pop_back();
    return false;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        p.clear();
        for(int i=1;i<=n*2;++i) a[i].clear(),h[i]=false;
        for(int i=1;i<=n*2;++i)
        {
            for(int j=1;j<=n*2;++j) b[i][j]=0;
        }
        for(int i=1;i<=n*2;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            b[x][n+y]=b[n+y][x]=i;
            a[x].push_back(n+y);
            a[n+y].push_back(x);
        }
        dfs(1,0);
        q=p.size()/2;
        for(int i=1;i<=q;++i) a1[i]=p[i-1];
        for(int i=1;i<=q;++i) a2[i]=p[q*2-i];
        int l=1,r=q;
        while(r-l>1)
        {
            int z=l+r>>1;
            int t=query(a1[z],a2[z]);
            b[a1[z]][a2[z]]=b[a2[z]][a1[z]]=t;
            if([&](){
                for(int i=l;i<z;++i)
                {
                    if(b[a1[i]][a1[i+1]]==t) return false;
                    if(b[a2[i]][a2[i+1]]==t) return false;
                }
                if(b[a1[l]][a2[l]]==t) return false;
                return true;
            }()) r=z;
            else l=z;
        }
        int x1=n+1,x2=0,y1=n+1,y2=0;
        auto solve=[&](int p)
        {
            if(p<=n) x1=min(x1,p),x2=max(x2,p);
            else y1=min(y1,p-n),y2=max(y2,p-n);
        };
        solve(a1[l]),solve(a1[r]),solve(a2[l]),solve(a2[r]);
        printf("! %d %d %d %d\n",x1,x2,y1,y2);
        fflush(stdout);
        scanf("%*s");
    }
    return 0;
}