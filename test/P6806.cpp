#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
const ll P=1e9+7;
int n,m,q;
ll f[N][N],g[N][N],h[N][N];
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
ll C(ll a,ll b)
{
    ll s=1;
    for(ll i=1;i<=b;++i) s=s*i%P;
    s=inv(s);
    for(ll i=a-b+1;i<=a;++i) s=s*i%P;
    return s;
}
void mul()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) h[i][j]=0;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(g[i][j]==0) continue;
            for(int k=1;k<=n;++k)
            {
                h[i][k]=(h[i][k]+g[i][j]*f[j][k]%P)%P;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=h[i][j];
    }
}
void sqr()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) h[i][j]=0;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            h[1][i]=(h[1][i]+f[1][j]*f[j][i]%P)%P;
        }
        h[i][1]=h[1][i];
    }
    for(int i=2;i<=n;++i)
    {
        for(int j=2;j<=n;++j)
        {
            if(i+j-1<=n) h[i][j]=(h[i-1][j-1]+h[1][i+j-1])%P;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i+j-1>n) h[i][j]=h[n-i+1][n-j+1];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=h[i][j];
    }
}
void solve(int m)
{
    if(m==1) return;
    solve(m/2);
    sqr();
    if(m%2==1) mul();
}
int main()
{
    scanf("%d%d%d",&m,&n,&q);
    for(int i=1;i<=n;++i)
    {
        f[i][i]=g[i][i]=1;
        if(i>1) f[i][i-1]=g[i][i-1]=1;
        if(i<n) f[i][i+1]=g[i][i+1]=1;
    }
    solve(m-1);
    for(int i=1;i<=q;++i)
    {
        char z;
        int x,y;
        scanf("%s%d%d",&z,&x,&y);
        if(z=='P')
        {
            if(x==y) printf("%d %d\n",m-1,1);
            else printf("%d %d\n",0,0);
        }
        else if(z=='R')
        {
            if(x==y) printf("%d %d\n",1,1);
            else printf("%d %d\n",2,2);
        }
        else if(z=='B')
        {
            if((x+1)%2!=(y+m)%2) printf("%d %d\n",0,0);
            else if(abs(x-y)==m-1) printf("%d %d\n",1,1);
            else
            {
                int w1=0,w2=0,t1=0,t2=0;
                {
                    t1=((m-1)-(x-1))%((n-1)*2);
                    w1=((m-1)-(x-1))/((n-1)*2)*2+1;
                    if(t1==0) t1+=(n-1)*2,w1-=2;
                    while(true)
                    {
                        ++w1;
                        if(t1<=y-1) {t1-=(y-1);break;}
                        t1-=(n-1);
                        ++w1;
                        if(t1<=n-y) {t1-=(n-y);break;}
                        t1-=(n-1);
                    }
                }
                {
                    t2=((m-1)-(n-x))%((n-1)*2);
                    w2=((m-1)-(n-x))/((n-1)*2)*2+1;
                    if(t2==0) t2+=(n-1)*2,w2-=2;
                    while(true)
                    {
                        ++w2;
                        if(t2<=n-y) {t2-=(n-y);break;}
                        t2-=(n-1);
                        ++w2;
                        if(t2<=y-1) {t2-=(y-1);break;}
                        t2-=(n-1);
                    }
                }
                t1=(-t1)/2,t2=(-t2)/2;
                ll s=0;
                if(w1<=w2)
                {
                    s=(s+C(t1+w1-2,t1))%P;
                }
                if(w2<=w1)
                {
                    s=(s+C(t2+w2-2,t2))%P;
                }
                printf("%d %lld\n",min(w1,w2),s);
            }
        }
        else if(z=='Q')
        {
            if(x==y||abs(x-y)==m-1) printf("%d %d\n",1,1);
            else
            {
                int s=4;
                if((x+1)%2==(y+n)%2)
                {
                    if(min(x,y)-((m-1)-abs(x-y))/2>=1) ++s;
                    if(max(x,y)+((m-1)-abs(x-y))/2<=n) ++s;
                }
                if(n==m&&(x==1||x==m)) ++s;
                if(n==m&&(y==1||y==m)) ++s;
                printf("%d %d\n",2,s);
            }
        }
        else if(z=='K')
        {
            printf("%d %lld\n",m-1,f[x][y]);
        }
    }
    return 0;
}