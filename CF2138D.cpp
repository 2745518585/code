#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=1e9+7;
int n,m,b[N];
ll jc[N],C[N][N],A[N][N];
struct str
{
    int x,t;
}a[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%*d%d",&n,&m);
        jc[0]=1;
        for(int i=1;i<=m;++i) jc[i]=jc[i-1]*i%P;
        C[0][0]=A[0][0]=1;
        for(int i=1;i<=m;++i)
        {
            C[i][0]=A[i][0]=1;
            for(int j=1;j<=i;++j)
            {
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
                A[i][j]=C[i][j]*jc[j]%P;
            }
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&a[i].t,&a[i].x);
            a[i].x-=a[i].t;
        }
        sort(a+1,a+m+1,[&](str x,str y){
            if(x.x!=y.x) return x.x<y.x;
            return x.t<y.t;
        });
        for(int i=1;i<=n;++i)
        {
            int w1=0,w2=0,w3=0,w4=0;
            ll s=0;
            for(int j=1;j<=m;++j)
            {
                if(a[j].t<i) ++w1;
                if(a[j].t==i) ++w2;
            }
            bool u=false;
            for(int j=1;j<=m;++j)
            {
                if(j>1&&a[j].x==a[j-1].x) continue;
                int u1=0,u2=0,u3=0;
                for(int p=j;p<=m&&a[p].x==a[j].x;++p)
                {
                    if(a[p].t<i) ++u1;
                    if(a[p].t==i) ++u2;
                    if(a[p].t>i) ++u3;
                }
                w1-=u1,w2-=u2;
                ll w=0;
                if(u1!=0)
                {
                    if(w3+w4!=0)
                    {
                        w=(w+u1*(w3+w4)%P*jc[w1+w2+w3+w4-1]%P*A[w1+w2+w3+w4+u1+u2-1][u1+u2-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u3]%P)%P;
                        u=true;
                    }
                    else if(b[i]<=a[j].x+i&&w1+w2==0)
                    {
                        if(b[i]<a[j].x+i)
                        {
                            w=(w+u1*jc[w1+w2+w3+w4]%P*A[w1+w2+w3+w4+u1+u2-1][u1+u2-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u3]%P)%P;
                            u=true;
                        }
                        else
                        {
                            w=(w+u1*jc[w1+w2+w3+w4]%P*A[w1+w2+w3+w4+u1+u2+u3-1][u1+u2+u3-1]%P)%P;
                            u=true;
                        }
                    }
                }
                if(u2!=0)
                {
                    if(w1+w2+w3+w4!=0)
                    {
                        w=(w+u2*(w3+w4)*jc[w1+w2+w3+w4-1]%P*A[w1+w2+w3+w4+u1+u2-1][u1+u2-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u3]%P)%P;
                        w=(w+u2*(w1+w2)*jc[w1+w2+w3+w4-1]%P*A[w1+w2+w3+w4+u2+u3-1][u2+u3-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u1]%P)%P;
                        u=true;
                    }
                    else
                    {
                        if(b[i]<a[j].x+i)
                        {
                            w=(w+u2*A[w1+w2+w3+w4+u1+u2-1][u1+u2-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u3]%P)%P;
                            u=true;
                        }
                        if(b[i]>a[j].x+i)
                        {
                            w=(w+u2*A[w1+w2+w3+w4+u2+u3-1][u2+u3-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u1]%P)%P;
                            u=true;
                        }
                        if(b[i]==a[j].x+i)
                        {
                            w=(w+u2*jc[u1+u2+u3-1]%P)%P;
                            u=true;
                        }
                    }
                }
                if(u3!=0)
                {
                    if(w1+w2!=0)
                    {
                        w=(w+u3*(w1+w2)%P*jc[w1+w2+w3+w4-1]%P*A[w1+w2+w3+w4+u2+u3-1][u2+u3-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u1]%P)%P;
                        u=true;
                    }
                    else if(b[i]>=a[j].x+i&&w3+w4==0)
                    {
                        if(b[i]>a[j].x+i)
                        {
                            w=(w+u3*jc[w1+w2+w3+w4]%P*A[w1+w2+w3+w4+u2+u3-1][u2+u3-1]%P*A[w1+w2+w3+w4+u1+u2+u3][u1]%P)%P;
                            u=true;
                        }
                        else
                        {
                            w=(w+u3*jc[w1+w2+w3+w4]%P*A[w1+w2+w3+w4+u1+u2+u3-1][u1+u2+u3-1]%P)%P;
                            u=true;
                        }
                    }
                }
                w=w*A[m][m-(w1+w2+w3+w4+u1+u2+u3)]%P;
                // printf("%d: %d %d %d: %d %d %d %d: %d\n",j,u1,u2,u3,w1,w2,w3,w4,w);
                s=(s+(a[j].x+i)*w%P)%P;
                // s=(s+w%P)%P;
                w3+=u2,w4+=u3;
            }
            if(!u) s=b[i]*jc[m]%P;
            // if(s!=jc[m]) exit(1);
            printf("%lld ",(s%P+P)%P);
        }
        printf("\n");
    }
    return 0;
}