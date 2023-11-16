#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,a[N][3],fa[N],g[N];
ll b[N],jc[N];
bool h[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
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
    scanf("%d",&n);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    for(int i=1;i<=n;++i) fa[i]=i,g[i]=1;
    int w[3]={0,n,0};
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x=find(x),y=find(y);
        if(x!=y)
        {
            --w[g[y]%3],--w[g[x]%3];
            g[y]+=g[x];
            ++w[g[y]%3];
            fa[x]=y;
        }
        else
        {
            if(g[x]%3!=0) h[i]=true;
            else --w[0];
        }
        a[i][0]=w[0],a[i][1]=w[1],a[i][2]=w[2];
        h[i]|=h[i-1];
    }
    ll w1=1,w2=1;
    int x=0,y=0;
    auto check1=[&]()
    {
        w1=(w2-(ll)(x+1)*(x+y+1)%P*w1%P)*inv(y)%P;
        w2=((x+2)*w2%P+(ll)y*(x+y+2)%P*w1%P)%P;
        x+=2,y-=1;
    };
    auto check2=[&]()
    {
        w1=(w2-(ll)(y+1)*(y+x+1)%P*w1%P)*inv(x)%P;
        w2=((y+2)*w2%P+(ll)x*(y+x+2)%P*w1%P)%P;
        y+=2,x-=1;
    };
    b[n]=1;
    for(int i=n;i>=1;--i)
    {
        for(int j=1;j<=((a[i][1]-a[i+1][1])*2+(a[i][2]-a[i+1][2]))/3;++j) check1();
        for(int j=1;j<=((a[i][1]-a[i+1][1])+(a[i][2]-a[i+1][2])*2)/3;++j) check2();
        // printf("%d | %d %d %d | %d %d | %lld %lld\n",i,a[i][0],a[i][1],a[i][2],x,y,w1,w2);
        b[i]=w1*jc[a[i][0]+a[i][1]+a[i][2]]%P*inv(jc[a[i][1]+a[i][2]])%P;
    }
    for(int i=1;i<=n;++i)
    {
        if(h[i]) printf("0\n");
        else printf("%lld\n",(b[i]%P+P)%P);
    }
    return 0;
}