#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=300001,M=301;
int n,m,b[N],c[N];
ll f[N][M],d[N];
struct str
{
    int l,r,k,t;
    str(){}
    str(int l,int r,int k,int t):l(l),r(r),k(k),t(t){}
};
void solve(vector<str> a,int l,int r)
{
    if(l>r) return;
    if(l==r)
    {
        for(auto i:a)
        {
            if(i.k>=b[l]) d[i.t]=c[l];
            else d[i.t]=0;
        }
        return;
    }
    int z=l+r>>1;
    for(int i=0;i<=200;++i) f[z][i]=(i>=b[z]?c[z]:0);
    for(int i=z-1;i>=l;--i)
    {
        for(int j=200;j>=0;--j)
        {
            f[i][j]=f[i+1][j];
            if(j>=b[i]) f[i][j]=max(f[i][j],f[i+1][j-b[i]]+c[i]);
        }
    }
    for(int i=0;i<=200;++i) f[z+1][i]=(i>=b[z+1]?c[z+1]:0);
    for(int i=z+2;i<=r;++i)
    {
        for(int j=200;j>=0;--j)
        {
            f[i][j]=f[i-1][j];
            if(j>=b[i]) f[i][j]=max(f[i][j],f[i-1][j-b[i]]+c[i]);
        }
    }
    vector<str> a1,a2;
    for(auto i:a)
    {
        if(i.r<=z) a1.push_back(i);
        else if(i.l>=z+1) a2.push_back(i);
        else
        {
            for(int j=0;j<=i.k;++j) d[i.t]=max(d[i.t],f[i.l][j]+f[i.r][i.k-j]);
        }
    }
    a.clear();
    solve(a1,l,z);
    solve(a2,z+1,r);
    a1.clear();
    a2.clear();
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
    }
    vector<str> a;
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        a.push_back(str(x,y,k,i));
    }
    solve(a,1,n);
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",d[i]);
    }
    return 0;
}