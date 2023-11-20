#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,t,tot,g[N];
ll s,f[N];
vector<int> a[N],a2[N];
stack<int> S;
struct tree
{
    int b,c;
}T[N];
void dfs(int x)
{
    ++t;
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(auto i:a[x])
    {
        if(T[i].b==0)
        {
            dfs(i);
            T[x].c=min(T[x].c,T[i].c);
            if(T[i].c==T[x].b)
            {
                ++q;
                while(true)
                {
                    a2[q].push_back(S.top());
                    a2[S.top()].push_back(q);
                    ++g[q];
                    if(S.top()==i) break;
                    S.pop();
                }
                S.pop();
                a2[q].push_back(x);
                a2[x].push_back(q);
                ++g[q];
            }
        }
        T[x].c=min(T[x].c,T[i].b);
    }
}
void dfs2(int x,int fa)
{
    int u;
    if(x<=n) f[x]=1,u=-1;
    else f[x]=0,u=g[x];
    for(auto i:a2[x])
    {
        if(i==fa) continue;
        dfs2(i,x);
        s+=(ll)u*f[x]*f[i];
        f[x]+=f[i];
    }
    s+=(ll)u*f[x]*(t-f[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    q=n;
    for(int i=1;i<=n;++i)
    {
        if(T[i].b!=0) continue;
        t=0;
        dfs(i);
        dfs2(i,0);
    }
    printf("%lld",s*2);
    return 0;
}