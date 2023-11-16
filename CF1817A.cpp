#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N],f[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=2;i<=n-1;++i)
    {
        if(a[i-1]>=a[i]&&a[i]>=a[i+1]) ++f[i];
    }
    for(int i=1;i<=n;++i) f[i]+=f[i-1];
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",(y-x+1)-max(f[y-1]-f[x],0));
    }
    return 0;
}