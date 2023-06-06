from flask import Flask, render_template, request, jsonify
import simulator # import your simulation code here
#import PyCFDFlow

app = Flask(__name__, static_folder='static')

#def simulate_CFD(input):

#    number_of_cells_in_x = int(input['Nx']) 
#    number_of_cells_in_y = int(input['Ny'])
#    Lx = float(input['Lx'])
#    Ly = float(input['Ly'])
#    Tw = float(input['Tw'])
#    Te = float(input['Te'])
#    Tn = float(input['Tn'])
#    Ts = float(input['Ts'])
#    total_simulation_t = float(input['total_t'])
#    ro = float(input['ro'])
#    cp = float(input['cp'])
#    k = float(input['k'])

#    dx = Lx/number_of_cells_in_x
#    dy = Ly/number_of_cells_in_y
    
#    dt = 0.1
#    number_of_time_steps = int(total_simulation_t/dt)
#    T0 = 1

#    mesh = PyCFDFlow.Mesh(number_of_cells_in_x, number_of_cells_in_y, dx, dy, Tw, Te, Tn, Ts, T0)
#    mesh.set_property("ro", ro)
#    mesh.set_property("k", cp)
#    mesh.set_property("cp", k)
#    mesh.set_property("Sc", 0)

#    solver = PyCFDFlow.Solver(mesh)

#    solver.solve(number_of_time_steps, dt)

#    temperature = solver.output_last_temperature()
    
#    x = mesh.compute_x_cell_center_coordinates()
#    y = mesh.compute_y_cell_center_coordinates()
#    z = [temperature[i:i+len(x)] for i in range(0, len(temperature), len(x))]        

#    results = {
#        'x': x,
#        'y': y,
#        'z': z
#    }

#    return results


# define a route to serve the index.html file
@app.route('/')
def index():
    return render_template('index.html')

# define a route to trigger the simulation
@app.route('/simulate', methods=['POST'])
def simulate():
    # get any parameters needed for the simulation from the request
    # call your simulation function with the parameters and get the results
    data = request.json
    results = simulator.simulate(data)

    # return the results as a JSON object
    return jsonify(results)

if __name__ == '__main__':
    app.run(debug=True)
