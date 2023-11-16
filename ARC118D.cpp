#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,n;
ll a,b,P,pow1[N],pow2[N];
bool h[N];
int main()
{
    scanf("%lld%lld%lld",&P,&a,&b);
    pow1[0]=1;
    for(int i=1;i<=P-1;++i) pow1[i]=pow1[i-1]*a%P,h[pow1[i]]=true;
    pow2[0]=1;
    for(int i=1;i<=P-1;++i) pow2[i]=pow2[i-1]*b%P;
    m=1;
    while(pow1[m]!=1) ++m;
    n=1;
    while(!h[pow2[n]]) ++n;
    if(m*n!=P-1)
    {
        printf("No");
        return 0;
    }
    printf("Yes\n");
    for(int i=0;i<n;++i)
    {
        printf("%lld ",(pow2[i]%P+P)%P);
    }
    for(int i=n-1;i>=0;--i)
    {
        if((n-i)%2)
        {
            for(int j=1;j<m;++j) printf("%lld ",(pow1[j]*pow2[i]%P+P)%P);
        }
        else
        {
            for(int j=m-1;j>=1;--j) printf("%lld ",(pow1[j]*pow2[i]%P+P)%P);
        }
    }
    printf("1\n");
    return 0;
}