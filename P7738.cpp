#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef unsigned long long ull;
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
const int N=400001;
int n,m,a[N][16],d[16],g[65536];
vector<int> b[16][65536];
namespace abc
{
    typedef unsigned long long ull;
    const int N = 400000;
    bool s[N+1][256];

    ull myRand(ull &k1, ull &k2) {
        ull k3 = k1, k4 = k2;
        k1 = k4;
        k3 ^= (k3 << 23);
        k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
        return k2 + k4;
    }

    void gen(int n, ull a1, ull a2) {
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 256; j++)
                s[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
    }
}
int sum(int x)
{
    int s=0;
    while(x) x-=x&-x,++s;
    return s;
}
int main()
{
    ull z1,z2;
    read(n),read(m),read(z1),read(z2);
    abc::gen(n,z1,z2);
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<256;++j) a[i][j/16]+=(abc::s[i][j]<<(j%16));
        for(int j=0;j<16;++j) b[j][a[i][j]].push_back(i);
    }
    for(int i=0;i<65536;++i) g[i]=sum(i);
    int las=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=0;j<16;++j) d[j]=0;
        for(int j=0;j<64;++j)
        {
            char z=gc();
            while(!((z>='0'&&z<='9')||(z>='A'&&z<='Z'))) z=gc();
            int p=0;
            if(z>='0'&&z<='9') p=(z-'0');
            if(z>='A'&&z<='Z') p=(z-'A'+10);
            for(int k=0;k<4;++k) d[j/4]+=(((p&(1<<(3-k)))!=0)<<(j%4*4+k));
        }
        int t;
        read(t);
        if(las)
        {
            for(int j=0;j<16;++j) d[j]^=((1<<16)-1);
        }
        las=0;
        for(int j=0;j<16;++j)
        {
            for(auto k:b[j][d[j]])
            {
                int w=0;
                for(int l=0;l<16;++l)
                {
                    w+=g[a[k][l]^d[l]];
                    if(w>t) break;
                }
                if(w<=t)
                {
                    las=1;
                    break;
                }
            }
            if(las) break;
        }
        print(las);
        putchar('\n');
    }
    return 0;
}