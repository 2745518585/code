#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
char a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        if(n==1)
        {
            if(a[1]!=a[2]) printf("-1\n");
            else if(a[1]=='1') printf("1\n()\n");
            else printf("0\n");
            continue;
        }
        int t=0;
        for(int i=1;i<=n*2;i+=2)
        {
            if(a[i]==a[i+1])
            {
                b[i]='(',b[i+1]=')';
                a[i]^=1,a[i+1]^=1;
            }
            else
            {
                if(t>0)
                {
                    b[i]=b[i+1]=')';
                    --t;
                    a[i+1]^=1;
                }
                else
                {
                    b[i]=b[i+1]='(';
                    ++t;
                    a[i]^=1;
                }
            }
        }
        if(t!=0||a[1]!=a[n*2])
        {
            printf("-1\n");
            continue;
        }
        if(a[1]=='1') printf("4\n");
        else printf("3\n");
        
        b[n*2+1]='\0';
        printf("%s\n",b+1);

        if(a[1]=='1')
        {
            for(int i=1;i<=n;++i) printf("()");
            printf("\n");
            for(int i=1;i<=n*2;++i) a[i]^=1;
        }

        printf("((");
        for(int i=3;i<=n*2-2;i+=2)
        {
            if(a[i]=='1') printf(")(");
            else printf("()");
        }
        printf("))");
        printf("\n");

        printf("((");
        for(int i=1;i<=n-2;++i) printf("()");
        printf("))");
        printf("\n");
    }
    return 0;
}