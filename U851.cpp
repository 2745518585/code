#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int n,m,s;
ll pow3[N],powb[N];
struct tree
{
    int x,l,r,s;
    ll h1,h2,h3,h4;
}T[N];
void dfs(int x)
{
    if(x==0) return;
    T[x].s=1;
    dfs(T[x].l);
    T[x].s+=T[T[x].l].s;
    dfs(T[x].r);
    T[x].s+=T[T[x].r].s;
    T[x].h1=((((T[x].l!=0)*pow3[T[T[x].l].s*2]+T[T[x].l].h1)*pow3[T[T[x].r].s*2]%P+T[T[x].r].h1)*pow3[1]+(T[x].r!=0)*2)%P;
    T[x].h2=((((T[x].r!=0)*pow3[T[T[x].r].s*2]+T[T[x].r].h2)*pow3[T[T[x].l].s*2]%P+T[T[x].l].h2)*pow3[1]+(T[x].l!=0)*2)%P;
    T[x].h3=((T[T[x].l].h3*powb[1]%P+T[x].x)*powb[T[T[x].r].s]%P+T[T[x].r].h3)%P;
    T[x].h4=((T[T[x].r].h4*powb[1]%P+T[x].x)*powb[T[T[x].l].s]%P+T[T[x].l].h4)%P;
    if(T[x].h1==T[x].h2&&T[x].h3==T[x].h4) s=max(s,T[x].s);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&T[i].x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&T[i].l,&T[i].r);
        if(T[i].l==-1) T[i].l=0;
        if(T[i].r==-1) T[i].r=0;
    }
    powb[0]=1;
    for(int i=1;i<=n;++i) powb[i]=powb[i-1]*1000%P;
    pow3[0]=1;
    for(int i=1;i<=n;++i) pow3[i]=pow3[i-1]*3%P;
    dfs(1);
    printf("%d",s);
    return 0;
}