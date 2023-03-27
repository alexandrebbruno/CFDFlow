#include "mesh.hpp"

mesh::mesh(int number_of_cells_in_x, int number_of_cells_in_y, double dx, double dy):
    number_of_cells_in_x(number_of_cells_in_x), number_of_cells_in_y(number_of_cells_in_y)
{   
    int number_of_cells = number_of_cells_in_x * number_of_cells_in_y;
    coordinates.reserve(number_of_cells);
    neighbors.reserve(number_of_cells);
    
    this->fill_cell_neighbors();
    this->fill_coordinates();
}

int mesh::get_row_id(const int& cell_id){
    return static_cast<int>(cell_id / this->number_of_cells_in_y);
}

int mesh::get_column_id(const int& cell_id){
    return cell_id % this->number_of_cells_in_y;
}

void mesh::fill_coordinates(){
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

void mesh::fill_cell_neighbors(){   

    for (size_t j = 0; j < this->number_of_cells_in_y; j++){
        for (size_t i = 0; i < this->number_of_cells_in_x; i++){
            const auto cell_id = i + j * this->number_of_cells_in_y;
            const auto east = this->has_east_neighbor(cell_id) ? cell_id - 1 : -1;
            const auto west = this->has_west_neighbor(cell_id) ? cell_id + 1 : -1;
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

bool mesh::has_west_neighbor(const int& cell_id){
    const auto row_id = this->get_row_id(cell_id);

    const auto first_element_in_row = row_id * this->number_of_cells_in_x;
    if (cell_id > first_element_in_row){
        return true;
    }else{
        return false;
    }
}

bool mesh::has_east_neighbor(const int& cell_id){
    const auto row_id = this->get_row_id(cell_id);
    int last_element_in_row = (row_id + 1) * this->number_of_cells_in_x - 1;
    if (cell_id < last_element_in_row){
        return true;
    }else{
        return false;
    }
}

bool mesh::has_north_neighbor(const int& cell_id){
    int first_element_of_last_row = (this->number_of_cells_in_y - 1) * this->number_of_cells_in_x;
    if (cell_id < first_element_of_last_row){
        return true;
    }else{
        return false;
    }
}

bool mesh::has_south_neighbor(const int& cell_id){
    int last_element_of_first_row = this->number_of_cells_in_x - 1;
    if (cell_id > last_element_of_first_row){
        return true;
    }else{
        return false;
    }
}
