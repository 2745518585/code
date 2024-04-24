#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,b[N],q1,q2,b1[N],b2[N];
bool g[N],h[N];
vector<pair<int,int>> a[N],ans;
bool dfs(int x,int fa)
{
    h[x]=true;
    vector<int> p;
    for(auto i:a[x])
    {
        if(g[i.second]) continue;
        g[i.second]=true;
        if(h[i.first])
        {
            p.push_back(i.second);
            continue;
        }
        if(dfs(i.first,i.second)) p.push_back(i.second);
    }
    bool u=true;
    if(p.size()%2==1) u=false,p.push_back(fa);
    for(int i=0;i<p.size();i+=2) ans.push_back(make_pair(p[i],p[i+1]));
    return u;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        q1=q2=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
            b1[++q1]=b[i]+i;
            b2[++q2]=b[i]-i;
        }
        sort(b1+1,b1+q1+1);
        q1=unique(b1+1,b1+q1+1)-b1-1;
        sort(b2+1,b2+q2+1);
        q2=unique(b2+1,b2+q2+1)-b2-1;
        for(int i=1;i<=n;++i) g[i]=false;
        for(int i=1;i<=q1+q2;++i) a[i].clear(),h[i]=false;
        ans.clear();
        for(int i=1;i<=n;++i)
        {
            int x=lower_bound(b1+1,b1+q1+1,b[i]+i)-b1,y=q1+lower_bound(b2+1,b2+q2+1,b[i]-i)-b2;
            a[x].push_back(make_pair(y,i));
            a[y].push_back(make_pair(x,i));
        }
        bool u=false;
        for(int i=1;i<=q1+q2;++i)
        {
            if(!dfs(i,0))
            {
                u=true;
                break;
            }
        }
        if(u)
        {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
        for(auto i:ans) printf("%d %d\n",i.first,i.second);
    }
    return 0;
}