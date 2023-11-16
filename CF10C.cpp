#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll s,h[10],n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) ++h[i%9];
    for(int i=0;i<=8;++i)
    {
        for(int j=0;j<=8;++j)
        {
            for(int k=0;k<=8;++k)
            {
                if(i*j%9==k%9) s+=h[i]*h[j]*h[k];   
            }
        }
    }
    for (ll i=1,j;i<=n;i=j+1)
    {
        j=min(n,n/(n/i));
        s-=(n/i)*(j-i+1);
    }
    printf("%lld",s);
    return 0;
}