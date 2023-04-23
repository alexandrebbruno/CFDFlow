function simulate() {
    // get any input values from the form
    var form_data = {
        // replace these with the names of your input fields
        'Nx': $('#Nx').val(),
        'Ny': $('#Ny').val(),
        'Lx': $('#Lx').val(),
        'Ly': $('#Ly').val(),
        'Tw': $('#Tw').val(),
        'Te': $('#Te').val(),
        'Tn': $('#Tn').val(),
        'Ts': $('#Ts').val(),
        'total_t': $('#total_t').val(),
        'ro': $('#ro').val(),
        'k': $('#k').val(),
        'cp': $('#cp').val(),
    };

    console.log(form_data);


    // Make an AJAX request to the Flask endpoint to start the simulation
    $.ajax({
        type: 'POST',
        url: '/simulate',
        data: JSON.stringify(form_data),
        contentType: 'application/json;charset=UTF-8',
        success: function(result) {
            // Plot the simulation results in a heatmap

            var colorscaleValue = [
                [0, '#0b7eff'],
                [1, '#f10300']
              ];

            var data = [
                {
                    x: result.x,
                    y: result.y,
                    z: result.z,
                    type: 'heatmap',
                    colorscale: colorscaleValue,
                    showscale: false
                }
            ];
            Plotly.newPlot('heatmap_id', data, {
                title: 'Temperature',
                width: 800,
                height: 600
              });
        },
        error: function(xhr, status, error) {
            alert('Error: ' + error);
        }
    });
}

$(document).ready(function() {
    // Attach a click event listener to the "Simulate" button
    $('#simulate-btn').click(function() {
        simulate();
    });
});
