#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=101;
int n,t,a[N][N],b[N][N];
ll s=0,k,c[N],d[N];
bool h[N];
bool cmp(int x,int y)
{
    return a[t][x]>a[t][y];
}
void dfs(int x,ll w,ll k)
{
    if(w+d[x]<=s||w+k<=s) return;
    if(x==n+1)
    {
        s=max(s,w);
        return;
    }
    for(int i=1;b[x][i]!=0;++i)
    {
        if(!h[b[x][i]])
        {
            h[b[x][i]]=true;
            dfs(x+1,w+a[x][b[x][i]],k-c[b[x][i]]);
            h[b[x][i]]=false;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&n);
    for(int i=1;i<=n*n;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        a[x][y]=w;
        c[y]=max(c[y],w);
        d[x]=max(d[x],w);
    }
    for(int i=1;i<=n;++i) k+=c[i];
    for(int i=n;i>=1;--i) d[i]+=d[i+1];
    for(int i=1;i<=n;++i)
    {
        t=i;
        for(int j=1;j<=n;++j) if(a[i][j]!=0) b[i][j]=j;
        sort(b[i]+1,b[i]+n+1,cmp);
    }
    dfs(1,0,k);
    printf("%d %lld",n,s);
    return 0;
}