/*
This is our front end that will grab data from main either from the hash table or heap and
Create our chart
 */

// set up listener for when html is loaded
document.addEventListener('DOMContentLoaded', function()
{
    fetch('/api/options-data') // fetch data from /api/options-data endpoint in backend input is a JSON
        .then(response => response.json()) // parses the JSON
        .then(data =>
        {
            console.log(data);
            createBubbleChart(data); // pass data to create the chart
        })
        .catch(error => console.error("Error fetching data:", error));
});

function createBubbleChart(data)
{
    // find min and max dates from data:
    let minDate = '9999-12-31';
    let maxDate = '0000-01-01';
    data.forEach(item => {
        if (item.date_range[0] < minDate)
        {
            minDate = item.date_range[0];
        }
        if (item.date_range[1] > maxDate)
        {
            maxDate = item.date_range[1];
        }
    });

    // define trace objects for plotly - plotly set of data points and styling options
    const traces = data.map(item => {
        return {
            x: [item.ticker], // x coordinates (ticker symbol)
            y: [item.total_options], // y coords (sum of calls + puts)
            text: `${item.high_price} - ${item.low_price}`,
            mode: 'markers',
            marker:
                {
                    size: Math.sqrt(item.total_options) * 10,
                    color: getBubbleColor(item.call_to_put_ratio)
                },
            type: 'scatter'
        };
    });
    const annotations = data.map(item => { // makes labels for the bubbles
        return {
            x: item.ticker,
            y: item.total_options,
            text: item.ticker, // labels ticker name
            xanchor: 'center',
            yanchor: 'middle',
            showarrow: false
        };
    });
    const layout = {
        title: "Visual of calls and put options for SP500 stock tickers",
        showlegend: false,
        xaxis: { title: 'Tickers'},
        yaxis: { title: `Total Volume of Options between ${minDate} and ${maxDate}` },
        annotations: annotations
    };

    Plotly.newPlot('bubbleChart', traces, layout);
}
function getBubbleColor(ratio)
{
    let hue = 0;
    if(ratio > 1)
    {
        hue = 120 * (1 - 1 / ratio); // 120 is green, 0 is red
    }
    return `hsl(${hue}, 100%, 50%)`; // creates an HSL color string
}
