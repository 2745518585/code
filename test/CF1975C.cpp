#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
bool check(int x)
{
    for(int i=1;i<=n-1;++i)
    {
        if(a[i]>=x&&a[i+1]>=x) return true;
    }
    for(int i=1;i<=n-2;++i)
    {
        if(a[i]>=x&&a[i+2]>=x) return true;
    }
    return false;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        int l=1,r=1e9;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(check(z)) l=z;
            else r=z-1;
        }
        printf("%d\n",l);
    }
    return 0;
}