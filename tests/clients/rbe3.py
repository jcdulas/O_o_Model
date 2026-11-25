"""Run with the Model under test and oo-solver 0.2.2."""
import json
import sys
import numpy as np
from oo_model import read_model
from oo_solver import prepare_optimization

def evaluate(deck):
    problem = prepare_optimization(deck, analysis={"aeroelastic": [1], "buckling": [2]})
    return problem.evaluate(problem.initial_values)

def measure(point):
    return [float(point.responses[4][0]), float(point.nodal_coordinate_gradient(4, [6])["values"][0, 0])]

source = read_model(sys.argv[1])
point = evaluate(source)
before = measure(point)
trial = source.copy()
trial.set_node_positions(np.array([6], dtype=np.int32), np.array([[.181, 1.75, 0.]]))
assert not trial.check_references()
print(json.dumps([before, measure(evaluate(trial)), measure(point), measure(evaluate(source))]))
