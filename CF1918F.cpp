#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
vector<int> a[N];
int n,k,q,b[N],c[N],d[N];
void dfs0(int x)
{
    c[x]=x;
    for(auto i:a[x])
    {
        d[i]=d[x]+1;
        dfs0(i);
        if(d[c[i]]>d[c[x]]) c[x]=c[i];
    }
}
void dfs(int x,int k)
{
    if(a[x].size()==0)
    {
        b[++q]=k*2-d[x];
        return;
    }
    for(auto i:a[x])
    {
        if(c[i]==c[x]) dfs(i,k+1);
        else dfs(i,1);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    ++k;
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x].push_back(i);
    }
    dfs0(1);
    dfs(1,0);
    sort(b+1,b+q+1,[](int a,int b){return a>b;});
    int s=0;
    for(int i=1;i<=min(k,q);++i)
    {
        s+=max(b[i],0);
    }
    printf("%d\n",(n-1)*2-s);
    return 0;
}