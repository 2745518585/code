#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2001;
int n,a[N],b[N];
vector<pair<int,int>> ans;
void solve(int n)
{
    int x=n;
    auto move0=[&]()
    {
        ans.push_back(make_pair(3,1));
        x=(x+1)%n+1;
    };
    auto move1=[&]()
    {
        ans.push_back(make_pair(2,1));
        swap(a[x],a[x%n+1]);
        x=x%n+1;
    };
    auto move2=[&]()
    {
        ans.push_back(make_pair(2,3));
        swap(a[x],a[x%n+1]);
        x=(x-2+n)%n+1;
    };
    for(int i=n;i>=1;--i)
    {
        if(a[i]==i) continue;
        if(n%2==0)
        {
            while(a[x]!=i&&a[x%n+1]!=i) move0();
            if(a[x%n+1]==i)
            {
                while(x!=n) move2();
                move0();
                move2();
            }
        }
        else
        {
            while(a[x]!=i) move0();
        }
        while(x<i) move1();
    }
    while(x!=n) move0();
    printf("%d\n",n-2);
    printf("%d\n",ans.size());
    for(auto i:ans) printf("%d %d\n",i.first,i.second);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        ans.clear();
        if([&](){
            for(int i=1;i<=n;++i) if(a[i]!=i) return false;
            return true;
        }())
        {
            printf("%d\n",n);
            printf("0\n");
            continue;
        }
        if([&](){
            for(int i=1;i<=n;++i) if((a[i]-i+n)%n!=(a[1]-1+n)%n) return false;
            return true;
        }())
        {
            printf("%d\n",n-1);
            printf("%d\n",a[1]-1);
            for(int i=1;i<=a[1]-1;++i)
            {
                printf("%d %d\n",1,2);
            }
            continue;
        }
        if(n%2==1) solve(n);
        else
        {
            int s=0;
            for(int i=1;i<=n;++i)
            {
                for(int j=i+1;j<=n;++j)
                {
                    if(a[i]>a[j]) ++s;
                }
            }
            if(s%2==0) solve(n);
            else
            {
                int x=0;
                while(a[x]!=n) ++x;
                auto move=[&](int x,int y)
                {
                    static int b[N];
                    int q=0;
                    for(int i=1;i<=n;++i)
                    {
                        if(i<x||i>x+(n-3)-1) b[++q]=a[i];
                    }
                    for(int i=x;i<=x+(n-3)-1;++i) b[n+i-x+1]=a[i];
                    q=0;
                    for(int i=1;i<=n;++i)
                    {
                        if(i>=y&&i<=y+(n-3)-1) a[i]=b[n+i-y+1];
                        else a[i]=b[++q];
                    }
                    ans.push_back(make_pair(x,y));
                };
                if(x<=2) move(x,3);
                while(a[n]!=n) move(3,4);
                solve(n-1);
            }
        }
    }
    return 0;
}