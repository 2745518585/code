#include<cstdio>
#include<algorithm>
using namespace std;
int n,x1=1,y1=1,x2=1,y2=2;
void check1()
{
    ++y1;
    if(y1>n) ++x1,y1=1;
    while((x1+y1)%2!=0)
    {
        ++y1;
        if(y1>n) ++x1,y1=1;
    }
}
void check2()
{
    ++y2;
    if(y2>n) ++x2,y2=1;
    while((x2+y2)%2!=1)
    {
        ++y2;
        if(y2>n) ++x2,y2=1;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x==1)
        {
            if(x2<=n)
            {
                printf("2 %d %d\n",x2,y2);
                fflush(stdout);
                check2();
            }
            else
            {
                printf("3 %d %d\n",x1,y1);
                fflush(stdout);
                check1();
            }
        }
        else if(x==2)
        {
            if(x1<=n)
            {
                printf("1 %d %d\n",x1,y1);
                fflush(stdout);
                check1();
            }
            else
            {
                printf("3 %d %d\n",x2,y2);
                fflush(stdout);
                check2();
            }
        }
        else if(x==3)
        {
            if(x1<=n)
            {
                printf("1 %d %d\n",x1,y1);
                fflush(stdout);
                check1();
            }
            else
            {
                printf("2 %d %d\n",x2,y2);
                fflush(stdout);
                check2();
            }
        }
    }
    return 0;
}