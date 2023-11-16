#include<cstdio>
using namespace std;
const int N=1000001;
int n,m,a[N],Q[N],T,R;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    T=0,R=-1;
    for(int i=1;i<=n;++i)
    {
        while(T<=R&&Q[T]<=i-m) ++T;
        while(T<=R&&a[Q[R]]>a[i]) --R;
        Q[++R]=i;
        if(i>=m) printf("%d ",a[Q[T]]);
    }
    printf("\n");
    T=0,R=-1;
    for(int i=1;i<=n;++i)
    {
        while(T<=R&&Q[T]<=i-m) ++T;
        while(T<=R&&a[Q[R]]<a[i]) --R;
        Q[++R]=i;
        if(i>=m) printf("%d ",Q[T]);
    }
    return 0;
}