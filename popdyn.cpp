#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

#include "vector.hpp"
#include "odeint.hpp"
using namespace cpl;

Vector f(const Vector& x) {

    double t = x[0], Xa = x[1], r = 1;
    Vector f(2);
    f[0] = 1;
    f[1] = r * Xa * (1 - Xa);

return f;
}

int main() {
   double r = 1, X0 = 0.1, dx, X, tmax, dt, t, accuracy;

   cout << "Enter the time limit, time's starting point and step size: ";
   cin >> tmax >> t >> dt;
   cout << "Accuracy for adaptive method: ";
   cin >> accuracy;

   clock_t tStart = clock();

   ofstream dataFile("euler.data");

   dx = dt * r * X0 * (1 - X0);
   X = X0 / (X0 + (1 - X0) * exp(-r * t));

   while (t < tmax || X0 >= 1) {

       t += dt;
       X0 += dx;

       dx = dt * r * X0 * (1 - X0);

       X = X0 / (X0 + (1 - X0) * exp(-r * t));

       dataFile << t << ' ' << X0 << ' ' << X << '\n';

   }

   dataFile.close();

   cerr << "Time elapsed for Euler method: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " s" << endl;

   clock_t tStart2 = clock();

   dataFile.open("adaptive.data");

   Vector x0(2);
   x0[0] = 0, x0[1] = 0.1;

   Vector x = x0;

   do {
       for (int i = 0; i < 2; i++) {
           dataFile << x[i] << '\t';
       }
       dataFile << '\n';

       adaptiveRK4Step(x, dt, accuracy, f);
       
   } while (x[0] < tmax || x[1] >= 1);

   dataFile.close();

   cerr << "Time elapsed for adaptiveRK4 method: " << (double)(clock() - tStart2)/CLOCKS_PER_SEC << " s" << endl;
}