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
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            if(a[i]!='a')
            {
                u=true;
                break;
            }
        }
        if(u==false)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        u=false;
        a[n+1]='a';
        for(int i=1;i<=(n+1)/2;++i)
        {
            if(a[i]!=a[(n+1)-i+1])
            {
                u=true;
                break;
            }
        }
        a[n+1]='\0';
        if(u) printf("%sa\n",a+1);
        else printf("a%s\n",a+1);
    }
    return 0;
}