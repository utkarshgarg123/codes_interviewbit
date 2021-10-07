int Solution::solve(vector<int> &a, int B){
    int sum=0;
    for(int i=0;i<B;i++)sum+=a[i];
    int ans=sum;
    int n=a.size();
    for(int i=n-1;i>=n-B;i--){
        sum+=a[i]-a[i-n+B];
        ans=max(ans,sum);
    }
    return ans;
}