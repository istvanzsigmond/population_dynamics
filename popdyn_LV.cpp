#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;


int main() {
   double nR = 500, nF = 500, dnR, dnF, tmax, dt, t, a, b, c, d;

   cout << "Enter the time limit, time's starting point and step size: ";
   cin >> tmax >> t >> dt;
   cout << "Enter the values of a, b, c, d: ";
   cin >> a >> b >> c >> d;

   clock_t tStart = clock();

   ofstream dataFile("LVEuler.data");

   dnR = dt * (a * nR - b * nF * nR);
   dnF = dt * (c * nF * nR - d * nF);
   

   while (t < tmax) {

       t += dt;
       nR += dnR;
       nF += dnF;

       dnR = dt * (a * nR - b * nF * nR);
       dnF = dt * (c * nF * nR - d * nF);

       dataFile << t << ' ' << nR << ' ' << nF << '\n';

   }

   dataFile.close();

   cerr << "Time elapsed for Euler method: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " s" << endl;

}