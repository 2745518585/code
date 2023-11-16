#include<cstdio>
#include<algorithm>
using namespace std;
int a[10];
int main()
{
    scanf("%d%d%d%d",&a[1],&a[2],&a[3],&a[4]);
    int s=a[1]+a[2]+a[3]+a[4];
    if(s%2!=0)
    {
        printf("No");
        return 0;
    }
    for(int i=0;i<=15;++i)
    {
        int w=0;
        for(int j=1;j<=4;++j)
        {
            if(i&(1<<(j-1))) w+=a[j];
        }
        if(w==s/2)
        {
            printf("Yes");
            return 0;
        }
    }
    printf("No");
    return 0;
}