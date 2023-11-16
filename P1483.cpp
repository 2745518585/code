#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n,m,a[N],b[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            b[x]+=k;
        }
        else
        {
            int x;
            scanf("%d",&x);
            int p=sqrt(x),s=0;
            for(int i=1;i<=p;++i)
            {
                if(x%i==0)
                {
                    s+=b[i];
                    if(x/i!=i) s+=b[x/i];
                }
            }
            printf("%d\n",a[x]+s);
        }
    }
    return 0;
}