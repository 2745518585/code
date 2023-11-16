#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=5001;
int n,m,tot,fa[N];
bool h[N],u;
vector<int> a[N];
stack<int> S;
struct str
{
    int l1,r1,l2,r2;
}b[N];
struct tree
{
    int b,c;
}T[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
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
        else if(h[i]==false) T[x].c=min(T[x].c,T[i].c);
    }
    if(T[x].b==T[x].c)
    {
        while(S.top()!=x)
        {
            fa[find(S.top())]=find(x);
            h[S.top()]=true;
            S.pop();
            u=true;
        }
        h[x]=true;
        S.pop();
    }
}
void solve()
{
    for(int i=1;i<=n;++i) a[i].clear();
    for(int i=1;i<=m;++i)
    {
        while(b[i].l1<=b[i].r1&&b[i].l2<=b[i].r2)
        {
            if(find(b[i].l1)!=find(b[i].l2)) break;
            ++b[i].l1,++b[i].l2;
        }
        if(b[i].l1>b[i].r1||b[i].l2>b[i].r2)
        {
            if(b[i].l2>b[i].r2)
            {
                printf("No");
                exit(0);
            }
        }
        else a[find(b[i].l1)].push_back(find(b[i].l2));
    }
    for(int i=1;i<=n;++i) T[i].b=T[i].c=h[i]=0;
    while(!S.empty()) S.pop();
    tot=u=0;
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i);
    }
    if(!u)
    {
        printf("Yes");
        exit(0);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d%d",&b[i].l1,&b[i].r1,&b[i].l2,&b[i].r2);
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    while(true) solve();
    return 0;
}