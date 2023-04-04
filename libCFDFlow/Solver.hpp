#include "Mesh.hpp"
#include <armadillo>

class Solver{
    private:
        Mesh mesh;
        arma::mat A;
        arma::vec B;

        void fill_matrix_A(arma::mat &A, double dt);

        void fill_matrix_B(double dt);

    public:

        Solver(const Mesh &mesh);

        void compute_time_step(double dt);

};