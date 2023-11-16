#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=1000001;
int n,a[N<<1],Q[N<<1],T,R;
int main()
{
    int K=read();
    while(K--)
    {
        n=read();
        for(int i=1;i<=n;++i) a[i]=read();
        for(int i=1;i<=n;++i)
        {
            a[i]-=read();
            a[n+i]=a[i];
        }
        for(int i=1;i<=n*2;++i) a[i]+=a[i-1];
        T=0,R=-1;
        bool u=false; 
        for(int i=1;i<=n*2-1;++i)
        {
            while(T<=R&&Q[T]<=i-n) ++T;
            while(T<=R&&a[Q[R]]>a[i]) --R;
            Q[++R]=i;
            if(i>=n&&a[Q[T]]>=a[i-n])
            {
                printf("%d\n",i-n+1);
                u=true;
                break;
            }
        }
        if(u==false) printf("Failed!\n");
    }
    return 0;
}