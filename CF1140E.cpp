#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,a[N],b[N];
ll s=1,f[N][2];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(a[i]!=-1&&a[i]==a[i-2])
        {
            printf("0");
            return 0;
        }
    }
    for(int i=n;i>=1;--i)
    {
        if(a[i]!=-1) b[i]=a[i];
        else b[i]=b[i+2];
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]!=-1) continue;
        if(a[i-2]==-1)
        {
            f[i][0]=(f[i-2][0]*(m-2)%P+f[i-2][1]*(m-1))%P;
            f[i][1]=f[i-2][0];
        }
        else
        {
            if(a[i-2]==0) f[i][0]=m-1,f[i][1]=1;
            else if(a[i-2]==b[i]) f[i][0]=m-1,f[i][1]=0;
            else f[i][0]=m-2,f[i][1]=1;
        }
        if(a[i+2]!=-1)
        {
            if(b[i]==0) s=s*(f[i][0]+f[i][1])%P;
            else s=s*f[i][0]%P;
        }
    }
    printf("%lld",s);
    return 0;
}