/*************************************************************************************************
 * Author: Ashley Suh										                                                         *
 * Date: 12/1/16										                                                             *
 * Class: MAD 4471 - Cryptography and Coding Theory					                                     *
 * Project: Pollard's Rho Method						                                                		 *
 * 												                                                                       *
 * Let p|N, if P(x) = P(y)mod p, then p|(x-y)(x+y) and gcd(N, x-y) = p.				                   *
 * Pollard's Rho is an algorithm to calculate the collisions of modulo p for p|N. 	          	 *
 * Since there are less values of P(x)mod p than P(x)mod N, our algorithm is more efficient	     *
 * than hard computing prime factors of N which break the RSA cryptosystem. Runtime is sqrt(N)	 *
 *************************************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int gcd(int, int); // calculates greatest common divisor
int pollardsRhoMethod(long int, int, int); // finds the prime factors of N

int main (void) {

	
	/* Can easily switch to N,x, and c being read from command line if preferred */
	long int N; // RSA number
	int c, x; // c is the arbitrary int of x^2 + c, x is our initial guess

	cout << "Enter a number N to factor: ";
	cin >> N;
	cout << "Enter a number c for the polynomial P = (x^2 + c): ";
	cin >> c;
	cout << "Enter a value x for x_0 : ";
	cin >> x;

	cout << "You entered N = " << N << ", P = (x^2 + " << c
		<< ") and x_0 = " << x << endl;

	int p = pollardsRhoMethod(N, c, x); // first prime factor of N using Pollard's Rho Method
	int q = N / p; // second prime factor of N
	cout << "N has the prime factors " << p << " and " << q << endl;

	return 0;
}

int gcd(int a, int b) {
	int c = a % b; // find the initial remainder of first int and second int

	while (c != 0) { // loops until remainder = 0
		a = b; // after first iteration, a copies previous c_(i-1) value
		b = c; // b copies the c_i value
		c = a % b; // c_i+1 is now the remainder of a / b
	}
	/* example from wikipedia: Euclid's algorithm--
		compute gcd(48, 18) -->
		begin loop, stop when c = 0, then return b:
		a = 48, b = 18, c = 48 % 18 = 12
		a = 18, b = 12, c = 18 % 12 = 6
		a = 12, b = 6,  c = 12 % 6  = 0
		ends loop, returns b = 6 */

	return b; // b is the greatest common divisor
}

int pollardsRhoMethod (long int rsa, int cVal, int xVal) {
	int primeFactor; // value of prime factor
	int k = 0; // index value for vector
	vector<int> currentValue; // vector of ints to store |x_i - x_2i|

	for (int i = 0; i < sqrt(rsa); i++) { // runtime of algorithm is sqrt(N) else failed

		// calculate x_(i) : (x^2 + c) * mod N
		int xCurrent = ( ((xVal * xVal) + cVal) % rsa );

		// store value into the vector to use it during all loop iterations
		currentValue.push_back(xCurrent);

		// calculate x_(i+1)
		int xNext = ( ((xCurrent * xCurrent) + cVal) % rsa );

		// stores next value into the vector
		currentValue.push_back(xNext);

		// access the first value in the vector, then increment each instance
		int myValue = currentValue.at(k++);

		// find the absolute value : |x_(i) - x_2i|
		int difference = abs(myValue - xNext);

		// set the next instance of initialX to the previous value
		xVal = xNext;

		// calculate the greatest common divisor between difference & N
		primeFactor = gcd(difference, rsa);

		// if our prime factor is nontrivial, return the value
		if (primeFactor != 1 && primeFactor != rsa)
			return primeFactor;
	}

	cout << "N could not be factored." << endl; // prime factorization failed

	return 1; // N can only be factored as p = 1 and q = N
}
