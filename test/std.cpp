#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],b[N],a2[N],b2[N];
bool h[N];
vector<int> p[N];
void dfs(int x)
{
    h[x]=true;
    for(int i:p[x])
    {
        if(h[i]) continue;
        dfs(i);
    }
}
ll sum()
{
    ll s=0;
    for(int i=1;i<=n;++i) p[i].clear();
    for(int i=1;i<=n-1;++i)
    {
        p[a2[i+1]].push_back(a2[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        p[b2[i+1]].push_back(b2[i]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) h[j]=false;
        dfs(i);
        for(int j=1;j<=n;++j) s+=h[j];
    }
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            a2[a[i]]=i;
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
            b2[b[i]]=i;
        }
        for(int i=1;i<=m;++i)
        {
            int z,x,y;
            scanf("%d%d%d",&z,&x,&y);
            if(z==1)
            {
                swap(a[x],a[y]);
                a2[a[x]]=x,a2[a[y]]=y;
            }
            else if(z==2)
            {
                swap(b[x],b[y]);
                b2[b[x]]=x,b2[b[y]]=y;
            }
            printf("%lld\n",sum());
        }
    }
    return 0;
}