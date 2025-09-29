#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k;
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%s",&n,&k,a+1);
        int t=0;
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(a[i]=='0') t=i;
            if(i-t>=k) u=false;
        }
        if(u)
        {
            printf("YES\n");
            int s1=1,s2=n;
            for(int i=1;i<=n;++i)
            {
                if(a[i]=='1') printf("%d ",s1++);
                else printf("%d ",s2--);
            }
            printf("\n");
        }
        else printf("NO\n");
    }
    return 0;
}