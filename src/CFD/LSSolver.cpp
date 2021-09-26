#include "LSSolver.h"

void LSSolver::SolveSparseCRS(std::vector<double>&& x, int nCol, const std::vector<int>& ptr, std::vector<int>& col,
	const std::vector<double>& val, const std::vector<double>& rhs, double& errorOut, int& nItOut, double tol)
{
}

LSSolver::LSSolver()
	:
	cPSolverFPreconditioned(nullptr)
{}
LSSolver::~LSSolver()
{
	if (cPSolverFPreconditioned)
	{
		delete cPSolverFPreconditioned;
		cPSolverFPreconditioned = nullptr;
	}
}

void LSSolver::PrecondtionCRS(int nCol, const std::vector<int>& ptr, std::vector<int>& col,
	const std::vector<double>& val, double tol)
{
	if (cPSolverFPreconditioned)
	{
		delete cPSolverFPreconditioned;
		cPSolverFPreconditioned = nullptr;
	}

	Solver::params prm;
	prm.solver.tol = tol;
	prm.solver.maxiter = 25;
	cPSolverFPreconditioned = new Solver(std::tie(nCol, ptr, col, val), prm);
}

void LSSolver::SolvePreconditionedCRS(std::vector<double>&& x, int nCol, const std::vector<int>& ptr, std::vector<int>& col,
	const std::vector<double>& val, const std::vector<double>& rhs, double& errorOut, int& nItOut)
{
	std::tie(nItOut, errorOut) = (*cPSolverFPreconditioned)(std::tie(nCol, ptr, col, val), rhs, std::move(x));
}

void LSSolver::SolveSparseCRSWithAMG(std::vector<double>&& x, int nCol, const std::vector<int>& ptr, std::vector<int>& col,
	const std::vector<double>& val, const std::vector<double>& rhs, double& errorOut, int& nItOut, double tol)
{
	Solver::params prm;
	prm.solver.tol = tol;

	Solver solve(std::tie(nCol, ptr, col, val), prm);

	std::tie(nItOut, errorOut) = solve(rhs, std::move(x));
}

void LSSolver::SolveTridiagonalDestructive(std::vector<double>& x, const size_t N, const std::vector<double>& a,
	const std::vector<double>& b, std::vector<double>& c)
{
	size_t n;

	/*
	resolve Ax = v onde A � uma matriz tridiagonal composta pelos veores a, b, c
	note que o conte�do do vetor de entrada c ser� modificado, tornando esta uma fun��o de um �nico tempo de uso
	x[] - inicialmente cont�m o vector de entrada v e retorna a solu��o x. indexados por[0, ..., N - 1]
	N - n�mero de equa��es
	a[] - subdiagonal (diagonal abaixo da diagonal principal) -- indexados por [1, ..., N - 1]
	b[] - matriz principal, indexados por [0, ..., N - 1]
	c[] - superdiagonal (diagonal acima da diagonal principal) -- indexedos por [0, ..., N - 2]
	*/

	c[0] = c[0] / b[0];
	x[0] = x[0] / b[0];

	/* loop de 1 a N - 1 inclusive */
	for (n = 1; n < N; n++) {
		double m = 1.0 / (b[n] - a[n] * c[n - 1]);
		c[n] = c[n] * m;
		x[n] = (x[n] - a[n] * x[n - 1]) * m;
	}

	/* loop de N - 2 a 0 inclusive */
	for (n = N - 1; n-- > 0; )
		x[n] = x[n] - c[n] * x[n + 1];
}
