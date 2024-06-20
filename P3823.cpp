#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T,typename ...O> inline void read(T &x,O &...o) {read(x),read(o...);}
template<typename T> inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
template<typename T,typename ...O> inline void print(T x,O ...o) {print(x),putchar(' '),print(o...);}
const int N=2000001,M=51;
const ll P=998244353;
int n,m,tot=1,a[N<<3][6],c[N],d[N][M],g[N<<3];
char e[N<<3];
struct str
{
    int l,r;
}b[N];
int add(int x,int c)
{
    if(a[x][c]==0) a[x][c]=++tot;
    x=a[x][c];
    return x;
}
void check(int x,int y,int t,int k)
{
    while(t<=50&&y!=0)
    {
        d[x][t]=add(d[x][t-1],c[y]);
        g[d[x][t]]+=k;
        y=b[y].r;
        ++t;
    }
}
int main()
{
    read(n,m);
    for(int i=1;i<=n;++i)
    {
        read(c[i]);
        --c[i];
        d[i][0]=1;
        d[i][1]=add(1,c[i]);
        ++g[d[i][1]];
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        read(z);
        if(z==1)
        {
            int x,y;
            read(x,y);
            b[x].r=y,b[y].l=x;
            int t=2;
            while(x!=0&&t<=50)
            {
                check(x,y,t,1);
                x=b[x].l,++t;
            }
        }
        else if(z==2)
        {
            int x;
            read(x);
            int y=b[x].r;
            b[x].r=b[y].l=0;
            int t=2;
            while(x!=0&&t<=50)
            {
                check(x,y,t,-1);
                x=b[x].l,++t;
            }
        }
        else if(z==3)
        {
            int k,l=0;
            char c=gc();
            while(c<'0'||c>'9') c=gc();
            while(c>='0'&&c<='9') e[++l]=c,c=gc();
            read(k);
            ll s=1;
            for(int i=1;i<=l-k+1;++i)
            {
                int x=1;
                for(int j=i;j<=i+k-1;++j) x=a[x][e[j]-'1'];
                s=(s*g[x])%P;
            }
            print(s);
            putchar('\n');
        }
    }
    return 0;
}