#include "Solver.hpp"
#include <armadillo>


Solver::Solver(const Mesh &mesh): mesh(mesh){
    const auto number_of_elements = this->mesh.get_number_of_cells();
    A.set_size(number_of_elements, number_of_elements);
    B.set_size(number_of_elements);
};

void Solver::fill_matrix(double dt){
    auto compute_A = [&](const auto p1_id, const auto p2_id, const auto direction) {
        auto d = 0.0;
        // TODO: Use SOLID
        if (direction == Direction::West || direction == Direction::East){
            d = this->mesh.compute_dx_between_neighbors(p1_id, p2_id);
        }else{
            d = this->mesh.compute_dy_between_neighbors(p1_id, p2_id);
        }
        const auto k = this->mesh.compute_property_between_neighbors("k", p1_id, p2_id);
        const auto cp = this->mesh.compute_property_between_neighbors("cp", p1_id, p2_id);
        return k / (cp * d);
    };

    const auto& number_of_cells = this->mesh.get_number_of_cells();
    const auto& neighbors = this->mesh.get_neighbors();
    const auto& coordinates = this->mesh.get_coordinates();
    A.zeros(number_of_cells, number_of_cells);
    B.zeros(number_of_cells);

    for(size_t p_id = 0; p_id < number_of_cells; p_id++){
        const auto w_id = neighbors[p_id][Direction::West];
        const auto e_id = neighbors[p_id][Direction::East];
        const auto n_id = neighbors[p_id][Direction::North];
        const auto s_id = neighbors[p_id][Direction::South];
        const auto ro_p = this->mesh.get_property("ro").values[p_id];
        const auto dx_p = this->mesh.compute_dx(p_id);
        const auto dy_p = this->mesh.compute_dy(p_id);

        // TODO: extract CC from fill_matrix_A (SOLID)
        // Prescribed temperature
        auto Ae = 0;
        auto Aw = 0;
        auto Aef = 0;
        auto Tef = 0;
        auto Awf = 0;
        auto Twf = 0;
        if (e_id != -1){
            Ae = compute_A(e_id, p_id, Direction::East) * dy_p;
        }else{
            const auto kf = this->mesh.get_property("k").values[p_id];
            const auto dxf = this->mesh.compute_dx(p_id) / 2.0;
            const auto cpf = this->mesh.get_property("cp").values[p_id];
            Aef = kf * dy_p / (dxf * cpf);
            Tef = this->mesh.get_prescribed_temperature(p_id)[Direction::East];
        }
        if (w_id != -1){
            Aw = compute_A(p_id, w_id, Direction::West) * dy_p;
        } else{
            const auto kf = this->mesh.get_property("k").values[p_id];
            const auto dxf = this->mesh.compute_dx(p_id) / 2.0;
            const auto cpf = this->mesh.get_property("cp").values[p_id];
            Awf = kf * dy_p / (dxf * cpf);
            Twf = this->mesh.get_prescribed_temperature(p_id)[Direction::West];
        }

        // CC of zero flux
        const auto An = (n_id == -1) ? 0 : compute_A(n_id, p_id, Direction::North) * dx_p;
        const auto As = (s_id == -1) ? 0 : compute_A(p_id, s_id, Direction::South) * dx_p;

        const auto Ap = Ae + Aef + Aw + Awf + An + As + (ro_p * dx_p * dy_p)/dt;
        const auto Ap0 = (this->mesh.get_property("T0").values[p_id] * ro_p * dx_p * dy_p)/dt;
        const auto Sp0 = this->mesh.get_property("Sc").values[p_id] * dx_p * dy_p;
        const auto Bp = Ap0 + Sp0 + Awf * Twf + Aef * Tef;
        A(p_id, p_id) = Ap;
        if (w_id != -1){
            this->A(p_id, w_id) = Aw;
        }
        if (e_id != -1){
            this->A(p_id, e_id) = Ae;
        }
        if (n_id != -1){
            this->A(p_id, n_id) = An;
        }
        if (s_id != -1){
            this->A(p_id, s_id) = As;
        }
        this->B(p_id) = Bp;
    }
};

void Solver::compute_time_step(double dt){
    this->fill_matrix(dt);
    arma::vec X = arma::spsolve(this->A, this->B);
}

