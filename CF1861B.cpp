#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n;
char a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s%s",a+1,b+1);
        n=strlen(a+1);
        bool u=false;
        for(int i=1;i<=n-1;++i)
        {
            if(a[i]=='0'&a[i+1]=='1'&&b[i]=='0'&&b[i+1]=='1') u=true;
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}