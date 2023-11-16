#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n;
char a[N],b[N],c[N],h[N];
void solve1()
{
    for(int i=1;i<=26;++i) h[i]=0;
    b[n+1]='\0';
    for(int i=1;i<=n;++i) ++h[a[i]-'a'+1];
    int x=0,x1=0,x2=0;
    for(int i=1;i<=26;++i)
    {
        if(h[i]==0) continue;
        if(x1==0)
        {
            while(h[i]>=2)
            {
                h[i]-=2;
                ++x;
                b[x]=b[n-x+1]=i+'a'-1;
            }
            if(h[i]%2==1) x1=i;
        }
        else
        {
            x2=i;
            break;
        }
    }
    if(x1!=0&&x2!=0)
    {
        ++x;
        b[x]=x2+'a'-1,b[n-x+1]=x1+'a'-1;
        --h[x1],--h[x2];
        for(int i=1;i<=26;++i)
        {
            while(h[i]>=1)
            {
                --h[i];
                b[++x]=i+'a'-1;
            }
        }
    }
    else if(x1!=0)
    {
        b[++x]=x1+'a'-1;
    }
}
void solve2()
{
    for(int i=1;i<=26;++i) h[i]=0;
    c[n+1]='\0';
    for(int i=1;i<=n;++i) ++h[a[i]-'a'+1];
    int x=0,x1=0,x2=0;
    for(int i=1;i<=26;++i)
    {
        while(h[i]>=2)
        {
            h[i]-=2;
            ++x;
            c[x]=c[n-x+1]=i+'a'-1;
        }
        if(h[i]==1) x1=x2,x2=i;
        if(x1!=0) break;
    }
    if(x1!=0&&x2!=0)
    {
        ++x;
        c[x]=x2+'a'-1,c[n-x+1]=x1+'a'-1;
        --h[x1],--h[x2];
        for(int i=1;i<=26;++i)
        {
            while(h[i]>=1)
            {
                --h[i];
                c[++x]=i+'a'-1;
            }
        }
    }
    else if(x2!=0)
    {
        c[++x]=x2+'a'-1;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        solve1();
        solve2();
        if(strcmp(b+1,c+1)<0) printf("%s\n",b+1);
        else printf("%s\n",c+1);
    }
    return 0;
}