#include <stdio.h>
#include <stdlib.h>
#include <math.h>



class QuadraticSolver
{
protected:
    double a, b, c;
    double r[2];
public:
    void SetCoefficients(double &a, double &b, double &c);
    int Solve(void);
    void GetRoots(double m, double n);
};


void QuadraticSolver::SetCoefficients(double &A, double &B, double &C)
{
    a=A;
    b=B;
    c=C;
}

int QuadraticSolver::Solve()
{
    r[0]=(-b+sqrt(b*b-4*a*c))/(2*a);
    r[1]=(-b+sqrt(b*b-4*a*c))/(2*a);
    if((b*b-4*a*c)<0)
    {
        return 0;
    }
    else return 1;
}

void QuadraticSolver::GetRoots(double m, double n)
{
    m=r[0];
    n=r[1];
}


int main(void)
{
	double a,b,c;

	char str[256];
	printf("a>");
	fgets(str,255,stdin);
	a=atof(str);

	printf("b>");
	fgets(str,255,stdin);
	b=atof(str);

	printf("c>");
	fgets(str,255,stdin);
	c=atof(str);

	QuadraticSolver solver;
	solver.SetCoefficients(a,b,c);
	if(0!=solver.Solve())
	{
		double x1,x2;
		solver.GetRoots(x1,x2);
		printf("Roots=%lf, %lf\n",x1,x2);
	}
	else
	{
		printf("No real roots.\n");
	}
	return 0;
}
