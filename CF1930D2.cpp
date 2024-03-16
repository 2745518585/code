#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll f[4];
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        ll s=0;
        f[0]=f[1]=f[2]=f[3]=0;
        for(int i=1;i<=n;++i)
        {
            f[0]+=f[1]+1;
            f[1]=f[2];
            f[2]=f[3];
            f[3]=0;
            if(a[i]=='1')
            {
                f[3]=f[0];
                f[0]=0;
                s+=f[3]*(n-i+1);
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}