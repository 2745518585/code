#include<cstdio>
using namespace std;
int f[10000001],n,p;
int main()
{
    scanf("%d%d",&n,&p);
    f[1]=1;
    printf("1\n");
    for(int i=2;i<=n;++i)
    {
        f[i]=(long long)(p-p/i)*f[p%i]%p;
        printf("%d\n",f[i]);
    }
    return 0;
}