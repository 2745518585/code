#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,b[N];
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        int s=0;
        for(int i=1;i<=n;++i) s+=(a[i]=='1');
        if(s%2==1)
        {
            printf("NO\n");
            continue;
        }
        int w=0,q=0;
        for(int i=1;i<=n;++i)
        {
            w+=(a[i]=='1');
            q+=(a[i]=='0');
            if(a[i]=='1')
            {
                if(w<=s/2) b[i]=0;
                else b[i]=1;
            }
            else
            {
                if(q%2==1) b[i]=0;
                else b[i]=1;
            }
        }
        int t1=0,t2=0;
        for(int i=1;i<=n;++i)
        {
            if(b[i]==0) ++t1;
            else --t1;
            if((a[i]-'0')^b[i]) ++t2;
            else --t2;
            if(t1<0||t2<0) break;
        }
        if(t1<0||t2<0)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        for(int i=1;i<=n;++i)
        {
            if(b[i]==0) printf("(");
            else printf(")");
        }
        printf("\n");
        for(int i=1;i<=n;++i)
        {
            if((a[i]-'0')^b[i]) printf("(");
            else printf(")");
        }
        printf("\n");
    }
    return 0;
}