#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;


int main() {
   double r1 = 1, r2 = 1, n1 = 1, n2 = 1, k1 = 200, k2 = 100, dn1, dn2, tmax, dt, t, alpha, beta;

   cout << "Enter the time limit, time's starting point and step size: ";
   cin >> tmax >> t >> dt;
   cout << "Enter alpha and beta: ";
   cin >> alpha >> beta;

   clock_t tStart = clock();

   ofstream dataFile("Euler.data");

   dn1 = dt * r1 * n1 * (1 - (n1 + alpha * n2) / k1);
   dn2 = dt * r2 * n2 * (1 - (n2 + beta * n1) / k2);
   

   while (t < tmax || n1 >= k1 || n2 >= k2) {

       t += dt;
       n1 += dn1;
       n2 += dn2;

       dn1 = dt * r1 * n1 * (1 - (n1 + alpha * n2) / k1);
       dn2 = dt * r2 * n2 * (1 - (n2 + beta * n1) / k2);

       dataFile << t << ' ' << n1 << ' ' << n2 << '\n';

   }

   dataFile.close();

   cerr << "Time elapsed for Euler method: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " s" << endl;

}