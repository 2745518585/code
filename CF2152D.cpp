#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],f[N],g[N];
int lg(int x)
{
    int s=0;
    while(x>1) x>>=1,++s;
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            f[i]=f[i-1]+lg(a[i]);
            g[i]=g[i-1];
            if(a[i]-(1<<lg(a[i]))>1) g[i]+=2;
            else if(a[i]-(1<<lg(a[i]))==1) ++g[i];
        }
        for(int i=1;i<=m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",(f[r]-f[l-1])+(g[r]-g[l-1])/2);
        }
    }
    return 0;
}