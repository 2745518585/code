#include<cstdio>
#include<algorithm>
using namespace std;
int n,a,b,c,d;
int main()
{
    scanf("%d%d%d%d%d",&n,&a,&b,&c,&d);
    if(abs(b-c)>1||(a!=0&&d!=0&&b==0&&c==0)) printf("No\n");
    else printf("Yes\n");
    return 0;
}