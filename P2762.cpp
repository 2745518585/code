#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int m,n,N,q,p=1,s1,s2,t[10001],t0[10001],f[10001];
struct str
{
    int m,q,r;
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
    scanf("%d%d",&m,&n);
    N=m+n+2;
    s1=N-1;
    s2=N;
    for(int i=1;i<=m;++i)
    {
        int w;
        scanf("%d ",&w);
        q+=w;
        road(s1,i,w);
        road(i,s1,0);
        char c=getchar();
        int x=0;
        while((c>='0'&&c<='9')||c==' ')
        {
            if(c==' ')
            {
                road(i,m+x,1e9);
                road(m+x,i,0);
                x=0;
            }
            else x=x*10+c-'0';
            c=getchar();
        }
        road(i,m+x,1e9);
        road(m+x,i,0);
    }
    for(int i=1;i<=n;++i)
    {
        int w;
        scanf("%d",&w);
        road(m+i,s2,w);
        road(s2,m+i,0);
    }
    int r=0;
    while(bfs())
    {
        for(int i=1;i<=N;++i) t0[i]=t[i];
        r+=dfs(s1,1e9);
    }
    for(int i=1;i<=m;++i)
    {
        if(f[i]!=0) printf("%d ",i);
    }
    printf("\n");
    for(int i=1;i<=n;++i)
    {
        if(f[m+i]!=0) printf("%d ",i);
    }
    printf("\n");
    printf("%d",q-r);
    return 0;
}