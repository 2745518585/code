#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=20001;
const ll P=1e9+7;
int n,pw[7][N],b[7];
ll f1[N][8][8][8],f2[N][8][8][8];
char a[N];
int main()
{
    for(int i=1;i<=6;++i)
    {
        pw[i][0]=1;
        for(int j=1;j<=10000;++j) pw[i][j]=pw[i][j-1]*i%7;
    }
    f1[0][0][0][0]=f2[0][1][1][1]=1;
    for(int i=1;i<=10000;++i)
    {
        for(int j1=0;j1<=6;++j1) for(int j2=0;j2<=6;++j2) for(int j3=0;j3<=6;++j3)
        {
            (f1[i][j1][j2][j3]+=f1[i-1][j1][j2][j3])%=P;
            (f2[i][j1][j2][j3]+=f2[i-1][j1][j2][j3])%=P;
            if(i%2==1)
            {
                (f1[i][(j1+pw[1][i])%7][(j2+pw[2][i])%7][(j3+pw[3][i])%7]+=f1[i-1][j1][j2][j3])%=P;
            }
            else
            {
                (f2[i][(j1+pw[1][i])%7][(j2+pw[2][i])%7][(j3+pw[3][i])%7]+=f2[i-1][j1][j2][j3])%=P;
            }
        }
    }
    for(int i=0;i<=10000;++i)
    {
        for(int j1=0;j1<=6;++j1) for(int j2=0;j2<=6;++j2) for(int j3=0;j3<=6;++j3) (f2[i][j1][j2][7]+=f2[i][j1][j2][j3])%=P;
        for(int j1=0;j1<=6;++j1) for(int j2=0;j2<=6;++j2) for(int j3=0;j3<=7;++j3) (f2[i][j1][7][j3]+=f2[i][j1][j2][j3])%=P;
        for(int j1=0;j1<=6;++j1) for(int j2=0;j2<=7;++j2) for(int j3=0;j3<=7;++j3) (f2[i][7][j2][j3]+=f2[i][j1][j2][j3])%=P;
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        for(int i=1;i<=6;++i) b[i]=0;
        ll s=0;
        for(int i=n-1;i>=1;--i)
        {
            if(a[n-i]=='1')
            {
                for(int j1=0;j1<=6;++j1) for(int j2=0;j2<=6;++j2) for(int j3=0;j3<=6;++j3)
                {
                    if(f1[i-1][j1][j2][j3]==0) continue;
                    int p1[3]={7,((-b[1]-j1)%7+7)%7,((-b[6]+j1)%7+7)%7},p2[3]={7,((-b[2]-j2)%7+7)%7,((-b[5]+j2)%7+7)%7},p3[3]={7,((-b[3]-j3)%7+7)%7,((-b[4]+j3)%7+7)%7};
                    if(p1[1]==p1[2]) p1[2]=-1;
                    if(p2[1]==p2[2]) p2[2]=-1;
                    if(p3[1]==p3[2]) p3[2]=-1;
                    for(int k1=0;k1<=2;++k1) for(int k2=0;k2<=2;++k2) for(int k3=0;k3<=2;++k3)
                    {
                        if(p1[k1]==-1||p2[k2]==-1||p3[k3]==-1) continue;
                        int z=((p1[k1]<7)^(p2[k2]<7)^(p3[k3]<7))?-1:1;
                        s=(s+z*f1[i-1][j1][j2][j3]*f2[i-1][p1[k1]][p2[k2]][p3[k3]]%P);
                    }
                    s%=P;
                }
                for(int j=1;j<=6;++j) b[j]=(b[j]+pw[j][i])%7;
            }
        }
        if(a[n]=='1')
        {
            for(int i=1;i<=6;++i) b[i]=(b[i]+1)%7;
            if([&](){for(int i=1;i<=6;++i) if(b[i]==0) return false; return true;}()) ++s;
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}