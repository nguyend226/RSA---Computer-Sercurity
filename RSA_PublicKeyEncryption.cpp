#include <iostream>
#include <fstream>
using namespace std;

bool verifyPrimes(int prime)
{
    fstream inFile;
    inFile.open("C:\\Users\\datnt\\source\\repos\\RSA\\PrimesTo10000.txt");
            bool primeFound = false;

    if (inFile.is_open())
    {

        int tempPrime;
        while (!primeFound && inFile.good())
        {
            inFile >> tempPrime;
            if (tempPrime == prime)
                primeFound = true;
        }
        inFile.close();
    }
    else{ cout << "Error: Prime file not found." << endl; }

    return primeFound;
}

int gcd(int a, int b)
{
    int r;
    while (b > 0)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int gcd_extendedEuclidian(int num1, int num2, int *x, int *y)
{
    if (num1 == 0)
    {
        *x = 0, *y = 1;
        return num2;
    }

    int x1;
    int y1;
    int gcd = gcd_extendedEuclidian(num1%num2, num1, &x1, &y1);

    *x = y1 - (num2 / num1) * x1;
    *y = x1;

    return gcd;
}

int getExtendedGcd(int a, int b)
{
    for (int i = 1; i < b; i++)
        if (((a % b) * (i % b)) % b == 1)
            return i;
}

int main()
{
    cout << "Enter the first prime number in range [5000, 10000]: ";
    int prime1;
    cin >> prime1;
    while (prime1 < 5000 || prime1 > 10000 || !verifyPrimes(prime1))
    {
        cout << "Error: Number invalid." << endl;
        cout << "Re-enter prime number: ";
        cin >> prime1;
    }

    cout << "Enter the second prime number in range [5000, 10000]: ";
    int prime2;
    cin >> prime2;
    while (prime2 < 5000 || prime2 > 10000 || !verifyPrimes(prime2))
    {
        cout << "Error: Number invalid." << endl;
        cout << "Re-enter prime number: ";
        cin >> prime2;
    }

    //Calculate n and totient
    int n = prime1 * prime2;
    int totient = (prime1 - 1) * (prime2 - 1);

    //Calculate e
    int e = 2;
    while (e < totient && gcd(e, totient) != 1)
        e++;

    
    //Calculate d
    int k = 2; // can be any value
    int d = getExtendedGcd(e, totient);

    //Print Results
    cout << endl << "Prime 1, p: " << prime1 << endl;
    cout << "Prime 2, q: " << prime2 << endl;
    cout << "n: " << n << endl;
    cout << "Phi: " << totient << endl;
    cout << "e: " << e << endl;
    cout << "d: " << d << endl;
    cout << "d^-1 mod(phi): " << getExtendedGcd(d, totient) << endl;
    cout << "Since (e) and the inverse modulus of d over phi are the same, " << endl;
    cout << "d and e are multiplicitive inverses with resect to phi." << endl << endl;
	system("pause");
}