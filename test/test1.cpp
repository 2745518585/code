#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,q,b[N];
ll f[N][2];
struct str
{
    int l,r;
}a[N];
bool cmp(str a,str b)
{
    return a.l<b.l;
}
struct sgt
{
    ll T[N];
    void add(int x,ll k)
    {
        while(x<=q) T[x]=(T[x]+k)%P,x+=x&-x;
    }
    ll sum(int x)
    {
        ll s=0;
        while(x>=1) s=(s+T[x])%P,x-=x&-x;
        return s;
    }
}T1,T2;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
        b[++q]=a[i].l,b[++q]=a[i].r;
    }
    sort(b+1,b+q+1);
    q=unique(b+1,b+q+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i].l=lower_bound(b+1,b+q+1,a[i].l)-b;
        a[i].r=lower_bound(b+1,b+q+1,a[i].r)-b;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int z1=lower_bound(b+1,b+q+1,l)-b,z2=lower_bound(b+1,b+q+1,r)-b;
        if(b[z1]!=l||b[z2]!=r)
        {
            printf("0\n");;
            continue;
        }
        l=z1,r=z2;
        for(int j=1;j<=q;++j) T1.T[j]=T2.T[j]=0;
        for(int j=1;j<=n;++j)
        {
            if(a[j].l<l||a[j].r>r) return;
        }
    }
}