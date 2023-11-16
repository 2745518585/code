#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=200001,M=31;
int n,m,q,a[N],b[N][M],lg[N],pw[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i][0]=a[i];
        lg[i]=log2(i);
    }
    q=log2(n);
    pw[0]=1;
    for(int i=1;i<=q;++i) pw[i]=pw[i-1]*2;
    for(int i=1;i<=q;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(j+pw[i]-1<=n) b[j][i]=max(b[j][i-1],b[j+pw[i-1]][i-1]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",max(b[x][lg[y-x]],b[y-pw[lg[y-x]]+1][lg[y-x]]));
    }
    return 0;
}