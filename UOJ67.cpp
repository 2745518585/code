#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,tot;
bool h[N];
vector<int> a[N];
struct tree
{
    int b,c;
}T[N];
void dfs(int x,int rt)
{
    T[x].b=T[x].c=++tot;
    int u=0;
    for(auto i:a[x])
    {
        if(T[i].b==0)
        {
            dfs(i,rt);
            ++u;
            T[x].c=min(T[x].c,T[i].c);
            if(x!=rt&&T[i].c>=T[x].b) h[x]=true;
        }
        T[x].c=min(T[x].c,T[i].b);
    }
    if(x==rt&&u>=2) h[rt]=true;
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
    dfs(1,1);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(!h[i]&&a[i].size()==m-n+2) ++s;
    }
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        if(!h[i]&&a[i].size()==m-n+2) printf("%d ",i);
    }
    return 0;
}