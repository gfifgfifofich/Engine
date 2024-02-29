#include <iostream>


int Facorial(int a)
{
	if (a == 0)
		return 1;
	int n = 1;
	
	for (int i = 1; i <= a; i++)
		n *= i;
	return n;
}
int C(int a, int b)
{
	return Facorial(b) / (Facorial(a) * Facorial(b - a));
}


int main()
{
	float p = 0.35f;
	float q = 1.0f-p;
	int n = 8;
	float sum = 0.0f;
	for (int i = 0; i <= n; i++)
	{
		int c = C(i, n);
		float pn = c * pow(p, i) * pow(q, n - i);
		sum += pn;
		std::cout << c << "	p"<<i<<"= " << pn << "\n";
	}
	std::cout << "sum = " << sum;
	return 0;
}