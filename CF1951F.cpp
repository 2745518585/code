#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N];
ll k,T[N];
void add(int x,ll k)
{
    while(x<=n) T[x]+=k,x+=x&-x;
}
ll sum(int x)
{
    ll s=0;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%lld",&n,&k);
        k=n*(n-1)-k;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i) T[i]=0;
        ll w=0;
        for(int i=1;i<=n;++i)
        {
            w+=sum(n)-sum(a[i]);
            add(a[i],1);
        }
        if(k<w||k>(ll)n*(n-1)-w||k%2!=w%2)
        {
            printf("NO\n");
            continue;
        }
        k-=w;
        for(int i=1;i<=n;++i) T[i]=0;
        int x=0;
        for(int i=1;i<=n;++i)
        {
            ll z=sum(a[i]-1);
            if(z*2<k) k-=z*2;
            else
            {
                x=i;
                break;
            }
            add(a[i],1);
        }
        int p=1;
        while(k>0)
        {
            if(a[p]<a[x]) k-=2;
            ++p;
        }
        printf("YES\n");
        for(int i=1;i<=p-1;++i)
        {
            printf("%d ",i+(n-x));
        }
        for(int i=p;i<=x-1;++i)
        {
            printf("%d ",i+(n-x)+1);
        }
        printf("%d ",p+(n-x));
        for(int i=x+1;i<=n;++i)
        {
            printf("%d ",(n+1)-i);
        }
        printf("\n");
    }
    return 0;
}