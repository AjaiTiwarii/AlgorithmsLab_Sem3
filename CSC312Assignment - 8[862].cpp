#include <iostream>
#include <cmath>

using namespace std;

long long power(long s) {
    long long result = 1;
    for (int i = 0; i < s; i++) {
        result *= 10;
    }
    return result;
}

long numlen(long t) {
    long length = 0;
    while (t > 0) {
        length++;
        t /= 10;
    }
    return length;
}

long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) {
        return x * y;
    }

    long n = max(numlen(x), numlen(y));
    long n2 = n / 2;

    long long x1 = x / power(n2);
    long long x2 = x % power(n2);
    long long y1 = y / power(n2);
    long long y2 = y % power(n2);

    long long x1y1 = karatsuba(x1, y1);
    long long x2y2 = karatsuba(x2, y2);
    // long long ad_bc = karatsuba(a + b, c + d) - ac - bd;/
    long long x1y2_x2y1 = x1y1 + x2y2 - karatsuba(x1 - x2, y1 - y2);

    return x1y1 * power(2 * n2) + x1y2_x2y1 * power(n2) + x2y2;
}

int main() {
    // long long a = 1234567890123;
    long long a = 1000;
    // long long b = 45678912345670;
    long long b = 2000;

    long long answer = karatsuba(a, b);

    cout << "Multiplication result: " << answer  << endl;

    return 0;
}


