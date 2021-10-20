int Solution::threeSumClosest(vector<int> &A, int B) {
    sort(A.begin(),A.end());
    long long bestsum=1e9,mindiff=1e9,n=A.size();
    for(int i=0;i<A.size();i++){
        int l=i+1,r=n-1;
        while(l<r){
            long long sum=A[i]+A[l]+A[r];
            if(abs(sum-B)<mindiff){
                mindiff=abs(sum-B);
                bestsum=sum;
            }
            if(sum>B)r--;
            else l++;
        }
    }
    return bestsum;
}
