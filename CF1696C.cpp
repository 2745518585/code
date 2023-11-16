#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,m,k;
struct str
{
    int x;
    ll w;
}a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int t;
        n=m=0;
        scanf("%d%d",&t,&k);
        for(int i=1;i<=t;++i)
        {
            int x;
            scanf("%d",&x);
            ll w=1;
            while(x%k==0) x/=k,w*=k;
            if(n>=1&&a[n].x==x) a[n].w+=w;
            else a[++n]=(str){x,w};
        }
        scanf("%d",&t);
        for(int i=1;i<=t;++i)
        {
            int x;
            scanf("%d",&x);
            ll w=1;
            while(x%k==0) x/=k,w*=k;
            if(m>=1&&b[m].x==x) b[m].w+=w;
            else b[++m]=(str){x,w};
        }
        if(m!=n)
        {
            printf("No\n");
            continue;
        }
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(a[i].x!=b[i].x||a[i].w!=b[i].w)
            {
                u=false;
                break;
            }
        }
        if(u) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}