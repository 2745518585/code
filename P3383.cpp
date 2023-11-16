#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100000001;
int n,m,t,a[N];
bool h[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i)
    {
        if(h[i]==false) a[++t]=i;
        for(int j=1;j<=t&&i*a[j]<=n;++j)
        {
            h[i*a[j]]=true;
            if(i%a[j]==0) break;
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",a[x]);
    }
    return 0;
}