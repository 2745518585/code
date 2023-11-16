#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=1000001;
int n,b[N],f[N],g[N],S[N],T;
char a[N];
map<int,int> Map;
int sum(int x)
{
    int z=lower_bound(S+1,S+T+1,x)-S;
    return b[S[z]];
}
int main()
{
    scanf("%d",&n);
    int p=0;
    lll s=0,w=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%s%d",&a[i],&b[i]);
        a[i]=(a[i]+s%26-'a')%26+'a';
        b[i]^=(s&((1<<30)-1));
        // printf("%c %d\n",a[i],b[i]);
        if(i>1)
        {
            while(p!=0&&a[p+1]!=a[i]) p=f[p];
            if(a[p+1]==a[i]) ++p;
            f[i]=p;
            if(a[f[i-1]+1]==a[i]) g[i-1]=g[f[i-1]];
            else g[i-1]=f[i-1];
            g[i]=f[i];
        }
        else f[i]=0;
        int z=i-1;
        while(z!=0)
        {
            if(a[z+1]!=a[i])
            {
                int z2=sum(i-z);
                w-=z2;
                // printf("%d %d\n",z,z2);
                // print(w);putchar('\n');
                --Map[z2];
                z=f[z];
            }
            else z=g[z];
        }
        while(T>0&&b[S[T]]>=b[i]) --T;
        S[++T]=i;
        if(a[1]==a[i]) w+=b[i],++Map[b[i]];
        while(Map.begin()!=Map.end())
        {
            auto x=prev(Map.end());
            if(x->first<=b[i]) break;
            Map[b[i]]+=x->second;
            w-=(lll)(x->first-b[i])*x->second;
            // printf("%d %d\n",x->first,x->second);
            Map.erase(x);
        }
        s+=w;
        print(s);
        putchar('\n');
    }
    return 0;
}