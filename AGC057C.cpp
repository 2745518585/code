#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,a[N],b[N],c[N],g[N];
vector<int> d;
int get(int x,int u)
{
    if((b[g[x]]^c[x]^u)==0) return x<<1;
    return x<<1|1;
}
int find(int k)
{
    int x=1;
    for(int i=0;i<=n-1;++i)
    {
        x=get(x,(k&(1<<i))!=0);
    }
    return x;
}
int find2(int k)
{
    int x=1;
    for(int i=0;i<=n-1;++i)
    {
        if((k&(1<<i))==0) x=x<<1;
        else x=x<<1|1;
    }
    return x;
}
void dfs(int x,int k)
{
    if(g[x]==n)
    {
        if(a[x]!=k)
        {
            printf("No");
            exit(0);
        }
        return;
    }
    dfs(get(x,0),k);
    dfs(get(x,1),k+(1<<g[x]));
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=(1<<n)*2-1;++i) g[i]=g[i/2]+1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        int x;
        scanf("%d",&x);
        a[find(x)]=i;
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        int x=find2(i)/2;
        if(a[get(x,0)]<a[get(x,1)]) continue;
        int w=0;
        for(int j=n-2;j>=0;--j)
        {
            if(x==get(x/2,0)) b[j]^=1,w^=(1<<j);
            x/=2;
        }
        d.push_back(w);
        x=1;
        for(int j=0;j<=n-1;++j)
        {
            c[x]^=1;
            x=get(x,0);
        }
        d.push_back(-1);
    }
    int x=1,w=0;
    for(int i=0;i<=n-1;++i)
    {
        if(a[find(0)]>a[find(1<<i)]) b[i]^=1,w^=(1<<i);
        x=get(x,0);
    }
    d.push_back(w);
    dfs(1,0);
    printf("Yes\n%d\n",d.size());
    for(auto i:d) printf("%d ",i);
    return 0;
}