#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,n1,n2,n3,m1,m2,p=1,s1,s2,t[10001],f[10001];
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
    for(int i=1;i<=n;++i) f[i]=0;
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
    for(int i=t[x];i!=0;i=a[i].q)
    {
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
        }
    }
    return s;
}
int main()
{
    scanf("%d%d%d%d",&n1,&n2,&n3,&m1);
    n=n1*2+n2+n3+2;
    s1=1;
    s2=n;
    for(int i=1;i<=m1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(y+n1*2+1,x+1,1);
        road(x+1,y+n1*2+1,0);
    }
    scanf("%d",&m2);
    for(int i=1;i<=m2;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x+n1+1,y+n1*2+n2+1,1);
        road(y+n1*2+n2+1,x+n1+1,0);
    }
    for(int i=1;i<=n1;++i)
    {
        road(i+1,i+n1+1,1);
        road(i+n1+1,i+1,0);
    }
    for(int i=1;i<=n2;++i)
    {
        road(1,i+n1*2+1,1);
        road(i+n1*2+1,1,0);
    }
    for(int i=1;i<=n3;++i)
    {
        road(i+n1*2+n2+1,n,1);
        road(n,i+n1*2+n2+1,0);
    }
    int r=0;
    while(bfs())
    {
        r+=dfs(s1,1e9);
    }
    printf("%d",r);
    return 0;
}