#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,q,a[N],f[N],g[N],T[N];
bool h[N];
vector<vector<int>> ans;
int check(int x,int y)
{
    return f[x]>f[y]?x:y;
}
void add(int x,int k)
{
    while(x<=n) T[x]=check(T[x],k),x+=x&-x;
}
int sum(int x)
{
    int s=0;
    while(x>=1) s=check(s,T[x]),x-=x&-x;
    return s;
}
void solve0()
{
    int p=ans.size();
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        int l=p,r=ans.size();
        while(l<r)
        {
            int z=l+r>>1;
            if(a[ans[z].back()]>a[i]) r=z;
            else l=z+1;
        }
        if(l==ans.size()) ans.push_back(vector<int>());
        ans[l].push_back(i);
    }
}
void solve()
{
    for(int i=1;i<=n;++i) T[i]=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        g[i]=sum(a[i]-1);
        f[i]=f[g[i]]+1;
        add(a[i],i);
    }
    int x=sum(n);
    if(f[x]<=q-ans.size())
    {
        solve0();
        return;
    }
    ans.push_back(vector<int>());
    while(x!=0)
    {
        ans.back().push_back(x);
        h[x]=true;
        x=g[x];
    }
    reverse(ans.back().begin(),ans.back().end());
    solve();
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        q=0;
        while((q+1)*(q+2)/2<=n) ++q;
        ans.clear();
        for(int i=1;i<=n;++i) h[i]=false;
        solve();
        printf("%d\n",ans.size());
        for(auto i:ans)
        {
            printf("%d ",i.size());
            for(auto j:i) printf("%d ",a[j]);
            printf("\n");
        }
    }
    return 0;
}