#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=998244353;
const int N=110001;
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
struct matrix
{
    int m,n;
    ll a[2][2];
    matrix() {}
    matrix(int m,int n):m(m),n(n) {init0();}
    friend matrix operator *(matrix a,matrix b)
    {
        matrix c(a.m,b.n);
        for(int i=0;i<c.n;++i)
        {
            for(int j=0;j<c.n;++j)
            {
                c.a[i][j]=0;
                for(int k=0;k<a.n;++k)
                {
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%P)%P;
                }
            }
        }
        return c;
    }
    void size(int x,int y) {m=x,n=y;}
    void init0(int x=0)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=x;
    }
    void init1()
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=(i==j);
    }
};
int n,q;
ll b[N][2][2],b0[2][2];
struct
{
    ll x,v,p;
}a[N];
struct str
{
    int x,u1,u2;
    ll w1,w2;
    str() {}
    str(int x,int u1,int u2,ll w1,ll w2):x(x),u1(u1),u2(u2),w1(w1),w2(w2) {}
}d[N<<1];
struct tree
{
    int l,r;
    matrix s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s*T[x<<1|1].s;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s.size(2,2);
        T[x].s.a[0][0]=b[l][0][0];
        T[x].s.a[0][1]=b[l][0][1];
        T[x].s.a[1][0]=b[l][1][0];
        T[x].s.a[1][1]=b[l][1][1];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        T[x].s.size(2,2);
        T[x].s.a[0][0]=b[T[x].l][0][0];
        T[x].s.a[0][1]=b[T[x].l][0][1];
        T[x].s.a[1][0]=b[T[x].l][1][0];
        T[x].s.a[1][1]=b[T[x].l][1][1];
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q);
    else add(x<<1|1,q);
    pushup(x);
}
bool cmp(str a,str b)
{
    return a.w1*b.w2<b.w1*a.w2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld%lld",&a[i].x,&a[i].v,&a[i].p);
        a[i].p=a[i].p*inv(100)%P;
        b[i][0][0]=b[i][1][0]=(1-a[i].p+P)%P;
        b[i][0][1]=b[i][1][1]=a[i].p;
        if(i==1) continue;
        for(int j=0;j<=1;++j)
        {
            for(int k=0;k<=1;++k)
            {
                ll x=a[i].x-a[i-1].x,v1=j?a[i-1].v:-a[i-1].v,v2=k?a[i].v:-a[i].v;
                if(v1==v2) continue;
                if(v1-v2>=0) d[++q]=str(i,j,k,x,v1-v2);
            }
        }
    }
    build(1,1,n);
    sort(d+1,d+q+1,cmp);
    matrix R(1,2);
    R.a[0][0]=1,R.a[0][1]=0;
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        // printf("%d %d %d\n",d[i].x,d[i].u1,d[i].u2);
        for(int j=0;j<=1;++j)
        {
            for(int k=0;k<=1;++k)
            {
                b0[j][k]=b[d[i].x][j][k];
                if(j!=d[i].u1||k!=d[i].u2) b[d[i].x][j][k]=0;
            }
        }
        // for(int j=1;j<=n;++j)
        // {
        //     for(int k=0;k<=1;++k)
        //     {
        //         for(int l=0;l<=1;++l)
        //         {
        //             printf("%d ",b[j][k][l]);
        //         }
        //         printf("\n");
        //     }
        //     printf("\n");
        // }
        add(1,d[i].x);
        // build(1,1,n);
        matrix z=R*T[1].s;
        // printf("%lld %lld\n",(z.a[0][0]%P+P)%P,(z.a[0][1]%P+P)%P);
        s=(s+(z.a[0][0]+z.a[0][1])*d[i].w1%P*inv(d[i].w2)%P)%P;
        for(int j=0;j<=1;++j) for(int k=0;k<=1;++k) b[d[i].x][j][k]=b0[j][k];
        b[d[i].x][d[i].u1][d[i].u2]=0;
        add(1,d[i].x);
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}