from flask import Flask, jsonify

app = Flask(__name__)


@app.route('/api/options-data')
def get_all_options_data():
    # return stats stored in app
    if hasattr(app, 'stats'):
        return jsonify(app.stats)
    else:
        return jsonify({'error': 'Statistics not available'}), 500


if __name__ == '__main__':
    app.run(debug=True)