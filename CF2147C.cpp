#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
char a[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%s",&n,a+1);
        a[0]=a[n+1]='0';
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(a[i]=='1') continue;
            if(a[i-1]=='0'||a[i+1]=='0')
            {
                while(a[i+1]=='1'&&a[i+2]=='0'&&i+2<=n) i+=2;
                continue;
            }
            if(a[i+1]=='1'&&a[i+2]=='0'&&i+2<=n)
            {
                i+=2;
                continue;
            }
            u=false;
            break;
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}