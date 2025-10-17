#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
const int N=1000001;
int n,pl[N],pr[N];
bool h[N];
ll a[N],b[N];
struct str
{
    int x;
    lll w;
    str() {}
    str(int x,lll w):x(x),w(w) {}
    friend bool operator<(str a,str b)
    {
        return a.w<b.w;
    }
};
lll check(int x,int y)
{
    return (lll)a[x]*b[y]+(lll)a[y]*b[x]-(lll)a[y]*b[y];
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            while(i>1&&a[i]<=a[i-1]) a[i-1]=a[i],--n,--i;
        }
        for(int i=1;i<=n;++i)
        {
            b[i]=a[i];
            pl[i]=i-1,pr[i]=i+1;
            h[i]=true;
        }
        pr[0]=1,pl[n+1]=n;
        // for(int i=1;i<=n;++i) printf("%lld ",a[i]);printf("\n");
        priority_queue<str> Q;
        for(int i=2;i<=n;++i)
        {
            Q.push(str(i,check(i-1,i)));
        }
        while(!Q.empty())
        {
            int k=Q.top().x;
            Q.pop();
            if(!h[k]||pl[k]==0||check(pl[k],k)<0) continue;
            a[k]=min(a[k],a[pl[k]]);
            h[pl[k]]=false;
            pl[k]=pl[pl[k]],pr[pl[k]]=k;
            if(pl[k]!=0) Q.push(str(k,check(pl[k],k)));
            if(pr[k]!=n+1) Q.push(str(k,check(k,pr[k])));
        }
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            if(h[i])
            {
                s+=(b[i]-1)/a[i]+1;
                // printf("%lld %lld\n",a[i],b[i]);
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}