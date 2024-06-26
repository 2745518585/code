#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e6+50,mod=998244353,ba=29;

int n,h[N],mi[N],f[N],ans[N],mx;
char s[N],t[N]; 

int find(int l,int r)
{
    if(l>r)return 0;
    return (h[r]-h[l-1]*mi[r-l+1]%mod+mod)%mod;
}

int find(int l1,int r1,int l2,int r2)
{
    int len=0,l=1,r=r1-l1+1;
    while(l<=r)
    {
        int md=(l+r)>>1;
        if(find(l1,l1+md-1)==find(l2,l2+md-1))len=md,l=md+1;
        else r=md-1;
    }
    return len;
}

void chk(int x,int w)
{
    ans[x]=max(ans[x],w);
}

main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    cin>>(s+1)>>(t+1);
    n=strlen(s+1);mi[0]=1;
    for(int i=1;i<=n;i++)mi[i]=mi[i-1]*ba%mod,s[i]-='a',t[i]-='a',h[i]=(h[i-1]*ba+s[i])%mod;
    for(int i=1;i<n;i++)
    {
        chk(i,f[min(i-1,n-i)]);
        f[i]=mx;
        int a=find(1,i),b=find(n-i+1,n);
        if(a==b){f[i]=mx=i;continue;}
        int pos=find(1,i,n-i+1,n)+1,len=i-pos,p1=pos,p2=n-len;
        if(find(pos+1,i)==find(n-len+1,n))
        {
            if(p1<n-i+1&&t[p1]==s[p2])chk(p1,i);
            if(p2>i&&t[p2]==s[p1])chk(p2,i);
            continue;
        }
        int p3=n-i+p2;
        if(find(p1+1,p2-1)==find(p2+1,p3-1)&&find(p2+1,i)==find(p3+1,n)&&s[p1]==t[p2]&&t[p2]==s[p3])chk(p2,i);
    }
    for(int i=1;i<=n;i++)
    {
        if(s[i]==t[i])ans[i]=max(ans[i],mx);
        cout<<ans[i]<<'\n';
    }
}