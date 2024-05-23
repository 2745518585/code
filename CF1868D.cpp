#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,a[N];
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
        int s=0;
        for(int i=1;i<=n;++i)
        {
            s+=a[i];
            if(s>n*2) break;
        }
        if(s!=n*2)
        {
            printf("No\n");
            continue;
        }
        s=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==2) ++s;
        }
        if(s==n)
        {
            printf("Yes\n");
            for(int i=1;i<=n;++i)
            {
                printf("%d %d\n",i,i%n+1);
            }
            continue;
        }
        if(s==0)
        {
            printf("Yes\n");
            vector<int> p;
            for(int i=1;i<=n;++i)
            {
                if(a[i]>2)
                {
                    if(!p.empty()) printf("%d %d\n",p.back(),i);
                    for(int j=1;j<=a[i]-2;++j) p.push_back(i);
                }
            }
            printf("%d %d\n",p.back(),p.front());
            for(int i=1;i<=n;++i)
            {
                if(a[i]==1)
                {
                    printf("%d %d\n",p.back(),i);
                    p.pop_back();
                }
            }
            continue;
        }
        int x=0,y=0,z=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]>2)
            {
                if(a[i]>a[x]) z=y,y=x,x=i;
                else if(a[i]>a[y]) z=y,y=i;
                else if(a[i]>a[z]) z=i;
            }
        }
        vector<int> p,q,v;
        for(int i=1;i<=n;++i)
        {
            if(a[i]>=2)
            {
                if(i!=x&&i!=y&&i!=z) p.push_back(i);
                v.push_back(i);
            }
            else q.push_back(i);
        }
        if(x==0||y==0)
        {
            printf("No\n");
            continue;
        }
        if(v.size()%2==1&&(a[x]==3||v.size()-2<=1)&&(z==0||v.size()-2<=3))
        {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
        printf("%d %d\n",x,y);
        printf("%d %d\n",y,x);
        a[x]-=2,a[y]-=2;
        auto add=[&](int x)
        {
            printf("%d %d\n",x,p.back());
            --a[x],--a[p.back()];
            int z=p.back();
            p.pop_back();
            return z;
        };
        if(v.size()%2==1)
        {
            if(a[x]>=2)
            {
                if(z) p.push_back(z);
                add(x);
            }
            else
            {
                printf("%d %d\n",x,z);
                --a[x],--a[z];
                add(z);
                x=add(z);
                y=add(y);
                y=add(y);
            }
        }
        else if(z) p.push_back(z);
        while(!p.empty())
        {
            x=add(x);
            y=add(y);
        }
        for(auto i:v)
        {
            for(int j=1;j<=a[i];++j) p.push_back(i);
        }
        for(auto i:q)
        {
            printf("%d %d\n",p.back(),i);
            p.pop_back();
        }
    }
    return 0;
}