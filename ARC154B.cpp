#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,h[N];
char a[N],b[N];
int main()
{
    scanf("%d%s%s",&n,a+1,b+1);
    for(int i=1;i<=n;++i)
    {
        ++h[a[i]-'a'+1];
        --h[b[i]-'a'+1];
    }
    for(int i=1;i<=26;++i)
    {
        if(h[i]!=0)
        {
            printf("-1");
            return 0;
        }
    }
    int x=n;
    for(int i=n;i>=1;--i)
    {
        while(x>=1&&a[i]!=b[x]) --x;
        if(x==0)
        {
            printf("%d",i);
            return 0;
        }
        --x;
    }
    printf("0");
    return 0;
}