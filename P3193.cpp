#include<cstdio>
using namespace std;
const int M=21;
int n,m,p,a[M][M],b[M][M],f[M];
char s[M];
void times(int c[][M],int a[][M],int b[][M])
{
    int t[M][M]={0};
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<m;++j)
        {
            for(int k=0;k<m;++k)
            {
                t[i][j]=(t[i][j]+(a[i][k]*b[k][j])%p)%p;
            }
        }
    }
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<m;++j)
        {
            c[i][j]=t[i][j];
        }
    }
}
void abc(long long x)
{
    while(x)
    {
        if(x&1) times(a,a,b);
        times(b,b,b);
        x>>=1;
    }
}
int main()
{
    scanf("%d%d%d%s",&n,&m,&p,s+1);
    f[1]=0;
    for(int i=2,j=0;i<=m;++i)
    {
        while(s[i]!=s[j+1]&&j!=0) j=f[j];
        if(s[i]==s[j+1]) ++j;
        f[i]=j;
    }
    for(int i=0;i<m;++i)
    {
        for(int j='0';j<='9';++j)
        {
            int x=i;
            while(s[x+1]!=j&&x!=0) x=f[x];
            if(s[x+1]==j) ++x;
            if(x<m) ++b[i][x];
        }
    }
    a[0][0]=1;
    abc(n);
    int s=0;
    for(int i=0;i<m;++i) s=(s+a[0][i])%p;
    printf("%d",s);
    return 0;
}