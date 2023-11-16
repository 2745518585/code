#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,q,tot;
ll f[N],g[N];
bool h[N];
vector<int> a[N],a2[N];
stack<int> S;
struct tree
{
    int b,c;
}T[N];
void dfs(int x)
{
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
                if(S.top()==i)
                {
                    S.pop();
                    a2[x].push_back(i);
                    a2[i].push_back(x);
                }
                else
                {
                    ++q;
                    while(S.top()!=i) S.pop();
                    S.pop();
                }
            }
        }
        T[x].c=min(T[x].c,T[i].b);
    }
}
void dfs2(int x,int fa)
{
    h[x]=true;
    f[x]=1;
    for(auto i:a2[x])
    {
        if(i==fa) continue;
        dfs2(i,x);
        f[x]=(f[x]*f[i])%P;
    }
    f[x]=(f[x]*g[a2[x].size()])%P;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        tot=q=0;
        for(int i=1;i<=n;++i) a[i].clear(),a2[i].clear(),T[i].b=T[i].c=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        dfs(1);
        if(n+q-1!=m)
        {
            printf("0\n");
            continue;
        }
        g[0]=g[1]=1;
        for(int i=2;i<=n;++i) g[i]=(g[i-1]+g[i-2]*(i-1))%P;
        for(int i=1;i<=n;++i) h[i]=false;
        ll s=1;
        for(int i=1;i<=n;++i)
        {
            if(h[i]) continue;
            dfs2(i,0);
            s=(s*f[i])%P;
        }
        printf("%lld\n",s);
    }
    return 0;
}