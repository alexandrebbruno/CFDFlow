#pragma once

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <unordered_map>
#include <armadillo>

enum Direction {
    East,
    West,
    South,
    North };

template <typename T>
class Property{
    public:
        std::string name;
        std::vector<T> values;

        Property(const std::string& name, std::vector<T> values): name(name), values(values){};
};

class Vertex {
    public:
        float x_coordinate;
        float y_coordinate;

        Vertex(const int x, const int y): x_coordinate(x), y_coordinate(y){};
};

class Mesh {
    private:
        std::vector<std::array<Vertex, 4>> coordinates;
        std::vector<std::array<int, 4>> neighbors;
        std::vector<Property<double>> properties;
        std::vector<arma::vec> temperature;
        int number_of_cells_in_x;
        int number_of_cells_in_y;
        double T0;
        double dx;
        double dy;
        double Te;
        double Tw;
        double Tn;
        double Ts;
        

    
    // Fill the neighbors of each cells
    void fill_cell_neighbors();

    /*
    Fill coordinates of all vertex of each cell.
    
    P3 ---- P2
    |       |
    |  Cell |
    |       | 
    P0 ---- P1 
    */
    void fill_coordinates();

    //void fill_prescribed_temperature(double Tw, double Te);

    bool has_west_neighbor(const int& cell_id);

    bool has_east_neighbor(const int& cell_id);

    bool has_north_neighbor(const int& cell_id);

    bool has_south_neighbor(const int& cell_id);

    int get_row_id(const int& cell_id);

    int get_column_id(const int& cell_id);


public:
    Mesh(int number_of_cells_in_x, int number_of_cells_in_y, double dx, double dy, double Tw, double Te, double Tn, double Ts, double T0);

    void set_initial_contidion();

    void set_property(const std::string& property_name, const double& property_values);

    void add_temperature(const arma::vec& temperature);

    const std::vector<double> compute_x_cell_center_coordinates();
    
    const std::vector<double> compute_y_cell_center_coordinates();

    const arma::vec& get_last_temperature();

    const std::array<double, 4> get_prescribed_temperature();

    const std::vector<std::array<int, 4>> get_neighbors();

    const std::vector<std::array<Vertex, 4>> get_coordinates();

    const int get_number_of_cells();

    const Property<double> get_property(const std::string& property_name);

    const double compute_dx(const int& p);

    const double compute_dy(const int& p);

    const double compute_dx_between_neighbors(const int& i, const int& j);

    const double compute_dy_between_neighbors(const int& i, const int& j);

    const double compute_property_between_neighbors(const std::string& property_name, const int i, const int j);

    ~Mesh();
};