#include<iostream>
#include<cmath>
using namespace std;
long long n;
int len;
int lim;
int lenp;
long long a[7000000];
long long g[7000000];
inline int get_index(long long x)
{
    if(x<=lim)
        return x;
    else
        return len-n/x+1;
}
int main()
{
    cin>>n;
    lim=sqrt(n);
    for(long long i=1;i<=n;i=a[len]+1)
    {
        a[++len]=n/(n/i);
        g[len]=a[len]-1;
    }
    for(int i=2;i<=lim;++i)
    {
        if(g[i]!=g[i-1])
        {
            ++lenp;
            for(int j=len;a[j]>=1ll*i*i;--j)
                g[j]=g[j]-g[get_index(a[j]/i)]+lenp-1;
        }
        
    }
    cout<<g[len];
    return 0;
}