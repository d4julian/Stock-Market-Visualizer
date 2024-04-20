/*
This is our front end that will grab data from main either from the hash table or heap and
Create our chart
 */

// set up listener for when html is loaded
document.addEventListener('DOMContentLoaded', function()
{
    fetch('/api/options-data') // fetch data from /api/options-data endpoint in backend input is a JSON
        .then(response => response.json()) // parses the JSON
        .then(data => {
            const dataArray = Object.entries(data).map(([ticker, details]) => {
                console.log(`Ticker: ${ticker}, Details: `, details);
                return {
                    ticker: ticker,
                    ...details,
                    call_put_ratio: parseFloat(details.call_put_ratio),
                    total_options: parseInt(details.total_options),
                    start_date: details.date_range ? details.date_range[0][0] : 'N/A',  // Handling missing data
                    end_date: details.date_range ? details.date_range[0][1] : 'N/A'  // Handling missing data
                };
            });
            console.log("Prepared Data:", dataArray);
            createBubbleChart(dataArray);
        })
        .catch(error => console.error('Error loading the data:', error));
});

function createBubbleChart(data)
{
     console.log("Received data for charting:", data);
     data.forEach(item => {
        console.log(`Processing ${item.ticker}: Total Options = ${item.total_options}, Ratio = ${item.call_put_ratio}`);
    });


    let minDate = '9999-12-31';
    let maxDate = '0000-01-01';
    data.forEach(item => {
        if (item.start_date < minDate)
            minDate = item.start_date;
        if (item.end_date > maxDate)
            maxDate = item.end_date;
    });
    // define trace objects for plotly - plotly set of data points and styling options
    const traces = data.map(item => {
        console.log(`Processing: ${item.ticker}, Ratio: ${item.call_put_ratio}`);
        return {
            x: [item.ticker], // x coordinates (ticker symbol)
            y: [item.total_options], // y coords (sum of calls + puts)
            text: `${item.high_price} - ${item.low_price}`,
            mode: 'markers',
            marker:
                {
                    size: Math.pow((item.total_options), 0.26),
                    color: getBubbleColor(item.call_put_ratio),
                    opacity: 0.5
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
        titleSize: '10000',
        showlegend: false,
        xaxis: { title: 'Stock Tickers', scale: [-0.5, data.length -0.5], gridcolor: 'gray',
        },
        yaxis: { title: `Total Volume of Options between ${minDate} and ${maxDate}`, gridcolor: 'gray'},
        annotations: annotations,
        margin: {r: 50, l: 50 },
        plot_bgcolor: '#202020',
        paper_bgcolor: '#202020',
        font: { color: 'white'}
    };

    Plotly.newPlot('bubbleChart', traces, layout);
}
function getBubbleColor(ratio)
{
    if (typeof ratio !== 'number' || isNaN(ratio)) {
        console.log("Invalid ratio received:", ratio);
        return 'hsl(0, 100%, 50%)';  // Red
    }
    const minRatio = 1.0;
    const maxRatio = 2.0;

    let normalizedRatio = (ratio - minRatio) / (maxRatio - minRatio);
    normalizedRatio = Math.max(0, Math.min(normalizedRatio, 1));

    const hue = 120* normalizedRatio;
    return `hsl(${hue}, 100%, 50%)`;
}
