#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,a[N],S[N],T,b[N][2];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        int z=T;
        while(T>0&&a[S[T]]>a[i]) --T;
        if(T!=0) b[S[T]][1]=i;
        if(T<z) b[i][0]=S[T+1];
        S[++T]=i;
    }
    ll s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        s1^=(ll)i*(b[i][0]+1);
        s2^=(ll)i*(b[i][1]+1);
    }
    printf("%lld %lld",s1,s2);
    return 0;
}