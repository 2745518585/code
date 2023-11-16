#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=101;
const ll P=1e9+7;
int m,a[N]={0,2,3,5,7,11,13,17,19,23,29},f[N];
ll s;
bool g[N],h[N];
vector<int> b[N];
bool check(int x)
{
    for(auto i:b[x])
    {
        if(h[i]) return false;
    }
    return true;
}
void dfs(int x,ll w)
{
    if(w==0) return;
    if(x==31)
    {
        s=(s+w)%P;
        return;
    }
    if(check(x))
    {
        for(auto i:b[x]) h[i]=true;
        g[x]=true;
        dfs(x+1,w*f[x]%P);
        g[x]=false;
        for(auto i:b[x]) h[i]=false;
    }
    dfs(x+1,w);
}
int main()
{
    int x;
    while(scanf("%d",&x)!=EOF) ++f[x];
    for(int i=1;i<=10;++i)
    {
        for(int j=1;a[i]*a[i]*j<=30;++j) f[a[i]*a[i]*j]=0;
    }
    for(int i=1;i<=10;++i)
    {
        for(int j=1;a[i]*j<=30;++j) b[a[i]*j].push_back(i);
    }
    dfs(1,1);
    printf("%lld",s-f[1]-1);
    return 0;
}