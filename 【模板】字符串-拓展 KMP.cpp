#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=20000001;
int m,n,f[N+1],g[N+1];
char a[N+1],b[N+1];
int main()
{
    scanf("%s%s",a+1,b+1);
    m=strlen(a+1),n=strlen(b+1);
    f[1]=0;
    for(int i=2,l=0,r=0;i<=n;++i)
    {
        if(i<=r) f[i]=min(f[i-l+1],r-i+1);
        else f[i]=0;
        while(i+f[i]<=n&&b[f[i]+1]==b[i+f[i]]) ++f[i];
        if(i+f[i]-1>r) l=i,r=i+f[i]-1;
    }
    for(int i=1,l=0,r=0;i<=m;++i)
    {
        if(i<=r) g[i]=min(f[i-l+1],r-i+1);
        else g[i]=0;
        while(i+g[i]<=m&&b[g[i]+1]==a[i+g[i]]) ++g[i];
        if(i+g[i]-1>r) l=i,r=i+g[i]-1;
    }
    ll s1=0,s2=0;
    f[1]=n;
    for(int i=1;i<=n;++i) s1^=(ll)i*(f[i]+1);
    for(int i=1;i<=m;++i) s2^=(ll)i*(g[i]+1);
    printf("%lld\n%lld",s1,s2);
    return 0;
}