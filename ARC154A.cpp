#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n;
char a[N],b[N];
int main()
{
    scanf("%d%s%s",&n,a+1,b+1);
    ll s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        s1=(s1*10+min(a[i],b[i])-'0')%P;
        s2=(s2*10+max(a[i],b[i])-'0')%P;
    }
    printf("%lld",s1*s2%P);
    return 0;
}