#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
#define sum(x,y) (ll)(x-1)*n+y
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline
void read(T& x)
{
    T f=1,b=0;char ch=gc();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=gc();}
    while(ch>='0'&&ch<='9') b*=10,b+=ch-'0',ch=gc();
    x=f*b;return;
}
template<typename T> inline
void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int st[129]={0},k=0;
    while(x) st[++k]=x%10,x/=10;
    for(int i=k;i;i--) putchar(st[i]+'0');
}
const int N=1000001;
int n,m,k,p=1,t[N],b[N],c[N],d[N],e[N],l[N];
bool h[N];
struct road
{
    int m,q;
}a[N];
map<ll,int> Map;
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int k,int q)
{
    c[k]=x;
    if(k==m+1)
    {
        printf("TAK\n");
        for(int i=1;i<=k;++i) printf("%d\n",c[i]);
        exit(0);
    }
    if(q)
    {
        h[q]=true;
        dfs(a[q].m,k+1,d[q]);
        h[q]=false;
        return;
    }
    for(int i=t[x];i;i=a[i].q)
    {
        if(h[i]||e[i]) continue;
        h[i]=true;
        dfs(a[i].m,k+1,d[i]);
        h[i]=false;
    }
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        read(x),read(y);
        road(x,y);
        Map[sum(x,y)]=p;
        ++l[x],--l[y];
    }
    for(int i=1;i<=n;++i)
    {
        if(l[i]!=0)
        {
            printf("NIE");
            return 0;
        }
    }
    read(k);
    for(int i=1;i<=k;++i)
    {
        int q;
        read(q);
        for(int j=1;j<=q;++j) read(b[j]);
        for(int j=1;j<=q-1;++j)
        {
            if(!Map.count(sum(b[j],b[j+1])))
            {
                printf("NIE");
                return 0;
            }
            int x=Map[sum(b[j],b[j+1])];
            if(j<=q-2)
            {
                int y=Map[sum(b[j+1],b[j+2])];
                if(d[x]==0) d[x]=y;
                if(d[x]!=y)
                {
                    printf("NIE");
                    return 0;
                }
            }
            if(j>=2)
            {
                int y=Map[sum(b[j-1],b[j])];
                if(e[x]==0) e[x]=y;
                if(e[x]!=y)
                {
                    printf("NIE");
                    return 0;
                }
            }
        }
    }
    dfs(1,1,0);
    printf("NIE");
    return 0;
}