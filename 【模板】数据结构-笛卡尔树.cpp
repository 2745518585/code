#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,a[N],S[N],t;
struct tree
{
    int l,r;
}T[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        S[t+1]=0;
        while(t>0&&a[S[t]]>a[i]) --t;
        if(t>0) T[S[t]].r=i;
        T[i].l=S[t+1];
        S[++t]=i;
    }
    ll s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        s1^=(ll)i*(T[i].l+1);
        s2^=(ll)i*(T[i].r+1);
    }
    printf("%lld %lld",s1,s2);
    return 0;
}