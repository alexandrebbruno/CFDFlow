#pragma once

#include "Mesh.hpp"
#include <armadillo>
#include <memory>
#include <string>

class Solver{
    private:
        Mesh mesh;
        arma::sp_mat A;
        arma::vec B;

    public:

        Solver(const Mesh &mesh);

        void fill_matrix(double dt);

        void compute_time_step(double dt);

        void solve(int total_time_steps, double dt);

        std::string get_A();

        std::string get_B();

        const std::vector<double> output_last_temperature();

};