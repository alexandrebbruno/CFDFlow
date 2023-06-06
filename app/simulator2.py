import numpy as np

def simulate(input):

    number_of_cells_in_x = int(input['Nx'])
    Lx = float(input['Lx'])
    Tw = float(input['Tw'])
    Te = float(input['Te'])
    Tn = float(input['Tn'])
    Ts = float(input['Ts'])
    ro = float(input['ro'])
    cp = float(input['cp'])
    k = float(input['k'])

    plate_length = Lx
    max_iter_time = 1000

    alpha = k/(ro*cp)
    delta_x = Lx/number_of_cells_in_x

    delta_t = (delta_x ** 2)/(4 * alpha)
    gamma = (alpha * delta_t) / (delta_x ** 2)

    # Initialize solution: the grid of u(k, i, j)
    u = np.empty((max_iter_time, plate_length, plate_length))

    # Initial condition everywhere inside the grid
    u_initial = 0

    # Boundary conditions
    u_top = Tn
    u_left = Tw
    u_bottom = Ts
    u_right = Te

    # Set the initial condition
    u.fill(u_initial)

    # Set the boundary conditions
    u[:, (plate_length-1):, :] = u_top
    u[:, :, :1] = u_left
    u[:, :1, 1:] = u_bottom
    u[:, :, (plate_length-1):] = u_right

    for k in range(0, max_iter_time-1, 1):
        for i in range(1, plate_length-1, delta_x):
            for j in range(1, plate_length-1, delta_x):
                u[k + 1, i, j] = gamma * (u[k][i+1][j] + u[k][i-1][j] + u[k][i][j+1] + u[k][i][j-1] - 4*u[k][i][j]) + u[k][i][j]


    xf = [x for x in range(1, plate_length-1, delta_x)]
    yf = [x for x in range(1, plate_length-1, delta_x)]
    results = {
        'x': xf,
        'y': yf,
        'z': u[max_iter_time, :, :]
    }

    return results
    
