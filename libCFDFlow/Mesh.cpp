#include "Mesh.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>      // std::invalid_argument

Mesh::Mesh(int number_of_cells_in_x, int number_of_cells_in_y, double dx, double dy, double Tw, double Te, double Tn, double Ts, double T0):
    number_of_cells_in_x(number_of_cells_in_x), number_of_cells_in_y(number_of_cells_in_y), T0(T0), dx(dx), dy(dy), Tw(Tw), Te(Te), Ts(Ts), Tn(Tn)
{   
    int number_of_cells = number_of_cells_in_x * number_of_cells_in_y;
    
    this->coordinates.resize(number_of_cells, std::array<Vertex, 4>({Vertex(-1, -1), Vertex(-1, -1), Vertex(-1, -1), Vertex(-1, -1)}));
    this->neighbors.resize(number_of_cells, std::array<int, 4>({-1, -1, -1, -1}));
    
    this->fill_cell_neighbors();
    this->fill_coordinates();
    //this->fill_prescribed_temperature(Tw, Te);
    this->set_initial_contidion();
}

Mesh::~Mesh(){};

void Mesh::set_initial_contidion(){
    this->temperature = std::vector<arma::vec>();
    arma::vec T0_vec(this->get_number_of_cells());
    T0_vec.fill(this->T0);
    this->temperature.push_back(T0_vec);
}

void Mesh::set_property(const std::string& property_name, const double& property_value){
    std::vector<double> values;
    values.resize(this->get_number_of_cells(), property_value);

    const auto prop = Property(property_name, values);
    this->properties.push_back(prop);
}

const arma::vec& Mesh::get_last_temperature(){
    return this->temperature.back();
}

void Mesh::add_temperature(const arma::vec& current_temperature){
    this->temperature.push_back(current_temperature);
}

int Mesh::get_row_id(const int& cell_id){
    return static_cast<int>(cell_id / this->number_of_cells_in_y);
}

int Mesh::get_column_id(const int& cell_id){
    return cell_id % this->number_of_cells_in_y;
}

void Mesh::fill_coordinates(){
    for (size_t j = 0; j < this->number_of_cells_in_y; j++){
        for (size_t i = 0;  i < this->number_of_cells_in_x; i++){
            const auto cell_id = i + j * number_of_cells_in_x;
            const auto row_id = j;
            const auto collum_id = i;
            const auto x1 = collum_id * dx;
            const auto y1 = row_id * dy;
            const auto P1 = Vertex(x1, y1);
            const auto x2 = x1 + dx;
            const auto y2 = y1;
            const auto P2 = Vertex(x2, y2);
            const auto x3 = x2;
            const auto y3 = y2 + dy;
            const auto P3 = Vertex(x3, y3);
            const auto x4 = x3 - dx;
            const auto y4 = y3;
            const auto P4 = Vertex(x4, y4);
            this->coordinates[cell_id] = {P1, P2, P3, P4};
        }
    }
}

void Mesh::fill_cell_neighbors(){   

    for (size_t j = 0; j < this->number_of_cells_in_y; j++){
        for (size_t i = 0; i < this->number_of_cells_in_x; i++){
            const auto cell_id = i + j * this->number_of_cells_in_y;
            const auto east = this->has_east_neighbor(cell_id) ? cell_id + 1 : -1;
            const auto west = this->has_west_neighbor(cell_id) ? cell_id - 1 : -1;
            const auto north = this->has_north_neighbor(cell_id) ? cell_id + this->number_of_cells_in_x : -1;
            const auto south = this->has_south_neighbor(cell_id) ? cell_id - this->number_of_cells_in_x : -1;
            
            std::array<int, 4> cell_neighbors;
            cell_neighbors[static_cast<int>(Direction::East)] = east;
            cell_neighbors[static_cast<int>(Direction::West)] = west;
            cell_neighbors[static_cast<int>(Direction::North)] = north;
            cell_neighbors[static_cast<int>(Direction::South)] = south;

            this->neighbors[cell_id] = cell_neighbors;
        }
    }
}

/*
void Mesh::fill_prescribed_temperature(const double Tw, const double Te){
    const auto number_of_cells = this->number_of_cells_in_x * this->number_of_cells_in_y;
    for(size_t p_id = 0; p_id < number_of_cells; p_id++){
        const auto neighbor = this->neighbors[p_id];
        if (neighbor[Direction::West] == -1){
            this->prescribedT[p_id] = {-1000000 , -1000000};
            this->prescribedT[p_id][Direction::West] = Tw;
        }
        if (neighbor[Direction::East] == -1){
            this->prescribedT[p_id] = {-1000000 , -1000000};
            this->prescribedT[p_id][Direction::East] = Te;
        }
    }
}
*/

bool Mesh::has_west_neighbor(const int& cell_id){
    const auto row_id = this->get_row_id(cell_id);

    const auto first_element_in_row = row_id * this->number_of_cells_in_x;
    if (cell_id > first_element_in_row){
        return true;
    }else{
        return false;
    }
}

bool Mesh::has_east_neighbor(const int& cell_id){
    const auto row_id = this->get_row_id(cell_id);
    const auto last_element_in_row = (row_id + 1) * this->number_of_cells_in_x - 1;
    if (cell_id < last_element_in_row){
        return true;
    }else{
        return false;
    }
}

bool Mesh::has_north_neighbor(const int& cell_id){
    const auto first_element_of_last_row = (this->number_of_cells_in_y - 1) * this->number_of_cells_in_x;
    if (cell_id < first_element_of_last_row){
        return true;
    }else{
        return false;
    }
}

bool Mesh::has_south_neighbor(const int& cell_id){
    int last_element_of_first_row = this->number_of_cells_in_x - 1;
    if (cell_id > last_element_of_first_row){
        return true;
    }else{
        return false;
    }
}

const std::array<double, 4> Mesh::get_prescribed_temperature(){
    const auto prescribedT = std::array<double, 4>({this->Te, this->Tw, this->Ts, this->Tn});
    return prescribedT;
}

const std::vector<std::array<int, 4>> Mesh::get_neighbors(){
    return this->neighbors;
}

const std::vector<std::array<Vertex, 4>> Mesh::get_coordinates(){
    return this->coordinates;
}

// [TODO] apply SOLID in next two methods
const std::vector<double> Mesh::compute_x_cell_center_coordinates(){
    auto x_CC_coordinates = std::vector<double>();
    x_CC_coordinates.push_back(this->dx/2.0);
    for(size_t i = 1; i < this->number_of_cells_in_x; i++){
        x_CC_coordinates.push_back(x_CC_coordinates[i-1] + this->dx);
    }
    return x_CC_coordinates;
}

const std::vector<double> Mesh::compute_y_cell_center_coordinates(){
    auto y_CC_coordinates = std::vector<double>();
    y_CC_coordinates.push_back(this->dy/2.0);
    for(size_t i = 1; i < this->number_of_cells_in_y; i++){
        y_CC_coordinates.push_back(y_CC_coordinates[i-1] + this->dy);
    }
    return y_CC_coordinates;
}
/*
------3------5
*/

const int Mesh::get_number_of_cells(){
    return this->number_of_cells_in_x * this->number_of_cells_in_y;
}

const Property<double> Mesh::get_property(const std::string& property_name){
    for(const auto& p: this->properties){
        if(p.name == property_name){
            return p;
        }
    }
    throw std::invalid_argument("Try to access Invalid property name.");
}

const double Mesh::compute_dx(const int& p){
    return this->dx;//this->coordinates[p][1].x_coordinate - this->coordinates[p][0].x_coordinate;
}

const double Mesh::compute_dy(const int& p){
    return this->dy;//this->coordinates[p][2].y_coordinate - this->coordinates[p][1].y_coordinate;
}

const double Mesh::compute_dx_between_neighbors(const int& i, const int& j){
    const auto i_neighbors = this->neighbors[i];
    const auto is_valid_neighbor = std::count(std::begin(i_neighbors), std::end(i_neighbors), j) > 0;
    if (is_valid_neighbor == false){
        std::string output = "";
        output += "i: " + std::to_string(i);
        output += " j: " + std::to_string(j);
        output += " n[i] :";
        for (const auto& n : i_neighbors){
            output += std::to_string(n) + " ";
        }
        
        throw std::invalid_argument(output);
    }
    assert(is_valid_neighbor);
    
    const auto dx_i = this->compute_dx(i);
    const auto dx_j = this->compute_dx(j);

    assert(dx_i == dx_j);
    
    return dx_i; // (dx_i + dx_j)/2.0;
}

const double Mesh::compute_dy_between_neighbors(const int& i, const int& j){
    const auto i_neighbors = this->neighbors[i];

    const auto is_valid_neighbor = std::count(std::begin(i_neighbors), std::end(i_neighbors), j) > 0;
    assert(is_valid_neighbor);
    
    const auto dy_i = this->compute_dy(i);
    const auto dy_j = this->compute_dy(j);
    
    assert(dy_i == dy_j);

    return dy_i; //(dy_i + dy_j)/2.0;
}

const double Mesh::compute_property_between_neighbors(const std::string& property_name, const int i, const int j){
    
    auto compute_distance = [&](const auto p1) {
        const auto x_neighbors = {neighbors[p1][Direction::West], neighbors[p1][Direction::East]};
        const auto p2 = (p1 == i) ? j : i; 
        const auto are_x_neighbors = std::count(std::begin(x_neighbors), std::end(x_neighbors), p2) > 0;        
        if (are_x_neighbors){
            return this->compute_dx(p1);
        }else{
            return this->compute_dy(p1);
        }
    };

    const auto i_neighbors = this->neighbors[i];
    const auto is_valid_neighbor = std::count(std::begin(i_neighbors), std::end(i_neighbors), j) > 0;
    assert(is_valid_neighbor);
    
    const auto properties = this->get_property(property_name);
    const auto prop_i = properties.values[i];
    const auto prop_j = properties.values[j];
    const auto d_i = compute_distance(i);
    const auto d_j = compute_distance(j);

    assert(prop_i == prop_j);

    return prop_i;//prop_i + ((prop_j - prop_i) * d_i)/(d_i + d_j); 
}