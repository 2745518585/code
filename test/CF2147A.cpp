#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x<y) printf("2\n");
        else if(x>=y+2&&y>=2) printf("3\n");
        else printf("-1\n");
    }
    return 0;
}