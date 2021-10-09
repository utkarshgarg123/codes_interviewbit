#include <bits/stdc++.h>
using namespace std;

vector<long long> secrets;
vector<long long> primes;

long long get_random_number(long long mn, long long mx)
{
    long long ret = mn + (rand() % mx);
    return ret;
}

vector<long long> sieve()
{
    vector<bool> isPrm(10001, true);
    vector<long long> ret;

    for (int i = 2; i * i <= 10000; i++)
    {
        if (isPrm[i] == true)
        {

            for (int j = i * i; j <= 10000; j += i)
                isPrm[j] = false;
        }
    }

    for (int i = 2; i <= 10000; i++)
    {
        if (isPrm[i] == true)
            ret.push_back(i);
    }

    return ret;
}

long long get_random_prime_number()
{
    int m = primes.size();

    int indx = rand() % m;

    return primes[indx];
}

long long get_GCD(long long a, long long b)
{
    while (a != 0)
    {
        long long c = a;
        a = b % a;
        b = c;
    }
    return b;
}

int get_coprime(long long n)
{
    int coprime = n;

    while (get_GCD(n, coprime) != 1)
    {
        coprime = get_random_number(1, n);
    }

    return coprime;
}

int main()
{
    secrets.clear();
    primes.clear();
    primes = sieve();

    char ch;
    cout << "Run the code for intruder(I)/prover(P): ";
    cin >> ch;
    cout << endl;
    long long t, k, n, count = 0;

    cout << "Enter the key size (k): ";
    cin >> k;
    cout << "Enter the number of challenges (t): ";
    cin >> t;
    cout << endl;

    // Generating two agreed upon prime numbers
    int p = get_random_prime_number();
    int q = get_random_prime_number();

    cout << "The generated prime numbers: " << p << " " << q << endl;

    // n is the product of two agreed upon prime numbers
    n = (long long)p * (long long)q;
    cout << "The value of n is: " << n << endl;
    cout << endl;

    // getting the secret keys
    for (int i = 0; i < k; i++)
    {
        int s = get_coprime(n);
        secrets.push_back(s);
    }

    cout << "The secret keys of the prover: ";
    for (int i = 0; i < k; i++)
        cout << secrets[i] << " ";
    cout << endl;
    cout << endl;

    // checking for 't' challenges
    for (int j = 0; j < t; j++)
    {
        // choosing a random number from 1 to n-1
        long long r = 1 + (rand() % (n - 1));

        // calculate (r^2)%n
        long long x = ((r % n) * (r % n)) % n;

        vector<long long> challenges(k);
        cout << "[Verifier] Enter the challenges: ";
        for (int i = 0; i < k; i++)
            cin >> challenges[i];

        //  Calculating  y1 = (r * ((secrets[0]^challenges[0]) * (secrets[1]^challenges[1]) ... (secrets[k-1]^challenges[k-1]))) % n
        long long y1;
        y1 = r % n;
        for (int i = 0; i < k; i++)
        {
            long long temp = pow(secrets[i], challenges[i]);
            temp %= n;
            y1 = ((y1 % n) * (temp % n)) % n;
        }

        // Calculating v[i] = (secrets[i]^2)%n
        vector<long long> v(k);
        for (int i = 0; i < k; i++)
            v[i] = ((secrets[i] % n) * (secrets[i] % n)) % n;

        //  Calculating  y = (x * ((v[0]^challenges[0]) * (v[1]^challenges[1]) ... (v[k-1]^challenges[k-1]))) % n
        long long y;
        y = x % n;
        for (int i = 0; i < k; i++)
        {
            long long temp = pow(v[i], challenges[i]);
            temp %= n;
            y = ((y % n) * (temp % n)) % n;
        }

        // y2 = (y1^2) % n
        long long y2 = ((y1 % n) * (y1 % n)) % n;

        // This is the case when there is an Intruder
        if (ch == 'I')
            y = 1 + (rand() % (n - 1));

        // If (y1^2)%n is equal to the y that peggy sent then challenge passed
        if (y2 == y)
        {
            cout << "challenge PASSED" << endl;
            count++;
        }
        else
        {
            cout << "challenge FAILED" << endl;
        }
        cout << endl;
    }
    if (count == t)
        cout << "SUCESSFULL AUTHENTICATION" << endl;
    else
        cout << "UNSUCESSFULL AUTHENTICATION" << endl;
}
