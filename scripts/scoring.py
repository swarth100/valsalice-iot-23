import random
import json

# Scoring rationale:
# 0 = No effort
# 1 = Small effort
# 2 = Good effort
# 3 = High effort
with open(".scores.json", "r") as file:
    SCORES: dict[str, int] = json.load(file)

SEAT_SCORES: dict[int, str] = {
    1: "high",
    2: "med",
    3: "low",
    4: "low",
    5: "low",
    6: "med",
    7: "high",
    8: "med",
    9: "low",
    10: "low",
    11: "low",
    12: "med",
    13: "med",
    15: "high",
    16: "med",
    17: "low",
    18: "low",
    19: "med",
    20: "med",
    21: "high",
    22: "high",
    23: "vhigh",
    24: "high",
    25: "high",
    26: "high",
    27: "vhigh",
    28: "vhigh",
    29: "vhigh",
}

# Higher is Better
SCORE_PRIORITY: dict[str, int] = {
    "low": 0,
    "med": 1,
    "high": 2,
    "vhigh": 3,
}

# Must be same seats as number of students!
assert len(SEAT_SCORES) == len(SCORES)

# Sort students by their scores in ascending order
student_names = list(SCORES.keys())
random.shuffle(student_names)

# Create a new dictionary with shuffled keys
shuffled_students = {key: SCORES[key] for key in student_names}
sorted_students = sorted(SCORES.items(), key=lambda x: x[1])

# Sort seats by their scores in ascending order
sorted_seats = sorted(SEAT_SCORES.items(), key=lambda x: SCORE_PRIORITY[x[1]])

# Initialize a dictionary to store the seating assignments
seating_assignments = {}

# Assign students to seats
for student, _ in sorted_students:
    seat, _ = sorted_seats.pop(0)
    seating_assignments[student] = seat

# Print the seating assignments
for student, seat in seating_assignments.items():
    print(f"{student} is assigned to seat# {seat} with score {SEAT_SCORES[seat]}")
