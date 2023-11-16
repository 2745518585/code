#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
char a[101];
bool h[31][31][31];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(h,0,sizeof(h));
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            scanf("%s",a+1);
            if(strlen(a+1)==1) u=true;
            else if(strlen(a+1)==2)
            {
                if(a[1]==a[2]) u=true;
                if(h[a[2]-'a'+1][0][0]) u=true;
                if(h[a[2]-'a'+1][a[1]-'a'+1][0]) u=true;
                for(int j=1;j<=26;++j)
                {
                    if(h[a[2]-'a'+1][a[1]-'a'+1][j]) u=true;
                }
                h[a[1]-'a'+1][a[2]-'a'+1][0]=true;
            }
            else if(strlen(a+1)==3)
            {
                if(a[1]==a[3]) u=true;
                if(a[1]==a[2]&&h[a[3]-'a'+1][0][0]) u=true;
                if(h[a[3]-'a'+1][a[2]-'a'+1][0]) u=true;
                if(h[a[3]-'a'+1][a[2]-'a'+1][a[1]-'a'+1]) u=true;
                h[a[1]-'a'+1][a[2]-'a'+1][a[3]-'a'+1]=true;
            }
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}