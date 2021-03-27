#include <iostream>
#include <cmath>

using fptr = double(double);
//double bisection(double xl, double xu, double eps, fptr f, int itermax);
double regulafalsi(double xl, double xu, double eps, fptr f, int itermax);
//double fixedpoint(double x0, double eps, fptr f, fptr g, int itermax);
double fun(double x);
double gaux(double x);
void error_itermax(double xr, double fxr, int itermax);

const double c = 6.9854; /*Debido a como se hizo el código, es por ello que no introduje un vector*/
const double R = 8.31; /*J.K^{-1}.mol^{-1}*/
const double T = 77; /*Kelvin*/


int main(void)
{
  std::cout.precision(15); std::cout.setf(std::ios::scientific);

  const double EPS = 1.0e-8;
  const int ITERMAX = 10000;


  double root = 0.0;
  root = regulafalsi(100, 200, EPS, fun, ITERMAX);
  std::cout << "\n \n" << "c" << "\t \t \t" << "T_E" <<  "\t \t \t" << "comprobación \n";
  std::cout << c << "\t" <<root << "\t" << fun(root) <<  "\n";


  return 0;
}


double regulafalsi(double xl, double xu, double eps, fptr f, int itermax)
{
  double xr = xl;
  int iter = 0;
  while(1) {
    xr = xu - (f(xu)*(xl-xu))/(f(xl) -f(xu));
    if (std::fabs(f(xr)) <= eps) {
      break;
    }
    else if (f(xr)*f(xl) < 0) {
      xu = xr;
    }
    else {
      xl = xr;
    }
    iter++;
    if (iter > itermax) {
      error_itermax(xr, f(xr), itermax);
      break;
    }
  }
  std::cout << "# regula falsi niter = " << iter << "\n";

  return xr;
}

double fun(double x)
{
    double X = x/T;
    double ex = std::exp(X);
    double d = ex-1;
  return c-(3*R*X*X*(ex/(d*d)));
}

void error_itermax(double xr, double fxr, int itermax)
{
  std::cerr << "############################################\n";
  std::cerr << "# ERROR: max number of iterations reached.\n";
  std::cerr << "# itermax = " << itermax << "\n";
  std::cerr << "# xr = " << xr << "\n";
  std::cerr << "# f(xr) = " << fxr << "\n";
  std::cerr << "############################################\n";
}
