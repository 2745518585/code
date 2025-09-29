#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,tot,r[N];
ll k,b[N];
vector<int> a[N];
struct tree
{
    int b,c;
}T[N];
void dfs(int x,int fa)
{
    T[x].b=T[x].c=++tot;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(T[i].b==0)
        {
            dfs(i,x);
            T[x].c=min(T[x].c,T[i].c);
            if(T[i].c>T[x].b) --r[x],--r[i];
        }
        T[x].c=min(T[x].c,T[i].b);
    }
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d%lld",&n,&m,&k);
        tot=0;
        for(int i=1;i<=n;++i) T[i].b=T[i].c=r[i]=0,a[i].clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&b[i]);
        }
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            ++r[x],++r[y];
            a[x].push_back(y);
            a[y].push_back(x);
        }
        for(int i=1;i<=n;++i)
        {
            if(T[i].b==0) dfs(i,0);
        }
        ll s=1;
        for(int i=1;i<=n;++i)
        {
            if(r[i]==0) s=s*k%P;
            else if(b[i]!=-1&&b[i]!=0) s=0;
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}