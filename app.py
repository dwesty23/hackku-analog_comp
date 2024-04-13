# app.py

from flask import Flask, request, jsonify, render_template
from flask_cors import CORS  # Import CORS module
from calculate import calculate_equation

app = Flask(__name__)
CORS(app)  # Enable CORS for all routes

@app.route('/')
def index():
    return render_template('calc.html')

@app.route('/calculate', methods=['POST'])
def calculate():
    data = request.json
    equation = data['equation']
    try:
        result = calculate_equation(equation)
        print("Result:", result)  # Log the output of calculate.py
        return jsonify({'result': result.strip()})
    except:
        return jsonify({'result': 'An error occurred while processing the equation.'})

if __name__ == '__main__':
    app.run(debug=True)
