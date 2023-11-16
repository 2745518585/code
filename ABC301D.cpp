#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll k,s;
char a[N];
int main()
{
    scanf("%s%lld",a+1,&k);
    n=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        if(a[i]!='?') s+=(1ll<<(n-i))*(a[i]-'0');
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='?')
        {
            if(s+(1ll<<(n-i))<=k) s+=(1ll<<(n-i));
        }
    }
    if(s>k) printf("-1");
    else printf("%lld",s);
    return 0;
}