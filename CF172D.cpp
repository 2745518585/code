#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=20000001;
int a,n,h[N];
ll s;
int main()
{
    scanf("%d%d",&a,&n);
    for(int i=1;i*i<=a+n-1;++i)
    {
        for(int j=1;i*i*j<=a+n-1;++j) h[i*i*j]=i*i;
    }
    for(int i=a;i<=a+n-1;++i)
    {
        s+=i/h[i];
    }
    printf("%lld",s);
    return 0;
}