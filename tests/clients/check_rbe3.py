"""Each CI client must agree with the same physical reference, including both original evaluations."""
import json
import math
import sys

base = [-0.9068347944434741, -0.05032212998106124]
moved = [-0.9068851528035369, -0.05039451433945616]
with open(sys.argv[1], encoding="utf-8-sig") as stream:
    rows = json.load(stream)
for actual, expected in zip(rows, (base, moved, base, base), strict=True):
    for value, target in zip(actual, expected, strict=True):
        if not math.isclose(value, target, rel_tol=2e-7, abs_tol=1e-9):
            raise ValueError(f"Expected {target}, got {value}")
