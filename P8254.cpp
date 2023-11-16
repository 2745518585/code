#include<cstdio>
#include<iostream>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int m,n,s,a[10001];
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x=read();
            if(x==1) ++a[j];
            else --a[j];
        }
    }
    for(int i=1;i<=n;++i)
    {
        int x=read();
        if((x==1&&a[i]>0)||(x==0&&a[i]<0)) ++s;
    }
    printf("%d",s);
    return 0;
}