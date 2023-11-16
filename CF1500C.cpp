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
const int N=3001;
int n,m,a[N][N],b[N][N],c[N],c1[N],c2[N],d[N],g[N];
bool h[N];
bool cmp1(int x,int y)
{
    for(int i=1;i<=m;++i)
    {
        if(a[x][i]!=a[y][i]) return a[x][i]<a[y][i];
    }
    return x<y;
}
bool cmp2(int x,int y)
{
    for(int i=1;i<=m;++i)
    {
        if(b[x][i]!=b[y][i]) return b[x][i]<b[y][i];
    }
    return x<y;
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j) read(a[i][j]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j) read(b[i][j]);
    }
    for(int i=1;i<=n;++i) c1[i]=i;
    sort(c1+1,c1+n+1,cmp1);
    for(int i=1;i<=n;++i) c2[i]=i;
    sort(c2+1,c2+n+1,cmp2);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(a[c1[i]][j]!=b[c2[i]][j])
            {
                printf("-1");
                return 0;
            }
        }
    }
    for(int i=1;i<=n;++i) c[c2[i]]=c1[i];
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n-1;++j)
        {
            if(a[c[j]][i]>a[c[j+1]][i]) ++g[i];
        }
    }
    vector<int> s;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(g[j]!=0) continue;
            for(int k=1;k<=n-1;++k)
            {
                if(!h[k]&&a[c[k]][j]<a[c[k+1]][j])
                {
                    h[k]=true;
                    for(int l=1;l<=m;++l)
                    {
                        if(a[c[k]][l]>a[c[k+1]][l]) --g[l];
                    }
                }
            }
            g[j]=-1;
            s.push_back(j);
            break;
        }
    }
    bool u=true;
    for(int i=1;i<=n-1;++i)
    {
        if(!h[i]&&c[i]>c[i+1]) u=false;
    }
    if(u)
    {
        printf("%d\n",s.size());
        while(!s.empty()) printf("%d ",s.back()),s.pop_back();
    }
    else printf("-1");
    return 0;
}