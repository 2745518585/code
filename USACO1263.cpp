#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,b[N];
char a[N];
int main()
{
    scanf("%d%s",&n,a+1);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    int x1=0,x2=0,x3=0,x4=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='G'&&x1==0) x1=i;
        if(a[i]=='H'&&x2==0) x2=i;
        if(a[i]=='G') x3=i;
        if(a[i]=='H') x4=i;
    }
    int s=(b[x1]>=x3&&b[x2]>=x4);
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='G'&&i<x2&&b[i]>=x2&&b[x2]>=x4) ++s;
        if(a[i]=='H'&&i<x1&&b[i]>=x1&&b[x1]>=x3) ++s;
    }
    printf("%d",s);
    return 0;
}