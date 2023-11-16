#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,q,p=1,s1,s2,t[10001],t0[10001],f[10001];
struct str
{
    int m,q,r,w;
}a[1000001];
void road(int x,int y,int r,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
bool bfs(int w)
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=n;++i) f[i]=0;
    f[s1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r!=0&&a[i].w<=w)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
int dfs(int x,int r,int w)
{
    if(x==s2) return r;
    int s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0&&a[i].w<=w)
        {
            int z=dfs(a[i].m,min(r,a[i].r),w);
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
    s1=1;
    s2=n;
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,1,w);
        road(y,x,0,0);
        road(y,x,1,w);
        road(x,y,0,0);
    }
    int r=0;
    for(int i=1;;++i)
    {
        while(bfs(i))
        {
            for(int j=1;j<=n;++j) t0[j]=t[j];
            r+=dfs(s1,1e9,i);
        }
        if(r>=q)
        {
            printf("%d",i);
            return 0;
        }
    }
    return 0;
}