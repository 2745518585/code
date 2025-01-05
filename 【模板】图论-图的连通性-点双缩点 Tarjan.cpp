#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,q,tot;
vector<int> a[N],p[N];
stack<int> S;
struct tree
{
    int b,c;
}T[N];
void dfs(int x,int rt)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    int u=0;
    for(auto i:a[x])
    {
        if(T[i].b==0)
        {
            dfs(i,rt);
            T[x].c=min(T[x].c,T[i].c);
            if(T[i].c>=T[x].b)
            {
                ++q;
                while(S.top()!=i)
                {
                    p[q].push_back(S.top());
                    S.pop();
                }
                p[q].push_back(i);
                S.pop();
                p[q].push_back(x);
            }
            ++u;
        }
        T[x].c=min(T[x].c,T[i].b);
    }
    if(x==rt&&u==0) p[++q].push_back(x);
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
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i,i);
    }
    printf("%d\n",q);
    for(int i=1;i<=q;++i)
    {
        printf("%d ",p[i].size());
        for(auto j:p[i]) printf("%d ",j);
        printf("\n");
    }
    return 0;
}