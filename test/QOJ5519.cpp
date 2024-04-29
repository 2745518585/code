#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=998244353;
int n;
char a[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        ll s=1;
        int w1=0,w2=0,p1=0,p2=0;
        for(int i=1;i<=n*2-1;++i)
        {
            if(a[i]=='W')
            {
                int z=max(min(min(w2,2),w1+w2-1),0);
                if(z==1) s=s*w2*2%P;
                else if(z==2) s=s*(w2*(w2-2)%P)%P;
                w2-=z,w1+=2-z;
            }
            else if(a[i]=='B')
            {
                int z=max(min(min(w1,2),w1+w2-1),0);
                if(z==1) s=s*w1*2%P;
                else if(z==2) s=s*(w1*(w1-2)%P)%P;
                w1-=z,w2+=2-z;
            }
            s=s*inv(2)%P;
        }
        printf("%lld\n",s);
    }
    return 0;
}