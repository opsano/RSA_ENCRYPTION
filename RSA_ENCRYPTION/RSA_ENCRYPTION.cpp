#include <random>
#include <iostream>
#include <cstdlib>
using namespace std;
int generateRandomNumber(int);
int getPrimeNumber();
int eulerTotientFunction(int);
int main(int argc, char* argv[])
{
    int p = getPrimeNumber();
    int q = getPrimeNumber();
    int product = p * q;
    int euler = eulerTotientFunction(product);
    int exponent = generateRandomNumber(euler);

    cout << p << " " << q << " " << product << " " << euler << endl;

    return 0;
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

int eulerTotientFunction(int n)
{
    int result = 1;
    for (int i = 2; i < n; i++)
    {
        if (gcd(i,n) == 1)
        {
            result++;
        }
    }
    return result;
}