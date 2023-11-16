#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100,P=997;
int n,s,q,b[N],jc[N];
int qpow(int a,int b)
{
    int x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void solve()
{
    int w=0;
    for(int i=1;i<=q;++i) w+=b[i]/2;
    for(int i=1;i<=q;++i)
    {
        for(int j=1;j<=i-1;++j) w+=gcd(b[i],b[j]);
    }
    int v=1;
    for(int i=1;i<=q;++i) v=v*b[i]%P;
    for(int i=1;i<=q;++i)
    {
        int j=i;
        while(j+1<=q&&b[i]==b[j+1]) ++j;
        v=v*jc[j-i+1]%P;
        i=j;
    }
    s=(s+qpow(2,w)*qpow(v,P-2)%P)%P;
}
void dfs(int x)
{
    if(x==n+1)
    {
        if(b[q]>=b[q-1]) solve();
        return;
    }
    if(x==1||b[q]>=b[q-1])
    {
        b[++q]=1;
        dfs(x+1);
        --q;
    }
    if(x>1)
    {
        ++b[q];
        dfs(x+1);
        --b[q];
    }
}
int main()
{
    scanf("%d",&n);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    dfs(1);
    printf("%d",s); 
    return 0;
}