class Solution {
public:
    long long fib(long long n, long long &next) {
        if (n == 0) {
            next = 1;
            return 0;
        }
        long long next2;
        long long a = fib(n/2, next2);
        long long b = next2;
        long long c = a * (2 * b - a + 1000000007) % 1000000007;
        long long d = (a * a + b * b) % 1000000007;
        if(n % 2 == 0) {
            next = d;
            return c;
        }
        next = (c + d) % 1000000007;
        return d;
    }
    int countGoodStrings(long long n) {
        long long next;
        long long ans = fib(n, next);
        return (2 * ans) % 1000000007;
    }
};