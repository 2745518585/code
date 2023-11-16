#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll k;
char a[N];
int main()
{
    scanf("%d%lld%s",&n,&k,a+1);
    k+=(1ll<<(a[n-1]-'a'))-(1ll<<(a[n]-'a'));
    sort(a+1,a+n-1);
    for(int i=n-2;i>=1;--i)
    {
        if(k<=0) k+=(1ll<<(a[i]-'a'));
        else k-=(1ll<<(a[i]-'a'));
    }
    if(k==0) printf("Yes\n");
    else printf("No\n");
    return 0;
}