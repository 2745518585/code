#include<cstdio>
#include<algorithm>
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
        scanf("%d%s",&n,a+1);
        for(int i=0;i<=1000;++i) h[i]=0;
        bool u=false;
        for(int i=1;i<=n-1;++i)
        {
            int x=(a[i]-'a')*26+(a[i+1]-'a');
            if(h[x]!=0&&i-h[x]>=2)
            {
                u=true;
                break;
            }
            if(h[x]==0) h[x]=i;
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}