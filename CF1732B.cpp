#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            if((a[i]=='1')^(a[i-1]=='1')) ++s;
        }
        printf("%d\n",max(s-1,0));
    }
    return 0;
}