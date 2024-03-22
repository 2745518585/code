#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,d1[N],d2[N];
vector<int> a[N];
void dfs(int x,int fa,int *d)
{
    for(auto i:a[x])
    {
        if(i==fa) continue;
        d[i]=d[x]+1;
        dfs(i,x,d);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        d1[1]=0;
        dfs(1,0,d1);
        int x=1;
        for(int i=1;i<=n;++i)
        {
            if(d1[i]>d1[x]) x=i;
        }
        d2[x]=1;
        dfs(x,0,d2);
        int y=1;
        for(int i=1;i<=n;++i)
        {
            if(d2[i]>d2[y]) y=i;
        }
        d1[y]=1;
        dfs(y,0,d1);
        int p=1,q=2;
        for(int i=1;i<=n;++i)
        {
            if(max(d1[i],d2[i])<max(d1[p],d2[p])) p=i;
        }
        for(int i=1;i<=n;++i)
        {
            if(max(d1[i],d2[i])==max(d1[p],d2[p])&&i!=p) q=i;
        }
        int t=d2[y];
        if(t%4==0)
        {
            printf("%d\n",t/2);
            for(int i=1;i<t/2;i+=2)
            {
                printf("%d %d\n",p,i);
                printf("%d %d\n",q,i);
            }
        }
        else
        {
            printf("%d\n",t/2+1);
            for(int i=0;i<max(d1[p],d2[p]);++i)
            {
                printf("%d %d\n",p,i);
            }
        }
    }
    return 0;
}