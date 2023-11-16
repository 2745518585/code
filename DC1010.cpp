#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,N,p=1,s1,s2,t[100001],t0[100001],f[100001],b[100001],r[100001];
struct str
{
    int m,q,r;
}a[10000001];
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
    scanf("%d%d",&n,&m);
    s1=n+1;
    s2=n+2;
    N=n+2;
    for(int i=1;i<=m;++i)
    {
        int x,y,r1,r2;
        scanf("%d%d%d%d",&x,&y,&r1,&r2);
        r[i]=r1;
        road(x,y,r2-r1);
        road(y,x,0);
        b[x]+=r1;
        b[y]-=r1;
    }
    for(int i=1;i<=n;++i)
    {
        if(b[i]<0)
        {
            road(s1,i,-b[i]);
            road(i,s1,0);
        }
        else if(b[i]>0)
        {
            road(i,s2,b[i]);
            road(s2,i,0);
        }
    }
    while(bfs())
    {
        for(int i=1;i<=N;++i) t0[i]=t[i];
        dfs(s1,1e9);
    }
    for(int i=t[s1];i!=0;i=a[i].q)
    {
        if(a[i].r!=0)
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES\n");
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",a[i*2+1].r+r[i]);
    }
    return 0;
}