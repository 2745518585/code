#include<cstdio>
#include<algorithm>
using namespace std;
char a[100];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        for(int i=1;i<=9;++i)
        {
            if(a[i]=='1')
            {
                printf("13\n");
                break;
            }
            if(a[i]=='3')
            {
                printf("31\n");
                break;
            }
        }
    }
    return 0;
}