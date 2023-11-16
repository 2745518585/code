#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2000001;
int n,f[N];
char a[N];
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        int w=0;
        for(int j=i;j<=n;++j)
        {
            if(w&(1<<(a[j]-'a'))) break;
            w|=(1<<(a[j]-'a'));
            f[w]=j-i+1;
        }
    }
    for(int i=0;i<=20;++i)
    {
        for(int j=0;j<=(1<<20)-1;++j)
        {
            if(j&(1<<i)) f[j]=max(f[j],f[j^(1<<i)]);
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        int w=0;
        for(int j=i;j<=n;++j)
        {
            if(w&(1<<(a[j]-'a'))) break;
            w|=(1<<(a[j]-'a'));
            s=max(s,(j-i+1)+f[((1<<20)-1)^w]);
        }
    }
    printf("%d",s);
    return 0;
}