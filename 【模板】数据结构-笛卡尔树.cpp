#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,a[N],S[N],T;
struct tree
{
    int l,r;
}b[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        S[T+1]=0;
        while(T>0&&a[S[T]]>a[i]) --T;
        if(T>0) b[S[T]].r=i;
        b[i].l=S[T+1];
        S[++T]=i;
    }
    ll s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        s1^=(ll)i*(b[i].l+1);
        s2^=(ll)i*(b[i].r+1);
    }
    printf("%lld %lld",s1,s2);
    return 0;
}