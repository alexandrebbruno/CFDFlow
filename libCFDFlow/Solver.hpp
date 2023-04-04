#include "Mesh.hpp"
#include <armadillo>
#include <memory>

class Solver{
    private:
        Mesh mesh;
        arma::sp_mat A;
        arma::vec B;

        void fill_matrix(double dt);

    public:

        Solver(const Mesh &mesh);

        void compute_time_step(double dt);

};