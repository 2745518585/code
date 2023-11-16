#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=30;
int n,las=1,tot=1,l[N<<1];
ll f[N<<1],g[N<<1];
char b[N];
bool h[N<<1];
struct tree
{
    int s[M],l,f;
}a[N<<1];
void add(int c)
{
    int x=las,nx=las=++tot;
    f[tot]=1;
    a[nx].l=a[x].l+1;
    while(x!=0&&a[x].s[c]==0)
    {
        a[x].s[c]=nx;
        x=a[x].f;
    }
    if(x==0) a[nx].f=1;
    else
    {
        int y=a[x].s[c];
        if(a[x].l+1==a[y].l) a[nx].f=y;
        else
        {
            int ny=++tot;
            a[ny]=a[y];
            a[ny].l=a[x].l+1;
            a[y].f=a[nx].f=ny;
            while(x!=0&&a[x].s[c]==y)
            {
                a[x].s[c]=ny;
                x=a[x].f;
            }
        }
    }
}
void tpsort()
{
    for(int i=2;i<=tot;++i) ++l[a[i].f];
    queue<int> Q;
    for(int i=1;i<=tot;++i)
    {
        if(l[i]==0)
        {
            g[i]=1;
            Q.push(i);
        }
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        g[a[k].f]+=g[k];
        --l[a[k].f];
        if(l[a[k].f]==0) Q.push(a[k].f);
    }
}
void dfs(int x)
{
    if(h[x]==true) return;
    h[x]=true;
    for(int i=1;i<=26;++i)
    {
        if(a[x].s[i]!=0)
        {
            dfs(a[x].s[i]);
            f[x]+=f[a[x].s[i]];
        }
    }
}
int main()
{
    scanf("%d%s",&n,b+1);
    for(int i=1;i<=n;++i) add(b[i]-'a'+1);
    for(int i=2;i<=tot;++i) f[i]=g[i]=1;
    dfs(1);
    printf("%lld",f[1]);
    return 0;
}
