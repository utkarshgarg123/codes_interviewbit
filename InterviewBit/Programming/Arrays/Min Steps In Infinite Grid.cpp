int Solution::coverPoints(vector<int> &a, vector<int> &b){
    int ans=0;
    for(int i=0;i<a.size()-1;i++){
        int x=abs(a[i]-a[i+1]);
        int y=abs(b[i]-b[i+1]);
        ans+=max(x,y);
    }
    return ans;
}
