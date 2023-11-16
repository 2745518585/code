#include<bits/stdc++.h>
using namespace std;
const int N=501;
int n,m,k,a[N],b[N],d[N][2],h[N],g[N];
char z[N];
struct str
{
    int s,w;
    str(){}
    str(int s,int w):s(s),w(w){}
    friend str operator +(str a,str b)
    {
        return str(a.s+b.s,a.w+b.w);
    }
}f[N][N],f2[N][N];
str max(str a,str b)
{
    if(a.s>b.s||(a.s==b.s&&a.w<b.w)) return a;
    return b;
}
int main()
{
    scanf("%s",z+1);
    m=strlen(z+1);
    for(int i=1;i<=m;++i)
    {
        if(z[i]=='1') h[++k]=i;
    }
    scanf("%s",z+1);
    n=strlen(z+1);
    for(int i=1;i<=n;++i)
    {
        b[i]=z[i]-'0';
    }
    b[n+1]=-1;
    g[1]=0;
    for(int i=2,j=0;i<=n;++i)
    {
        while(j!=0&&b[i]!=b[j+1]) j=g[j];
        if(b[i]==b[j+1]) ++j;
        g[i]=j;
    }
    for(int i=0;i<=n;++i)
    {
        int x=i;
        while(x!=0&&b[x+1]!=0) x=g[x];
        if(b[x+1]==0) ++x;
        d[i][0]=x;
        x=i;
        while(x!=0&&b[x+1]!=1) x=g[x];
        if(b[x+1]==1) ++x;
        d[i][1]=x;
    }
    for(int i=0;i<=k;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f[i][j]=str(-1e9,0);
        }
    }
    f[0][0]=str(0,0);
    for(int i=1;i<=m;++i)
    {
        for(int j=0;j<=k;++j)
        {
            for(int l=0;l<=n;++l)
            {
                f2[j][l]=f[j][l];
                f[j][l]=str(-1e9,0);
            }
        }
        for(int j=0;j<=k;++j)
        {
            for(int l=0;l<=n;++l)
            {
                f[j][d[l][0]]=max(f[j][d[l][0]],f2[j][l]+str(d[l][0]==n,0));
                f[j+1][d[l][1]]=max(f[j+1][d[l][1]],f2[j][l]+str(d[l][1]==n,abs(i-h[j+1])));
            }
        }
    }
    str s=str(0,0);
    for(int i=0;i<=n;++i)
    {
        s=max(s,f[k][i]);
    }
    printf("%d %d",s.s,s.w);
    return 0;
}