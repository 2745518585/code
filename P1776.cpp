#include<cstdio>
using namespace std;
int n,m,q[1000001][2],T=-1,R=0,f[100001];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int a,b,c;
        scanf("%d%d%d",&b,&a,&c);
        for(int j=0;j<a;++j)
        {
            T=0;
            R=-1;
            for(int k=j;k<=m;k+=a)
            {
                while(T<=R&&k-q[T][0]>a*c) ++T;
                while(T<=R&&q[R][1]+(k-q[R][0])/a*b<=f[k]) --R;
                q[++R][0]=k;
                q[R][1]=f[k];
                f[k]=q[T][1]+(k-q[T][0])/a*b;
            }
        }
    }
    printf("%d",f[m]);
    return 0;
}