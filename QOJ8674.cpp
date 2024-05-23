#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    printf("1 0 0\n");
    printf("0 1 0\n");
    printf("0 0 1\n");
    printf("1 1 1\n");
    printf("1 2 3\n");
    fflush(stdout);
    int s1,s2,s3,s4,s5;
    scanf("%d%d%d%d%d",&s1,&s2,&s3,&s4,&s5);
    if(s1+s2+s3==s4||s1+s2*2+s3*3==s5)
    {
        printf("%d %d %d\n",s1,s2,s3);
        return 0;
    }
    if(s2+s3*2==s5-s4)
    {
        printf("%d %d %d\n",s4-s2-s3,s2,s3);
    }
    else
    {
        printf("%d %d %d\n",s1,s4*3-s5-s1*2,s5-s4*2+s1);
    }
    return 0;
}