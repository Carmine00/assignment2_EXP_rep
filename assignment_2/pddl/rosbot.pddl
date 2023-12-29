(define (domain rosbot)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents)

(:types
	waypoint
	robot
	marker
)

(:predicates
	(robot_at ?v - robot ?wp - waypoint)
	(visited ?wp - waypoint)
	(marker_found ?m - marker)
	(marker_at ?m - marker ?wp - waypoint)
	(reach_init ?wp - waypoint)
)

(:functions
	(marker_detected)
)



;; Move to any waypoint, avoiding terrain
(:durative-action goto_waypoint
	:parameters (?r - robot ?from ?to - waypoint)
	:duration ( = ?duration 30)
	:condition (and
			(at start (robot_at ?r ?from)))
	:effect (and
			(at start (not (robot_at ?r ?from)))
			(at end (visited ?to))
			(at end (robot_at ?r ?to)))
)


;; Rotate to find marker
(:durative-action find_marker
	:parameters (?r - robot ?m - marker ?wp - waypoint)
	:duration ( = ?duration 10)
	:condition (and
			(at start (robot_at ?r ?wp))
			(at start (marker_at ?m ?wp)))
	:effect (and
		  (at end (increase (marker_detected) 1))
		  (at end (marker_found ?m)))
)

;; Reach init
(:durative-action go_init
	:parameters (?r - robot ?from ?to - waypoint)
	:duration ( = ?duration 30)
	:condition (and
			(at start (robot_at ?r ?from))
			(at start (= (marker_detected) 4)))
	:effect (and
			(at start (not (robot_at ?r ?from)))
			(at end (robot_at ?r ?to))
			(at end (reach_init ?to)))
)




)
