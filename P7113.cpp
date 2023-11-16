#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef __int128_t int128;
const int N=1000001;
int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
void print(int128 x)
{
    if(x>=10) print(x/10);
    printf("%d",int(x%10));
}
int128 b[N],m,n,d,q=0;
int128 t[N];
struct P
{
    int128 x=0,y=1;
}p[N];
struct A
{
    int128 a,p=-1;
}a[N];
int128 gcd(int128 a,int128 b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void dfs(int128 x,int128 w)
{
    if(b[x]==0)
    {
        p[x].x=p[x].x*w+p[x].y;
        p[x].y*=w;
        d=gcd(p[x].x,p[x].y);
        p[x].x/=d;
        p[x].y/=d;
        return;
    }
    for(int i=t[x];i!=-1;i=a[i].p)
    {
        dfs(a[i].a,w*b[x]);
    }
}
int main()
{
    n=read(),m=read();
    int128 x;
    for(int i=1;i<=n;++i)
    {
        b[i]=read();
        for(int j=1;j<=b[i];++j)
        {
            x=read();
            if(j==1) t[i]=q+1;
            else a[q].p=q+1;
            ++q;
            a[q].a=x;
            a[q].p=-1;
        }
    }
    for(int i=1;i<=m;++i) dfs(i,1);
    bool u=false;
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0)
        {
            if(u==true) printf("\n");
            print(p[i].x);
            printf(" ");
            print(p[i].y);
            u=true;
        }
    }
    return 0;
}