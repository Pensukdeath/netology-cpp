#include "Calc.h"
#include <cmath>

double Calculator::addition(double num_1, double num_2) {
	return num_1 + num_2;
}
double Calculator::subtraction(double num_1, double num_2) {
	return num_1 - num_2;
}
double Calculator::multiplication(double num_1, double num_2) {
	return num_1 * num_2;
}
double Calculator::division(double num_1, double num_2) {
	return num_1 / num_2;
}
long double Calculator::pow(double num_1, double num_2) {
	return powl(num_1, num_2);
}