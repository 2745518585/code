#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=301,inf=1e9;
int n,m,q,f[N][N][N];
ll d[N];
vector<int> a1[N],a2[N];
struct pt
{
    int z,x,y;
}b[N];
struct str
{
    int x,w;
    str() {}
    str(int x,int w):x(x),w(w) {}
    friend bool operator<(str a,str b)
    {
        if(a.x!=b.x) return a.x<b.x;
        return a.w<b.w;
    }
}g[N][N*N];
ll solve()
{
    for(int i=0;i<=q;++i)
    {
        for(int j=0;j<=q;++j) f[1][i][j]=-inf;
    }
    f[1][0][0]=0;
    for(int i=2;i<=n;++i)
    {
        for(int j=0;j<=q;++j)
        {
            for(int k=0;k<=q;++k) f[i][j][k]=-inf;
        }
        for(auto j:a2[i])
        {
            for(int k=0;k<=q;++k)
            {
                for(int l=0;l<=q;++l)
                {
                    if(b[i].z==1)
                    {
                        f[i][max(k,b[i].x)][l]=max(f[i][max(k,b[i].x)][l],f[j][k][l]+b[i].x*b[i].y);
                        if(b[i].x+l<=q) f[i][max(k,b[i].x+l)][l]=max(f[i][max(k,b[i].x+l)][l],f[j][k][0]+(b[i].x+l)*b[i].y);
                    }
                    else if(b[i].z==2)
                    {
                        f[i][k][max(l-b[i].x,0)]=max(f[i][k][max(l-b[i].x,0)],f[j][k][l]);
                    }
                    else if(b[i].z==3)
                    {
                        f[i][k][l]=max(f[i][k][l],f[j][k][l]+k*b[i].x);
                    }
                    else if(b[i].z==4)
                    {
                        f[i][k][l]=max(f[i][k][l],f[j][k][l]+b[i].x);
                    }
                    else f[i][k][l]=max(f[i][k][l],f[j][k][l]);
                }
            }
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        for(auto j:a1[i])
        {
            for(int k=0;k<=q;++k)
            {
                s=max(s,f[i][k][0]+d[j]);
            }
        }
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i].z);
        if(b[i].z!=0) scanf("%d",&b[i].x);
        if(b[i].z==1) scanf("%d",&b[i].y);
        if(b[i].z!=4) q=max(q,max(b[i].x,b[i].y));
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a1[x].push_back(y);
        a2[y].push_back(x);
    }
    for(int i=0;i<=n*q;++i) g[n][i]=str(-inf,-inf);
    g[n][0]=str(0,0);
    for(int i=n-1;i>=1;--i)
    {
        for(int j=0;j<=n*q;++j) g[i][j]=str(-inf,-inf);
        for(auto j:a1[i])
        {
            for(int k=0;k<=n*q;++k)
            {
                if(b[i].z==1)
                {
                    g[i][k]=max(g[i][k],str(g[j][k].x,g[j][k].w+b[i].x*b[i].y));
                }
                else if(b[i].z==2)
                {
                    if(k>=b[i].x) g[i][k]=max(g[i][k],g[j][k-b[i].x]);
                }
                else if(b[i].z==3)
                {
                    g[i][k]=max(g[i][k],str(g[j][k].x+b[i].x,g[j][k].w));
                }
                else if(b[i].z==4)
                {
                    g[i][k]=max(g[i][k],str(g[j][k].x,g[j][k].w+b[i].x));
                }
                else g[i][k]=max(g[i][k],g[j][k]);
            }
        }
        if(b[i].z==1)
        {
            for(auto j:a1[i])
            {
                for(int k=0;k<=n*q;++k)
                {
                    if(g[j][k].x>=0) d[i]=max(d[i],(ll)(b[i].x+k)*(b[i].y+g[j][k].x)*inf+g[j][k].w);
                }
            }
        }
    }
    // for(int i=1;i<=n;++i) printf("%lld ",d[i]);printf("\n");
    ll s=solve();
    for(int i=1;i<=n;++i)
    {
        if(b[i].z==1) swap(b[i].x,b[i].y);
        else if(b[i].z==2) b[i].z=3;
        else if(b[i].z==3) b[i].z=2;
    }
    s=max(s,solve());
    printf("%lld",s);
    return 0;
}