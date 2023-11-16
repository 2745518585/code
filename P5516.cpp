#include<bits/stdc++.h>
using namespace std;
const int N=20001;
int n,g[N];
double f[N],a[N],b[N];
char c[N];
int main()
{
    scanf("%s",c+1);
    n=strlen(c+1);
    for(int i=1;i<=n;++i) ++g[c[i]-'A'+1];
    a[1]=-1,b[1]=(double)n/2;
    for(int i=2;i<=n-1;++i)
    {
        double p=1-(double)(1-i)/(i*2)*a[i-1];
        a[i]=(double)(-1-i)/(i*2)/p;
        b[i]=((double)n*(n-1)/(i*2)/(n-i)-(double)(1-i)/(i*2)*b[i-1])/p;
    }
    for(int i=n-1;i>=1;--i)
    {
        f[i]=b[i]-a[i]*f[i+1];
    }
    double s=0;
    for(int i=1;i<=26;++i)
    {
        s+=(double)f[g[i]]*g[i]/n;
    }
    printf("%.1lf",s);
    return 0;
}