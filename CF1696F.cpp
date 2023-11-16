#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=201;
int n,q,p=1,t[N],f[N][N];
char b[N][N][N];
bool h[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
struct str
{
    int x,y;
}c[N];
void solve(int x)
{
    queue<str> Q;
    for(int i=1;i<=n;++i) h[i]=false;
    Q.push((str){1,x});
    Q.push((str){x,1});
    q=0;
    h[1]=h[x]=true;
    while(!Q.empty())
    {
        str k=Q.front();
        Q.pop();
        if(k.x!=1)
        {
            c[++q]=(str){k.x,k.y};
            road(k.x,k.y);
            road(k.y,k.x);
        }
        for(int i=1;i<=n;++i)
        {
            if(h[i]==false&&b[k.x][k.y][i])
            {
                h[i]=true;
                Q.push((str){i,k.x});
            }
        }
    }
}
void dfs(int x,int fa,int *f)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        f[a[i].m]=f[x]+1;
        dfs(a[i].m,x,f);
    }
}
bool check()
{
    for(int i=1;i<=n;++i)
    {
        f[i][i]=1;
        dfs(i,0,f[i]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n;++k)
            {
                if(b[i][j][k]^(f[i][j]==f[i][k])) return false;
            }
        }
    }
    return true;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            for(int j=i+1;j<=n;++j)
            {
                char z[N];
                scanf("%s",z+1);
                for(int k=1;k<=n;++k)
                {
                    b[k][i][j]=b[k][j][i]=(z[k]=='1');
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) b[i][j][j]=1;
        }
        bool u=false;
        for(int i=2;i<=n;++i)
        {
            p=1;
            for(int j=1;j<=n;++j) t[j]=0;
            solve(i);
            if(q!=n-1) continue;
            if(check())
            {
                u=true;
                printf("Yes\n");
                for(int j=1;j<=n-1;++j)
                {
                    printf("%d %d\n",c[j].x,c[j].y);
                }
                break;
            }
        }
        if(!u) printf("No\n");
    }
    return 0;
}