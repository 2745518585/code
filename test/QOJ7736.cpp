#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,q,d[N],f0[N],g[N];
char b[N];
vector<int> a[N],f1[N],f2[N];
struct tree
{
    int s,md,z;
}T[N];
void dfs0(int x)
{
    if(a[x].size()==0) T[x].md=1;
    else T[x].md=1e9;
    T[x].s=(b[x]=='1');
    T[x].z=0;
    for(auto i:a[x])
    {
        dfs0(i);
        T[x].s+=T[i].s;
        T[x].md=min(T[x].md,T[i].md+1);
        if(T[i].md>T[T[x].z].md) T[x].z=i;
    }
}
void add(int x,int k)
{
    q=0;
    for(int i=0;i<f1[x].size()&&q<k;++i) d[++q]+=f1[x][i];
    q+=f0[x];
    for(int i=(int)f2[x].size()-1;i>=0&&q<k;--i) d[++q]+=f2[x][i];
}
void dfs(int x)
{
    f1[x].clear(),f2[x].clear(),f0[x]=0,g[x]=0;
    if(T[x].z)
    {
        dfs(T[x].z);
        f0[x]=f0[T[x].z];
        swap(f1[x],f1[T[x].z]);
        swap(f2[x],f2[T[x].z]);
        g[x]=g[T[x].z];
    }
    for(auto i:a[x])
    {
        if(i==T[x].z) continue;
        dfs(i);
        for(int j=1;j<=T[x].md-1;++j) d[j]=0;
        add(x,T[x].md-1);
        add(i,T[x].md-1);
        f1[x].clear(),f2[x].clear(),f0[x]=0;
        g[x]=0;
        for(int j=1;j<=T[x].md-1;++j)
        {
            if(d[j]<0) f1[x].push_back(d[j]),g[x]+=d[j];
            else if(d[j]==0) ++f0[x];
            else f2[x].push_back(d[j]);
        }
        reverse(f2[x].begin(),f2[x].end());
    }
    if(b[x]=='0') f2[x].push_back(1);
    else f1[x].push_back(-1),--g[x];
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%s",&n,b+1);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=2;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            a[x].push_back(i);
        }
        dfs0(1);
        dfs(1);
        for(int i=1;i<=n;++i)
        {
            printf("%d ",T[i].s+g[i]);
        }
        printf("\n");
    }
    return 0;
}