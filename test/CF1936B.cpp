#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b1[N],b2[N];
ll T1[N],T2[N];
char a[N];
void add(ll *T,int x,ll k)
{
    while(x<=n) T[x]+=k,x+=x&-x;
}
ll sum(ll *T,int x)
{
    ll s=0;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        for(int i=0;i<=n+1;++i) T1[i]=T2[i]=0;
        b1[0]=b2[n+1]=0;
        for(int i=1;i<=n;++i)
        {
            b1[i]=b1[i-1];
            if(a[i]=='>')
            {
                ++b1[i];
                add(T1,b1[i],i);
            }
        }
        for(int i=n;i>=1;--i)
        {
            b2[i]=b2[i+1];
            if(a[i]=='<')
            {
                ++b2[i];
                add(T2,b2[i],i);
            }
        }
        for(int i=1;i<=n;++i)
        {
            ll s=0;
            if(a[i]=='<')
            {
                int w=min(b1[i-1],b2[i+1]);
                s+=((sum(T2,b2[i+1])-sum(T2,b2[i+1]-w))-(ll)w*i)*2;
                if(b1[i-1]<=b2[i+1]) s+=i;
                else
                {
                    s+=n-i+1;
                    ++w;
                }
                s+=((ll)w*i-(sum(T1,b1[i-1])-sum(T1,b1[i-1]-w)))*2;
            }
            else
            {
                int w=min(b1[i-1],b2[i+1]);
                s+=((ll)w*i-(sum(T1,b1[i-1])-sum(T1,b1[i-1]-w)))*2;
                if(b1[i-1]<b2[i+1])
                {
                    s+=i;
                    ++w;
                }
                else s+=n-i+1;
                s+=((sum(T2,b2[i+1])-sum(T2,b2[i+1]-w))-(ll)w*i)*2;
            }
            printf("%lld ",s);
        }
        printf("\n");
    }
    return 0;
}