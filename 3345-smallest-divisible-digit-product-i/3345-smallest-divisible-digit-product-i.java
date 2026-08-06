class Solution {
    public int smallestNumber(int n, int t) {
        while(true){
            if(digitSum(n)%t==0)return n;
            n++;
        }
    }
    public static int digitSum(int n){
        int sum=1;
        while(n>0){
            sum*=(n%10);
            n/=10;
        }
        return sum;
    }
}