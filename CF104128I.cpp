#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n,h[N];
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        for(int i=0;i<=25;++i) h[i]=0;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]-'a'];
        }
        int s=0;
        for(int i=0;i<=25;++i) s=max(s,h[i]);
        printf("%d\n",n-s);
    }
    return 0;
}