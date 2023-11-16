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
        scanf("%d%s%s",&n,a+1,b+1);
        int w=0,x=-1;
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(x==-1) x=(a[i]-'0')^(b[i]-'0');
            if(((a[i]-'0')^(b[i]-'0'))!=x)
            {
                u=false;
                break;
            }
            if(a[i]=='0') ++w;
            else --w;
            if(w==0) x=-1;
        }
        if(x==1) u=false;
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}