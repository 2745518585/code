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
        int x=0;
        for(int i=2;i<=n-1;++i)
        {
            if(a[i]=='a')
            {
                x=i;
                break;
            }
        }
        if(x!=0)
        {
            for(int i=1;i<=x-1;++i) printf("%c",a[i]);
            printf(" %c ",a[x]);
            for(int i=x+1;i<=n;++i) printf("%c",a[i]);
            printf("\n");
        }
        else
        {
            printf("%c ",a[1]);
            for(int i=2;i<=n-1;++i) printf("%c",a[i]);
            printf(" %c",a[n]);
            printf("\n");
        }
    }
    return 0;
}