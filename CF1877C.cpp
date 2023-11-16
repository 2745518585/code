#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        if(k==1)
        {
            printf("1\n");
        }
        else if(k==2)
        {
            if(m<n) printf("%d\n",m);
            else printf("%d\n",n+(m-n)/n);
        }
        else if(k==3)
        {
            if(m<n) printf("0\n");
            else printf("%d\n",(m-n)-(m-n)/n);
        }
        else printf("0\n");
    }
    return 0;
}