(define (problem task)

(:domain rosbot)

(:objects
    init wp1 wp2 wp3 wp4 - waypoint
    rosbot - robot
    m11 m12 m13 m15 - marker
)

(:init
    (robot_at rosbot init)
    
    (marker_at m11 wp1)
    (marker_at m12 wp2)
    (marker_at m13 wp3)
    (marker_at m15 wp4)
    
    (= (marker_detected) 0)


)

(:goal (and
    (marker_found m11)
    (marker_found m12)
    (marker_found m13)
    (marker_found m15)
    
    (reach_init init)  
    )
))
