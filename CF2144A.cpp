#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
int sum(int x,int y)
{
    int s=0;
    for(int i=x;i<=y;++i) s+=a[i];
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        int x1=0,x2=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=i+1;j<=n-1;++j)
            {
                int s1=sum(1,i),s2=sum(i+1,j),s3=sum(j+1,n);
                if((s1%3==s2%3&&s2%3==s3%3)||(s1%3!=s2%3&&s2%3!=s3%3&&s3%3!=s1%3)) x1=i,x2=j;
            }
        }
        printf("%d %d\n",x1,x2);
    }
    return 0;
}