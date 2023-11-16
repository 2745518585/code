#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll k;
char a[N];
int main()
{
    scanf("%s%lld",a+1,&k);
    n=strlen(a+1);
    int x=0;
    while(x<n&&a[x+1]==a[n]) ++x;
    if(x==n)
    {
        printf("%lld",n*k/2);
        return 0;
    }
    ll s=0;
    int w=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]!=a[i-1])
        {
            s+=w/2;
            w=1;
        }
        else ++w;
    }
    s+=w/2;
    for(int i=1;i<=n;++i) a[n+i]=a[i];
    for(int i=1;i<=n;++i) a[i]=a[x+i];
    w=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]!=a[i-1])
        {
            s+=(w/2)*(k-1);
            w=1;
        }
        else ++w;
    }
    s+=(w/2)*(k-1);
    printf("%lld",s);
    return 0;
}