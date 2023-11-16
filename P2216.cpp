#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int m,n,k,a[N][N],b1[N][N],b2[N][N],c1[N][N],c2[N][N],Q[N],s=1e9,T=0,R=0;
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;++i)
    {
        T=1,R=0;
        for(int j=1;j<=n;++j)
        {
            while(T<=R&&j-Q[T]>=k) ++T;
            while(T<=R&&a[i][j]<=a[i][Q[R]]) --R;
            Q[++R]=j;
            b1[i][j]=a[i][Q[T]];
        }
    }
    for(int i=1;i<=m;++i)
    {
        T=1,R=0;
        for(int j=1;j<=n;++j)
        {
            while(T<=R&&j-Q[T]>=k) ++T;
            while(T<=R&&a[i][j]>=a[i][Q[R]]) --R;
            Q[++R]=j;
            b2[i][j]=a[i][Q[T]];
        }
    }
    for(int i=1;i<=n;++i)
    {
        T=1,R=0;
        for(int j=1;j<=m;++j)
        {
            while(T<=R&&j-Q[T]>=k) ++T;
            while(T<=R&&b1[j][i]<=b1[Q[R]][i]) --R;
            Q[++R]=j;
            c1[j][i]=b1[Q[T]][i];
        }
    }
    for(int i=1;i<=n;++i)
    {
        T=1,R=0;
        for(int j=1;j<=m;++j)
        {
            while(T<=R&&j-Q[T]>=k) ++T;
            while(T<=R&&b2[j][i]>=b2[Q[R]][i]) --R;
            Q[++R]=j;
            c2[j][i]=b2[Q[T]][i];
        }
    }
    for(int i=k;i<=m;++i)
    {
        for(int j=k;j<=n;++j)
        {
            s=min(s,c2[i][j]-c1[i][j]);
        }
    }
    printf("%d",s);
    return 0;
}