#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=301;
const ll P=998244353;
int n,h[4][4][4][4][2],c[4][2];
char a[N];
ll f[N<<2][4][4][4][4],g[N<<2][4][4][4][4],s1,s2,s3;
int check(int x,int k)
{
    if((x&(1<<k))==0) return x|(1<<k);
    return 0;
}
void solve(int x)
{
    for(int j=0;j<=n*4;++j)
    {
        int k[4];
        for(k[0]=0;k[0]<=3;++k[0])
        for(k[1]=0;k[1]<=3;++k[1])
        for(k[2]=0;k[2]<=3;++k[2])
        for(k[3]=0;k[3]<=3;++k[3])
        {
            f[j][k[0]][k[1]][k[2]][k[3]]=0;
        }
    }
    {
        for(int i=0;i<=3;++i)
        {
            for(int j=0;j<=1;++j) c[i][j]=check(i,j);
        }
        int k[4];
        for(k[0]=0;k[0]<=3;++k[0])
        for(k[1]=0;k[1]<=3;++k[1])
        for(k[2]=0;k[2]<=3;++k[2])
        for(k[3]=0;k[3]<=3;++k[3])
        {
            for(int l=0;l<=1;++l)
            {
                int p=0;
                for(int o=0;o<=3;++o)
                {
                    if((x&(1<<o))&&c[k[o]][l]==0)
                    {
                        if(l==0) ++p;
                        else --p;
                    }
                }
                h[k[0]][k[1]][k[2]][k[3]][l]=p;
            }
        }
    }
    f[n*2][0][1][2][3]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=n*4;++j)
        {
            int k[4];
            for(k[0]=0;k[0]<=3;++k[0])
            for(k[1]=0;k[1]<=3;++k[1])
            for(k[2]=0;k[2]<=3;++k[2])
            for(k[3]=0;k[3]<=3;++k[3])
            {
                g[j][k[0]][k[1]][k[2]][k[3]]=f[j][k[0]][k[1]][k[2]][k[3]];
                f[j][k[0]][k[1]][k[2]][k[3]]=0;
            }
        }
        for(int j=0;j<=n*4;++j)
        {
            int k[4];
            for(k[0]=0;k[0]<=3;++k[0])
            for(k[1]=0;k[1]<=3;++k[1])
            for(k[2]=0;k[2]<=3;++k[2])
            for(k[3]=0;k[3]<=3;++k[3])
            {
                if(g[j][k[0]][k[1]][k[2]][k[3]]==0) continue;
                for(int l=0;l<=1;++l)
                {
                    if((l==0&&a[i]=='b')||(l==1&&a[i]=='a')) continue;
                    (f[j+h[k[0]][k[1]][k[2]][k[3]][l]][c[k[0]][l]][c[k[1]][l]][c[k[2]][l]][c[k[3]][l]]+=g[j][k[0]][k[1]][k[2]][k[3]])%=P;
                }
            }
        }
    }
    {
        int k[4];
        for(k[0]=0;k[0]<=3;++k[0])
        for(k[1]=0;k[1]<=3;++k[1])
        for(k[2]=0;k[2]<=3;++k[2])
        for(k[3]=0;k[3]<=3;++k[3])
        {
            int z=0;
            for(int p=0;p<=3;++p) z=k[z];
            int t=0;
            for(int p=0;p<=3;++p) t|=(1<<z),z=k[z];
            if(t!=x) continue;
            for(int j=0;j<=n*2-1;++j) s3=(s3+f[j][k[0]][k[1]][k[2]][k[3]])%P;
            s2=(s2+f[n*2][k[0]][k[1]][k[2]][k[3]])%P;
            for(int j=n*2+1;j<=n*4;++j) s1=(s1+f[j][k[0]][k[1]][k[2]][k[3]])%P;
        }
    }
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=0;i<=(1<<4)-1;++i) solve(i);
    printf("%lld\n%lld\n%lld\n",(s1%P+P)%P,(s2%P+P)%P,(s3%P+P)%P);
    return 0;
}