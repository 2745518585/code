#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
char a[N],b[N];
bool f[N][2];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s%s",&n,a+1,b+1);
        f[0][0]=f[0][1]=true;
        for(int i=1;i<=n;++i)
        {
            f[i][0]=f[i][1]=false;
            if(a[i]=='B'&&b[i]=='W') f[i][0]|=f[i-1][0];
            else if(a[i]=='W'&&b[i]=='B') f[i][1]|=f[i-1][1];
            else f[i][0]|=f[i-1][1],f[i][1]|=f[i-1][0];
        }
        if(f[n][0]||f[n][1]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}