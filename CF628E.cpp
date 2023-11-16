#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=5001;
int n,m,b1[N][N],b2[N][N];
ll s,T[N];
char a[N][N];
vector<int> d[N];
void add(int x,int k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&-x);
        T[x]+=k;
    }
}
ll sum(int x)
{
    ll s=T[x];
    while(x>=1)
    {
        x-=(x&-x);
        s+=T[x];
    }
    return s;
}
void solve(int x,int y,int k)
{
    add(y,1);
    if(y+b2[x][y]<=k) d[y+b2[x][y]].push_back(y);
    else d[k+1].push_back(y);
    for(int i=0;i<d[y].size();++i) add(d[y][i],-1);
    s+=sum(y)-sum(y-b1[x][y]);
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]=='z') b1[i][j]=b1[i][j-1]+1;
            else b1[i][j]=0;
        }
        for(int j=n;j>=1;--j)
        {
            if(a[i][j]=='z') b2[i][j]=b2[i][j+1]+1;
            else b2[i][j]=0;
        }
    }
    for(int i=2;i<=m+n;++i)
    {
        for(int j=1;j<=n+1;++j) T[j]=0,d[j].clear();
        for(int j=max(i-m,1);j<=min(i-1,n);++j)
        {
            if(a[i-j][j]=='.') continue;
            int k=j;
            while(k+1<=min(i-1,n)&&a[i-(k+1)][k+1]=='z') ++k;
            for(int l=j;l<=k;++l) solve(i-l,l,k);
            for(int l=0;l<d[k+1].size();++l) add(d[k+1][l],-1);
            j=k;
        }
    }
    printf("%lld",s);
    return 0;
}