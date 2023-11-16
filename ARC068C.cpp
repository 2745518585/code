#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,f[N];
void solve()
{
    int x,y;
    scanf("%d%d",&x,&y);
    for(int i=1;i<=min(x-1,y);++i)
    {
        int j=min((x-1)/((x-1)/i),y/(y/i));
        if((x-1)/i<y/i) ++f[i],--f[j+1];
        i=j;
    }
    ++f[x];
    --f[y+1];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) solve();
    for(int i=1;i<=m;++i) f[i]+=f[i-1];
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",f[i]);
    }
    return 0;
}