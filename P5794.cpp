#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=3000001;
int n,m,q,a[N],b[N],d[N],f[N],g[N];
vector<int> c[N];
int main()
{
    scanf("%d%d",&n,&m);
    ++n;
    int x=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
        if(a[i]==0) x=i;
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;++i)
    {
        c[b[i]].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        f[i]=c[a[i]][d[a[i]]];
        ++d[a[i]];
    }
    for(int i=1;i<=n-1;++i)
    {
        x=f[x];
        g[++q]=a[x];
    }
    for(int i=n-1;i>=1;--i)
    {
        printf("%d ",g[i]);
    }
    return 0;
}