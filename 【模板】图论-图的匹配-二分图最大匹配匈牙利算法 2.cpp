#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=100001;
int n1,n2,m,p=0,t[N],g1[N],g2[N],r[N];
bool h[N];
struct str
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void check(int x,int y)
{
    while(true)
    {
        int z=g1[r[y]];
        g2[y]=r[y];
        g1[r[y]]=y;
        if(r[y]==x) break;
        y=z;
    }
}
bool bfs(int x)
{
    for(int i=1;i<=n2;++i) h[i]=false;
    queue<int> Q;
    Q.push(x);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(h[a[i].m]==true) continue;
            h[a[i].m]=true;
            r[a[i].m]=k;
            if(g2[a[i].m]==0)
            {
                check(x,a[i].m);
                return true;
            }
            else Q.push(g2[a[i].m]); 
        }
    }
    return false;
}
int main()
{
    scanf("%d%d%d",&n1,&n2,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
    }
    int s=0;
    for(int i=1;i<=n1;++i)
    {
        if(bfs(i)) ++s;
    }
    printf("%d",s);
    return 0;
}