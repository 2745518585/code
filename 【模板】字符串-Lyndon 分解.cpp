#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=10000001;
int n;
char a[N];
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    int s=0;
    for(int i=1;i<=n;)
    {
        int j=i,k=i+1;
        while(k<=n&&a[j]<=a[k])
        {
            if(a[j]<a[k]) j=i;
            else ++j;
            ++k;
        }
        while(i<=j)
        {
            s^=i+k-j-1;
            i+=k-j;
        }
    }
    printf("%d",s);
    return 0;
}