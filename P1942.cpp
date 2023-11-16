#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2001;
int n,m,q,a[N];
char c[N];
int main()
{
    scanf("%d",&n);
    while(cin>>c+1)
    {
        m=strlen(c+1);
        q=0;
        for(int i=1;i<=m;++i)
        {
            a[i]=a[i-1]+c[i]-'0';
            q+=(c[i]-'0')*i;
        }
        if(m==n)
        {
            if(q%(n+1)==0)
            {
                cout<<c+1;
                printf("\n");
                continue;
            }
            bool u=false;
            for(int i=1;i<=n;++i)
            {
                if(c[i]=='1'&&(q-i)%(n+1)==0)
                {
                    c[i]='0';
                    cout<<c+1;
                    printf("\n");
                    u=true;
                    break;
                }
            }
            if(u==false) printf("-1\n");
        }
        else if(m==n-1)
        {
            bool u=false;
            for(int i=1;i<=n;++i)
            {
                if((q+(a[n-1]-a[i-1]))%(n+1)==0)
                {
                    for(int j=1;j<=i-1;++j)
                    {
                        printf("%c",c[j]);
                    }
                    printf("0");
                    for(int j=i;j<=n-1;++j)
                    {
                        printf("%c",c[j]);
                    }
                    printf("\n");
                    u=true;
                    break;
                }
                else if((q+i+(a[n-1]-a[i-1]))%(n+1)==0)
                {
                    for(int j=1;j<=i-1;++j)
                    {
                        printf("%c",c[j]);
                    }
                    printf("1");
                    for(int j=i;j<=n-1;++j)
                    {
                        printf("%c",c[j]);
                    }
                    printf("\n");
                    u=true;
                    break;
                }
            }
            if(u==false) printf("-1\n");
        }
        else if(m==n+1)
        {
            bool u=false;
            for(int i=1;i<=n+1;++i)
            {
                if((q-(c[i]-'0')*i-(a[n+1]-a[i]))%(n+1)==0)
                {
                    for(int j=1;j<=i-1;++j)
                    {
                        printf("%c",c[j]);
                    }
                    for(int j=i+1;j<=n+1;++j)
                    {
                        printf("%c",c[j]);
                    }
                    printf("\n");
                    u=true;
                    break;
                }
            }
            if(u==false) printf("-1\n");
        }
    }
    return 0;
}