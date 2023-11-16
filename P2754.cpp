#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int N,M=200,n,m,q,p=1,s1,s2,t[10001],t0[10001],f[10001],e[201][501],y[501],z[501];
bool u=true;
struct str
{
    int m,q;
    int r;
}a[1000001];
void road(int x,int y,int r)
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
    for(int i=1;i<=N;++i) f[i]=0;
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
int dfs(int x,int r)
{
    if(x==s2) return r;
    int s=0;
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
    scanf("%d%d%d",&n,&m,&q);
    n+=2;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&z[i],&y[i]);
        for(int j=0;j<=y[i]-1;++j)
        {
            scanf("%d",&e[i][j]);
            e[i][j]+=2;
        }
    }
    s1=2;
    int r=0;
    for(int i=1;i<=M;++i)
    {
        N=(i+1)*n;
        s2=i*n+1;
        for(int j=1;j<=n;++j)
        {
            road((i-1)*n+j,i*n+j,1e9);
            road(i*n+j,(i-1)*n+j,0);
        }
        for(int j=1;j<=m;++j)
        {
            road((i-1)*n+e[j][(i-1)%y[j]],i*n+e[j][i%y[j]],z[j]);
            road(i*n+e[j][i%y[j]],(i-1)*n+e[j][(i-1)%y[j]],0);
        }
        while(bfs())
        {
            for(int j=1;j<=N;++j) t0[j]=t[j];
            r+=dfs(s1,1e9);
        }
        if(r>=q)
        {
            printf("%d",i);
            return 0;
        }
    }
    printf("0");
    return 0;
}
