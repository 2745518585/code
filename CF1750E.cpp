#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,S[N],T;
ll T1[N],T2[N],T3[N],T4[N];
char a[N];
void add(ll *T,int x,ll k)
{
    while(x<=n*2) T[x]+=k,x+=x&-x;
}
ll sum(ll *T,int x)
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
        scanf("%d%s",&n,a+1);
        for(int i=1;i<=n*2+1;++i) T1[i]=T2[i]=T3[i]=T4[i]=0;
        ll s=0;
        int w1=0,w2=0;
        add(T1,n+1,1);
        add(T2,n+1,0);
        add(T3,n+1,1);
        add(T4,n+1,0);
        for(int i=1;i<=n;++i)
        {
            if(a[i]=='(') ++w1;
            else ++w2;
            s+=(w1*sum(T1,w1-w2+n+1)-sum(T2,w1-w2+n+1));
            s+=(w2*(sum(T3,n*2)-sum(T3,w1-w2+n+1))-(sum(T4,n*2)-sum(T4,w1-w2+n+1)));
            add(T1,w1-w2+n+1,1);
            add(T2,w1-w2+n+1,w1);
            add(T3,w1-w2+n+1,1);
            add(T4,w1-w2+n+1,w2);
        }
        S[T=0]=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]=='(') S[++T]=i;
            else
            {
                if(T>=1)
                {
                    s-=(ll)S[T]*(n-i+1);
                    --T;
                }
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}