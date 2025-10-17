#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,x1,y1,x2,y2;
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d%d%d%d",&n,&x1,&y1,&x2,&y2);
        if(x1>x2) x1=n-x1,x2=n-x2;
        if(y1>y2) y1=n-y1,y2=n-y2;
        printf("%d\n",max(x1!=x2?x2:0,y1!=y2?y2:0));
    }
    return 0;
}