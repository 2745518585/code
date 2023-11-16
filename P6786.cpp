#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=300001,M=10000001;
int n,a[N];
ll f[N],s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    int x=1;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==a[i+1])
        {
            ++x;
            continue;
        }
        f[i]=(ll)a[i]*x;
        int z=lower_bound(a+1,a+n+1,a[i]/3*2)-a;
        if(a[i]%3==0&&a[z]==a[i]/3*2) f[i]+=f[z];
        f[i-x+1]=f[i];
        s=max(s,f[i]);
        x=1;
    }
    printf("%lld",s);
    return 0;
}