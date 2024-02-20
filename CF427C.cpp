#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,q,tot,b[N],c[N],d[N],r[N];
vector<int> a[N];
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
        }
        else if(r[i]==0)
        {
            T[x].c=min(T[x].c,T[i].c);
        }
    }
    if(T[x].b==T[x].c)
    {
        ++q;
        while(S.top()!=x)
        {
            r[S.top()]=q;
            S.pop();
        }
        r[x]=q;
        S.pop();
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
    }
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i);
    }
    for(int i=1;i<=q;++i) c[i]=1e9;
    for(int i=1;i<=n;++i)
    {
        if(b[i]<c[r[i]]) c[r[i]]=b[i],d[r[i]]=1;
        else if(b[i]==c[r[i]]) ++d[r[i]];
    }
    ll s=0,w=1;
    for(int i=1;i<=q;++i)
    {
        s+=c[i];
        w=(w*d[i])%P;
    }
    printf("%lld %lld",s,w);
    return 0;
}
