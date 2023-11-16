#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)    
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        if(n%2==0)
        {
            int s1=2e9,s2=2e9,q1,q2;
            for(int i=1;i<=n;++i)
            {
                if(i%2==1&&a[i]<s1) s1=a[i],q1=i;
                if(i%2==0&&a[i]<s2) s2=a[i],q2=i;
            }
            if(s1>s2||(s1==s2&&q1>q2)) printf("Mike\n");
            else printf("Joe\n");
        }
        else printf("Mike\n");
    }
    return 0;
}