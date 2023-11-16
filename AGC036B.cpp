#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,t,a[N],b[N],c[N],S[N];
ll k,g[N];
bool h[N];
int main()
{
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) a[n+i]=a[i];
    for(int i=n*2;i>=1;--i)
    {
        b[i]=c[a[i]]-i+1;
        c[a[i]]=i;
    }
    ll q=0;
    while(true)
    {
        if(q+b[q%n+1]>k*n) break;
        if(g[q%n+1]!=0)
        {
            q+=(k*n-q)/(q-g[q%n+1])*(q-g[q%n+1]);
            break;
        }
        g[q%n+1]=q;
        q+=b[q%n+1];
    }
    while(true)
    {
        if(q+b[q%n+1]>k*n) break;
        q+=b[q%n+1];
    }
    while(q<k*n)
    {
        if(h[a[q%n+1]])
        {
            while(S[t]!=a[q%n+1]) h[S[t]]=false,--t;
            --t;
            h[a[q%n+1]]=false;
        }
        else
        {
            S[++t]=a[q%n+1];
            h[a[q%n+1]]=true;
        }
        ++q;
    }
    for(int i=1;i<=t;++i)
    {
        printf("%d ",S[i]);
    }
    return 0;
}