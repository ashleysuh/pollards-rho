# pollards-rho
Short implementation of the Pollard's Rho algorithm

User can enter any long int 'N', an int 'c' for the polynomial x^2 + c, and an int 'x' which is our initial guess x_0. 
pollardsRhoMethod(long int,int,int) will calculate the first pair of prime factors for N, or return 1 if N is not factorable (likely because N is prime). 

The pollardsRhoMethod() function uses gcd(int,int), which was a direct reflection of the wikipedia article using Euclid's algorithm. 
