#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
const int N=100001,M=1000001;
struct str
{
    int m,q;
}a[M];
stack<int> S;
int n,m,p=1,q=0,s=0,t[N],b[N],c[N],r[N];
bool h[N];
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
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
    }
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0) dfs(i);
    }
    printf("%d\n",s);
    for(int i=1;i<=s;++i) h[i]=false;
    for(int i=1;i<=n;++i)
    {
        if(h[r[i]]==true) continue;
        h[r[i]]=true;
        int w=0;
        for(int j=1;j<=n;++j)
        {
            if(r[j]==r[i]) ++w;
        }
        printf("%d ",w);
        for(int j=1;j<=n;++j)
        {
            if(r[j]==r[i]) printf("%d ",j);
        }
        printf("\n");
    }
    return 0;
}