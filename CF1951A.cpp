#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
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
        int w=0,s1=1e9,s2=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]=='1')
            {
                ++w;
                s1=min(s1,i);
                s2=max(s2,i);
            }
        }
        if(w%2==1||(w==2&&s1==s2-1))
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
        }
    }
    return 0;
}