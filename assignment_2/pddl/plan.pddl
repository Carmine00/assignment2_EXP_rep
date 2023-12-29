Number of literals: 19
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
92% of the ground temporal actions in this problem are compression-safe
Initial heuristic = 17.000
b (16.000 | 30.000)b (13.000 | 60.002)b (12.000 | 60.002)b (9.000 | 90.004)b (8.000 | 90.004)b (5.000 | 120.006)b (4.000 | 120.006)b (1.000 | 130.007);;;; Solution Found
; States evaluated: 26
; Cost: 160.008
; Time 0.00
0.000: (goto_waypoint rosbot init wp1)  [30.000]
30.001: (find_marker rosbot m11 wp1)  [10.000]
30.002: (goto_waypoint rosbot wp1 wp2)  [30.000]
60.003: (find_marker rosbot m12 wp2)  [10.000]
60.004: (goto_waypoint rosbot wp2 wp3)  [30.000]
90.005: (find_marker rosbot m13 wp3)  [10.000]
90.006: (goto_waypoint rosbot wp3 wp4)  [30.000]
120.007: (find_marker rosbot m15 wp4)  [10.000]
130.008: (go_init rosbot wp4 init)  [30.000]
