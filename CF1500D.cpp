#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
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
const int N=1501;
int n,q,a[N][N],d[N];
bool h[N*N];
vector<pair<int,int>> f[N][N];
int main()
{
    read(n),read(q);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            read(a[i][j]);
            vector<pair<int,int>> p;
            for(auto k:f[i-1][j-1]) p.push_back(make_pair(k.first+1,k.second));
            for(auto k:f[i-1][j]) p.push_back(make_pair(k.first+1,k.second));
            for(auto k:f[i][j-1]) p.push_back(make_pair(k.first+1,k.second));
            p.push_back(make_pair(1,a[i][j]));
            sort(p.begin(),p.end());
            for(auto k:p)
            {
                if(h[k.second]) continue;
                h[k.second]=true;
                f[i][j].push_back(k);
                if(f[i][j].size()>=q+1) break;
            }
            for(auto k:f[i][j]) h[k.second]=false;
            if(f[i][j].size()>=q+1) ++d[min(f[i][j].back().first-1,min(i,j))];
            else ++d[min(i,j)];
        }
    }
    for(int i=n;i>=1;--i) d[i]+=d[i+1];
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",d[i]);
    }
    return 0;
}