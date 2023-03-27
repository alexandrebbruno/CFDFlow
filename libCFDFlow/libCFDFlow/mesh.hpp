#include <vector>
#include <array>
#include <string>
#include <iostream>

enum class Direction {
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

class mesh {
    private:
        std::vector<std::array<Vertex, 4>> coordinates;
        std::vector<std::array<int, 4>> neighbors;
        std::vector<Property<float>> properties;
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

    bool has_west_neighbor(const int& cell_id);

    bool has_east_neighbor(const int& cell_id);

    bool has_north_neighbor(const int& cell_id);

    bool has_south_neighbor(const int& cell_id);

    int get_row_id(const int& cell_id);

    int get_column_id(const int& cell_id);


public:
    mesh(int number_of_cells_in_x, int number_of_cells_in_y, double dx, double dy);
    
    ~mesh();
};