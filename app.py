from flask import Flask, jsonify, render_template

app = Flask(__name__)

@app.route('/', methods=['GET'])
def home():
    return "Welcome to Team 144 ? I think Flask app is running"
@app.route('/chart')
def chart():
    return render_template('chart.html')
@app.route('/api/options-data', methods=['GET'])
def get_all_options_data():
    # return stats stored in app
    return jsonify(app.stats)

       # return jsonify({'error': 'Statistics not available'}), 500
@app.route('/api')
def test():
    print("hello")


if __name__ == '__main__':
    app.run(debug=True)