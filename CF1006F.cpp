#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=21,M=200001;
int m,n,q1[N],q2[N];
ll k,a[N][N],b1[N][M],b2[N][M],s;
void dfs1(int x,int y,ll w)
{
    w^=a[x][y];
    if(x+y==m+1)
    {
        b1[x][++q1[x]]=w;
        return;
    }
    if(x<m) dfs1(x+1,y,w);
    if(y<n) dfs1(x,y+1,w);
}
void dfs2(int x,int y,ll w)
{
    if(x+y==m+1)
    {
        b2[x][++q2[x]]=w;
        return;
    }
    w^=a[x][y];
    if(x>1) dfs2(x-1,y,w);
    if(y>1) dfs2(x,y-1,w);
}
void check(ll b1[],ll b2[],int q1,int q2)
{
    for(int i=1;i<=q1;++i) b1[i]^=k;
    sort(b1+1,b1+q1+1);
    sort(b2+1,b2+q2+1);
    int x=1;
    ll q=0;
    for(int i=1;i<=q1;++i)
    {
        if(i>1&&b1[i]==b1[i-1])
        {
            s+=q;
            continue;
        }
        q=0;
        while(x<=q2&&b2[x]<b1[i]) ++x;  
        while(x<=q2&&b2[x]==b1[i]) ++x,++q;
        s+=q;
    }
}
int main()
{
    scanf("%d%d%lld",&m,&n,&k);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lld",&a[i][j]);
        }
    }
    dfs1(1,1,0);
    dfs2(m,n,0);
    for(int i=1;i<=m;++i) check(b1[i],b2[i],q1[i],q2[i]);
    printf("%lld",s);
    return 0;
}