#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
const int N=200001,M=500,K=3;
int n,m,q,a[N],b1[N],b2[N],g1[N],g2[N],T,S1[N],T1,S2[N],T2;
bool h[M];
ll f1[M][M],f2[M][M],f3[M],f4[M],powb[N];
struct str
{
    int g;
    ll *f;
    str(){}
    str(int g,ll *f):g(g),f(f){}
}S[N];
bool solve(int l,int r)
{
    T1=T2=0;
    for(int i=l;i<=r;++i)
    {
        if(a[i]>0) S2[++T2]=a[i];
        else
        {
            if(T2==0) S1[++T1]=-a[i];
            else if(S2[T2]!=-a[i]) return false;
            else --T2;
        }
    }
    return true;
}
void build(int x)
{
    h[x]=true;
    if(solve(b1[x-1]+1,b1[x])==false)
    {
        h[x]=false;
        return;
    }
    g1[x]=T1,g2[x]=T2;
    for(int i=1;i<=T1;++i)
    {
        f1[x][i]=(f1[x][i-1]*K+S1[T1-i+1])%P;
    }
    for(int i=1;i<=T2;++i)
    {
        f2[x][i]=(f2[x][i-1]*K+S2[i])%P;
    }
}
bool check(int x,ll *f)
{
    while(x>0&&T>0)
    {
        int z=min(S[T].g,x);
        if(((S[T].f[S[T].g]-S[T].f[S[T].g-z]*powb[z]%P)%P+P)%P!=((f[x]-f[x-z]*powb[z]%P)%P+P)%P) return false;
        S[T].g-=z;
        x-=z;
        if(S[T].g==0) --T;
    }
    if(T==0&&x!=0) return false;
    return true;
}
bool query(int l,int r)
{
    if(b2[l]==b2[r])
    {
        if(solve(l,r)==false) return false;
        if(T1!=0||T2!=0) return false;
        return true;
    }
    T=0;
    if(solve(l,b1[b2[l]])==false) return false;
    if(T1!=0) return false;
    for(int i=1;i<=T2;++i) f3[i]=(f3[i-1]*K+S2[i])%P;
    if(T2!=0) S[++T]=str(T2,f3);
    for(int i=b2[l]+1;i<=b2[r]-1;++i)
    {
        if(h[i]==false) return false;
        if(check(g1[i],f1[i])==false) return false;
        if(g2[i]!=0) S[++T]=str(g2[i],f2[i]);
    }
    if(solve(b1[b2[r]-1]+1,r)==false) return false;
    for(int i=1;i<=T1;++i) f4[i]=(f4[i-1]*K+S1[T1-i+1])%P;
    if(check(T1,f4)==false) return false;
    while(T>=1&&S[T].g==0) --T;
    if(T2!=0||T!=0) return false;
    return true;
}
int main()
{
    scanf("%d%*d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    powb[0]=1;
    for(int i=1;i<=n;++i) powb[i]=powb[i-1]*K%P;
    q=sqrt(n);
    for(int i=1;i<=q;++i) b1[i]=(n/q)*i;
    b1[q]=n;
    for(int i=1;i<=q;++i)
    {
        for(int j=b1[i-1]+1;j<=b1[i];++j) b2[j]=i;
    }
    for(int i=1;i<=q;++i) build(i);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            a[x]=k;
            build(b2[x]);
        }
        else if(z==2)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            if(query(l,r)) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}