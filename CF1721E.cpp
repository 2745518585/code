#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2000001,M=31;
int m,n,f[N],g[N][M];
char a[N];
void KMP0()
{
    f[1]=0;
    for(int i=2,j=0;i<=m;++i)
    {
        while(j!=0&&a[i]!=a[j+1]) j=f[j];
        if(a[i]==a[j+1]) ++j;
        f[i]=j;
    }
    for(int i=0;i<=m-1;++i)
    {
        for(int j='a';j<='z';++j)
        {
            int x=i;
            if(x!=0&&j!=a[x+1]) x=f[x];
            if(i==x) g[i][j-'a']=i;
            else g[i][j-'a']=g[x][j-'a'];
        }
    }
}
void KMP()
{
    int n=strlen(a+m+1)+m;
    for(int i=m+1,j=f[m];i<=n;++i)
    {
        while(j!=0&&a[i]!=a[j+1])
        {
            if(g[j][a[i]-'a']!=-1)
            {
                j=g[j][a[i]-'a'];
                break;
            }
            j=f[j];
        }
        if(a[i]==a[j+1]) ++j;
        f[i]=j;
        printf("%d ",j);
    }
}
int main()
{
    scanf("%s%d",a+1,&n);
    m=strlen(a+1);
    for(int i=0;i<=m+100;++i)
    {
        for(int j=0;j<=25;++j) g[i][j]=-1;
    }
    KMP0();
    for(int i=1;i<=n;++i)
    {
        scanf("%s",a+m+1);
        KMP();
        printf("\n");
    }
    return 0;
}