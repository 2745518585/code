#include<bits/stdc++.h>
#define sum(x,y) (x-1)*n+y
#define min(x,y) x<y?x:y
const int N=101,M=3001,K=100001;
int m,n,q,s=1e9,p=1,p2=1,t[M],t2[M],f[M][M],g[2][K];
char b[N][N],d[K];
bool h[K];
struct road
{
    int m,q,w;
}a[K];
struct str
{
    int x,y,q,t;
}c[K];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void str(int x,int y,int k)
{
    c[++p2].x=x;
    c[p2].y=y;
    c[p2].q=t2[k];
    t2[k]=p2;
    c[p2].t=sum(x,y);
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("\n");
        for(int j=1;j<=n;++j)
        {
            b[i][j]=getchar();
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x=j;
            while(x>=1&&b[i][x]==b[i][j]) --x;
            if(x>=1) road(sum(i,j),sum(i,x),1);
            x=j;
            while(x<=n&&b[i][x]==b[i][j]) ++x;
            if(x<=n) road(sum(i,j),sum(i,x),1);
            x=i;
            while(x>=1&&b[x][j]==b[i][j]) --x;
            if(x>=1) road(sum(i,j),sum(x,j),1);
            x=i;
            while(x<=m&&b[x][j]==b[i][j]) ++x;
            if(x<=m) road(sum(i,j),sum(x,j),1);
        }
    }
    for(int r=1;r<=m*n;++r)
    {
        for(int i=1;i<=m*n;++i) f[r][i]=1e9,h[i]=false;
        f[r][r]=0;
        h[r]=true;
        std::queue<int> Q;
        Q.push(r);
        while(!Q.empty()) 
        {
            int k=Q.front();
            Q.pop();
            if(h[k]==false) continue;
            h[k]=false;
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(f[r][k]+a[i].w<f[r][a[i].m])
                {
                    f[r][a[i].m]=f[r][k]+a[i].w;
                    h[a[i].m]=true;
                    Q.push(a[i].m);
                }
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            bool u=false;
            for(int k=1;k<=m;++k)
            {
                for(int l=1;l<=n;++l)
                {
                    if(k!=i&&l!=j&&f[sum(k,l)][])
                }
            }
            if(b[i-1][j]==b[i][j]&&b[i+1][j]==b[i][j]&&b[i][j-1]==b[i][j]&&b[i][j+1]==b[i][j]) continue;
            str(i,j,b[i][j]);
        }
    }
    scanf("%s",d+1);
    q=strlen(d+1);
    d[++q]='*';
    d[0]='#';
    str(1,1,'#');
    for(register int i=1;i<=q;++i)
    {
        register int t=i&1;
        for(register int j=t2[(int)d[i]];j!=0;j=c[j].q)
        {
            register int s=1e9;
            for(register int k=t2[(int)d[i-1]];k!=0;k=c[k].q)
            {
                s=min(s,g[t^1][k]+f[c[k].t][c[j].t]+1);
            }
            g[t][j]=s;
        }
    }
    int s=1e9;
    for(register int i=t2[(int)d[q]];i!=0;i=c[i].q)
    {
        s=min(s,g[q&1][i]);
    }
    printf("%d",s);
    return 0;
}