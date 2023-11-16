#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2001;
int m,a[11],f[N];
bool h[N];
int main()
{
    scanf("%d%d%d",&a[1],&a[2],&a[3]);
    for(int i=1;i<=1000;++i)
    {
        for(int j=0;j<=1000;++j) h[j]=false;
        for(int j=1;j<=3;++j)
        {
            for(int k=1;k<=i-a[j]+1;++k)
            {
                h[f[k-1]^f[i-(k+a[j]-1)]]=true;
            }
        }
        for(int j=0;j<=1000;++j)
        {
            if(!h[j])
            {
                f[i]=j;
                break;
            }
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",(f[x]==0)+1);
    }
    return 0;
}