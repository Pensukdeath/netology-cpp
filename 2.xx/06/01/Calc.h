#pragma once
class Calculator{
public:
	double num_1;
	double num_2;

	double addition(double num_1, double num_2);
	double subtraction(double num_1, double num_2);
	double multiplication(double num_1, double num_2);
	double division(double num_1, double num_2);
	long double pow(double num_1, double num_2);
};