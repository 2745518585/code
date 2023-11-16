#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001,M=31;
int n,m,a1[N],a2[N],lg[N];
ll c[N];
struct str
{
    int a,b,t;
}a[N];
struct num
{
    int x1,x2;
    num() {}
    num(int x1,int x2):x1(x1),x2(x2) {}
    friend num max(num a,num b)
    {
        if(a2[a.x1]<a2[b.x1]) swap(a,b);
        if(a2[b.x1]>a2[a.x2]&&b.x1!=a.x1) a.x2=b.x1;
        else if(a2[b.x2]>a2[a.x2]&&b.x2!=a.x1) a.x2=b.x2;
        return a;
    }
}b[N][M];
void init()
{
    for(int i=1;i<=20;++i)
    {
        for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
    }
    for(int i=1;i<=n;++i) b[i][0]=num(i,0);
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(j+(1<<i)-1<=n) b[j][i]=max(b[j][i-1],b[j+(1<<(i-1))][i-1]);
        }
    }
}
num sum(int x,int y)
{
    return max(b[x][lg[y-x]],b[y-(1<<lg[y-x])+1][lg[y-x]]);
}
bool cmp(str a,str b)
{
    return a.a<b.a;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        m=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i].b);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i].a);
            m=max(m,a[i].a);
            a[i].t=i;
        }
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=n;++i) a1[i]=a[i].a,a2[i]=a[i].b;
        init();
        for(int i=1;i<=n;++i) c[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x=1,p=0;
            ll s1=0,s2=0;
            while(x<=n)
            {
                int y=upper_bound(a1+x,a1+n+1,((a1[x]-1)/i+1)*i)-a1-1;
                auto z=sum(x,y);
                ll z1=(ll)a2[z.x1]*((a1[x]-1)/i+1),z2=(ll)a2[z.x2]*((a1[x]-1)/i+1);
                if(z1>s1)
                {
                    s2=max(s1,z2);
                    s1=z1;
                    p=z.x1;
                }
                else s2=max(s2,z1);
                x=y+1;
            }
            c[a[p].t]=max(c[a[p].t],s1-s2);
            // printf("%d %lld %lld\n",i,s1,s2);
        }
        for(int i=1;i<=n;++i)
        {
            printf("%lld ",c[i]);
        }
        printf("\n");
    }
    return 0;
}