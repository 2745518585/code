#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,m,a[N],T,R;
ll q,Q[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d",&a[i]);
        q+=a[i];
    }
    for(int i=q;i>=0;--i) Q[++R]=i;
    for(int i=3;i<=n-1;++i)
    {
        for(int j=1;j<=a[i];++j) Q[R+j]=Q[R-j];
        R+=a[i];
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a[n]);
        if(a[n]>=q)
        {
            printf("%lld\n",a[1]*2+a[n]-q);
            continue;
        }
        printf("%lld\n",Q[R-a[n]]+a[1]-a[2]);
    }
    return 0;
}