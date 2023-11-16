#include<cstdio>
#include<algorithm>
#include<cstring>
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
        scanf("%s",a+1);
        n=strlen(a+1);
        int s=1e9;
        for(int i=2;i<=n-1;++i)
        {
            if(a[i]=='O')
            {
                s=min(s,(a[i-1]!='M')+(a[i+1]!='O'));
            }
        }
        if(s==1e9) printf("-1\n");
        else printf("%d\n",s+n-3);
    }
    return 0;
}