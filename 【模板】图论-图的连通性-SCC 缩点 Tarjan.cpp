#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,q,tot,b[N],r[N],l[N],f[N],g[N];
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
        }
        else if(r[i]==0)
        {
            T[x].c=min(T[x].c,T[i].b);
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
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
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
    for(int i=1;i<=n;++i)
    {
        g[r[i]]+=b[i];
        for(auto j:a[i])
        {
            if(r[i]!=r[j]) a2[r[i]].push_back(r[j]),++l[r[j]];
        }
    }
    for(int i=1;i<=q;++i) f[i]=g[i];
    queue<int> Q;
    for(int i=1;i<=q;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(auto i:a2[k])
        {
            f[i]=max(f[i],f[k]+g[i]);
            --l[i];
            if(l[i]==0) Q.push(i);
        }
    }
    int s=0;
    for(int i=1;i<=q;++i) s=max(s,f[i]);
    printf("%d",s);
    return 0;
}