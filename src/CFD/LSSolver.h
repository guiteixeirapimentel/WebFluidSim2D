#pragma once

#define AMGCL_NO_BOOST
#include "../../external/AMGCL/amgcl/make_solver.hpp"
#include "../../external/AMGCL/amgcl/solver/bicgstab.hpp"
#include "../../external/AMGCL/amgcl/amg.hpp"
#include "../../external/AMGCL/amgcl/coarsening/smoothed_aggregation.hpp"
#include "../../external/AMGCL/amgcl/relaxation/spai0.hpp"
#include "../../external/AMGCL/amgcl/adapter/crs_tuple.hpp"

#include "../../external/AMGCL/amgcl/preconditioner/dummy.hpp"

typedef amgcl::backend::builtin<double> Backend;

typedef amgcl::make_solver<
	// Use AMG as preconditioner:
	amgcl::amg<
	Backend,
	amgcl::coarsening::smoothed_aggregation,
	amgcl::relaxation::spai0
	>,
	// And BiCGStab as iterative solver:
	amgcl::solver::bicgstab<Backend>
> Solver;


class LSSolver
{
public:
	LSSolver();
	~LSSolver();

	void SolveSparseCRSWithAMG(std::vector<double>&& x, int nCol, const std::vector<int>& ptr, std::vector<int>& col,
		const std::vector<double>& val, const std::vector<double>& rhs, double& errorOut, int& nItOut, double tol = 1e-9);

	void PrecondtionCRS(int nCol, const std::vector<int>& ptr, std::vector<int>& col,
		const std::vector<double>& val, double tol = 1e-9);

	void SolvePreconditionedCRS(std::vector<double>&& x, int nCol, const std::vector<int>& ptr, std::vector<int>& col,
		const std::vector<double>& val, const std::vector<double>& rhs, double& errorOut, int& nItOut);

	void SolveSparseCRS(std::vector<double>&& x, int nCol, const std::vector<int>& ptr, std::vector<int>& col,
		const std::vector<double>& val, const std::vector<double>& rhs, double& errorOut, int& nItOut, double tol = 1e-9);

	// solve [aa bb cc] x = b; -> b � a saida e cc ser� modificado
	static void SolveTridiagonalDestructive(std::vector<double>& b, const size_t N, const std::vector<double>& aa,
		const std::vector<double>& bb, std::vector<double>& cc);

private:
	Solver* cPSolverFPreconditioned;
};