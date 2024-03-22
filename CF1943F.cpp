#include<cstdio>
#include<algorithm>
using namespace std;
const int N=11001;
int n,m,c[N],d1[N],d0[N],f[N][N];
char a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s%s",&n,a+1,b+1);
        int z=0;
        for(int i=1;i<=n;++i) z+=b[i]-'0';
        if(z>=(n+1)/2)
        {
            for(int i=1;i<=n;++i) a[i]='0'+'1'-a[i],b[i]='0'+'1'-b[i];
        }
        for(int i=1;i<=n;++i)
        {
            c[i]=max(c[i-1]+(b[i]=='1'?1:-1),0);
        }
        for(int i=1;i<=n;++i) d0[i]=d0[i-1]+((b[i]-'0')^1);
        for(int i=1;i<=n;++i) d1[i]=d1[i-1]+b[i]-'0';
        for(int i=0;i<=n;++i)
        {
            for(int j=0;j<=n;++j) f[i][j]=1e9;
        }
        f[0][0]=0;
        for(int i=1;i<=n;++i)
        {
            if(b[i]=='0')
            {
                for(int j=0;j<=n-1;++j) f[i][j]=min(f[i][j],f[i-1][j+1]);
                if(a[i]=='1')
                {
                    int x=i-1;
                    for(int j=i;j<=n;++j)
                    {
                        int t=((d0[j]-d0[i-1])-(d1[j]-d1[i-1])+1)/2;
                        while(d0[j]-d0[x]>t) ++x;
                        f[j][min(c[x],x-i+1)+(j-x)]=min(f[j][min(c[x],x-i+1)+(j-x)],f[i-1][0]+max(t,0));
                    }
                }
                else f[i][0]=min(f[i][0],f[i-1][0]);
            }
            else
            {
                for(int j=1;j<=n;++j) f[i][j]=min(f[i][j],f[i-1][j-1]);
            }
        }
        int s=1e9;
        for(int i=0;i<=n;++i) s=min(s,f[n][i]);
        printf("%d\n",s);
    }
    return 0;
}