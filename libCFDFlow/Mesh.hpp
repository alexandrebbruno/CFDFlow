#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <unordered_map>

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
        std::vector<Property<float>> properties;
        std::unordered_map<int, std::array<int, 2>> prescribedT;
        int number_of_cells_in_x;
        int number_of_cells_in_y;
        double dx;
        double dy;

    
    // Fill the neighbors of each cells
    void fill_cell_neighbors();

    /*
    Fill coordinates of all vertex of each cell.
    
    P4 ---- P3
    |       |
    |  Cell |
    |       | 
    P1 ---- P2 
    */
    void fill_coordinates();

    void fill_prescribed_temperature(double Tw, double Te);

    bool has_west_neighbor(const int& cell_id);

    bool has_east_neighbor(const int& cell_id);

    bool has_north_neighbor(const int& cell_id);

    bool has_south_neighbor(const int& cell_id);

    int get_row_id(const int& cell_id);

    int get_column_id(const int& cell_id);


public:
    Mesh(int number_of_cells_in_x, int number_of_cells_in_y, double dx, double dy, double Tw, double Te);

    const std::vector<std::array<int, 4>> get_neighbors();

    const std::vector<std::array<Vertex, 4>> get_coordinates();

    const int get_number_of_cells();

    const Property<float> get_property(const std::string& property_name);

    const double compute_dx(const int& p);

    const double compute_dy(const int& p);

    const double compute_dx_between_neighbors(const int& i, const int& j);

    const double compute_dy_between_neighbors(const int& i, const int& j);

    const double compute_property_between_neighbors(const std::string& property_name, const int i, const int j);

    ~Mesh();
};