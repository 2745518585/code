#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,a[N],b[N],c[N],fa[N];
vector<int> e[N];
struct str
{
    int x,w;
    str() {}
    str(int x,int w):x(x),w(w) {}
    friend bool operator<(str a,str b)
    {
        return a.w<b.w;
    }
};
priority_queue<str> Q;
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i]=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            ++a[x];
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&b[i]);
            e[i].resize(b[i]+1);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&c[i]);
        }
        for(int i=1;i<=n;++i)
        {
            if(a[i]) Q.push(str(i,a[i]));
        }
        bool u=false;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=b[i];++j)
            {
                if(Q.empty())
                {
                    u=true;
                    break;
                }
                e[i][j]=Q.top().x;
                --a[Q.top().x];
                Q.pop();
                if(j>=c[i]&&a[e[i][j-c[i]+1]]) Q.push(str(e[i][j-c[i]+1],a[e[i][j-c[i]+1]]));
            }
            if(u) break;
            for(int j=b[i]-c[i]+2;j<=b[i];++j)
            {
                if(a[e[i][j]]) Q.push(str(e[i][j],a[e[i][j]]));
            }
            if(u) break;
        }
        if(u)
        {
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=b[i];++j)
            {
                printf("%d ",e[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}