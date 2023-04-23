from flask import Flask, render_template, request, jsonify
import simulator  # import your simulation code here


app = Flask(__name__, static_folder='static')


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
