#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=1000001,K=101;
int n,m,q1,q2,d,p=1,s1,s2,t[N],t0[N],f[N],b[K][K],g1[K][K],g2[K][K];
struct road
{
    int m,q;
    ll r;
}a[M];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i) f[i]=0;
    f[s1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r!=0)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            int z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        char z[K];
        scanf("%s",z+1);
        for(int j=1;j<=n;++j)
        {
            if(z[j]=='*') b[i][j]=0;
            else if(z[j]=='x') b[i][j]=1;
            else if(z[j]=='#') b[i][j]=2;
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int k=j-1;
            while(k+1<=n&&b[i][k+1]!=2) ++k;
            if(j<=k)
            {
                ++q1;
                for(int l=j;l<=k;++l) g1[i][l]=q1;
            }
            while(k+1<=n&&b[i][k+1]==2) ++k;
            j=k;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            int k=j-1;
            while(k+1<=m&&b[k+1][i]!=2) ++k;
            if(j<=k)
            {
                ++q2;
                for(int l=j;l<=k;++l) g2[l][i]=q1+q2;
            }
            while(k+1<=m&&b[k+1][i]==2) ++k;
            j=k;
        }
    }
    s1=q1+q2+1,s2=q1+q2+2;
    for(int i=1;i<=q1;++i)
    {
        road(s1,i,1);
        road(i,s1,0);
    }
    for(int i=q1+1;i<=q1+q2;++i)
    {
        road(i,s2,1);
        road(s2,i,0);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[i][j]==0)
            {
                road(g1[i][j],g2[i][j],1);
                road(g2[i][j],g1[i][j],0);
            }
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",r);
    return 0;
}