#include <random>
#include <iostream>
#include <cstdlib>
using namespace std;
int generateRandomNumber(int);
int getPrimeNumber();
int modInverse(int, int);
int gcd(int, int);
int power(int, int, int);
void generateKeys(int&, int&, int&);
int encrypt(int, int, int);
int decrypt(int, int, int);
int main(int argc, char* argv[])
{
    int e, d, n;
    generateKeys(e, d, n);
    
    int message = 15203;

    int c = encrypt(message, e, n);

    int decrypted = decrypt(c, d, n);

    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";
    cout << "Original Message: " << message << endl;
    cout << "Encrypted Message: " << c << endl;
    cout << "Decrypted Message: " << decrypted << endl;
    return 0;
}

int encrypt(int m, int e, int n)
{
    return power(m, e, n);
}

int decrypt(int c, int d, int n)
{
    return power(c, d, n);
}

void generateKeys(int &e, int&d, int&n) // pointers to variables in main
{
    int p = getPrimeNumber();
    int q = getPrimeNumber();
    n = p * q;

    int phi = (p - 1) * (q - 1); 

    for (e = 2; e < phi; e++)
    {
        if (gcd(e, phi) == 1)
        {
            break;
        }
    }

    d = modInverse(e,phi);
    
}



int modInverse(int e, int phi)
{
    for (int d = 2; d < phi; d++)
    {
        if ((e * d) % phi == 1)
        {
            return d;
        }
    }
    return -1;
}
int generateRandomNumber(int upperBound)
{
    // thanks to https://www.w3schools.com/cpp/cpp_howto_random_number.asp 
    srand( rand()); // random seed
    int randomnum = rand() % upperBound; // random number from 0 to upper bound
    return randomnum;
}

int getPrimeNumber() // this is incredibly slow, need to find quicker way to do this
{
    bool prime = false;
    while (!prime)
    {
        int n = generateRandomNumber(15000);
        if (n % 2 == 0)
        {
            n += 1; // make number odd
        }
        if (n < 2)
        {
            continue; // skip if number is 1
        }
        for (int i = 2; i < n; i++) // loop through all numbers up to n and check if prime
        {
            if (n % i == 0) // checking if there is a divisor
            {
                prime = false; 
                break; // no need to check rest of the numbers just generate new number
            }
            prime = true; // if no divisor n = prime
        }
        if (prime == true)
        {
            return n;
        }
    }
}

int gcd(int a, int b)
{
    if (a==0)
    {
        return b;
    }
    return gcd(b % a, a);
}

int power(int base, int exp, int mod)
{
    int result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result = (result * 1LL * base) % mod;
        }
        base = (base * 1LL * base) % mod;
        exp = exp / 2;
    }
    return result;
}