#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
const int N=2000001;
stack<int> S;
int n,m,p=0,q=0,s=0,t[N],d[N],b[N],c[N],r[N];
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
void dfs(int x)
{
    b[x]=c[x]=++q;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(b[a[i].m]==0)
        {
            dfs(a[i].m);
            c[x]=min(c[x],c[a[i].m]);
        }
        else if(h[a[i].m]==false)
        {
            c[x]=min(c[x],c[a[i].m]);
        }
    }
    if(b[x]==c[x])
    {
        ++s;
        while(S.top()!=x)
        {
            h[S.top()]=true;
            r[S.top()]=s;
            S.pop();
        }
        h[x]=true;
        r[x]=s;
        S.pop();
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        road(i*2-1,i*2+n*2);
        road(i*2,i*2-1+n*2);
        road(i*2+n*2,i*2-1);
        road(i*2-1+n*2,i*2);
    }
    n*=2;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,n+y);
        road(y,n+x);
    }
    for(int i=1;i<=n*2;++i)
    {
        if(b[i]==0) dfs(i);
    }
    for(int i=1;i<=n;++i)
    {
        if(c[i]==c[n+i])
        {
            printf("NIE");
            return 0;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(r[i]<r[n+i]) printf("%d\n",i);
    }
    return 0;
}