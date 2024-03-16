#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20000001;
int n,m,f[N];
char a[N],b[N];
int KMP(int n,char *x)
{
    f[1]=0;
    for(int i=2,j=0;i<=n;++i)
    {
        while(j!=0&&x[i]!=x[j+1]) j=f[j];
        if(x[i]==x[j+1]) ++j;
        f[i]=j;
    }
    if(n%(n-f[n])==0) return n-f[n];
    else return n;
}
int main()
{
    scanf("%d%d%s%s",&n,&m,a+1,b+1);
    int l=0;
    while(a[l+1]==b[l+1]&&l<n) ++l;
    int r=0;
    while(a[n-r]==b[m-r]&&r<n) ++r;
    if(l+r<n)
    {
        printf("0");
        return 0;
    }
    int p=l+r-n;
    l-=p,r-=p;
    int v=KMP(m-n,b+(n-r));
    ll s=0;
    for(int i=v;i<=p;i+=v)
    {
        if((m-l-r-p)%i!=0) continue;
        s+=p-i+1;
    }
    printf("%lld",s);
    return 0;
}