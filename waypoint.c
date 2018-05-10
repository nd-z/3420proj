#include "waypoint.h"

volatile waypoint* nearest_waypoint = NULL;
volatile waypoint* waypoint_head = NULL;
volatile waypoint* waypoint_tail = NULL;

volatile unsigned int waypoints_hit = 0;
volatile float angle_next_wp = 0;

void push_tail_waypoint(waypoint *wp) {
	if (!waypoint_head) {
		waypoint_head = wp;
		waypoint_tail = wp;
		return;
	}

	if (waypoint_tail) {
		waypoint_tail->next = wp;
	}

	waypoint_tail = wp;
	waypoint_tail->next = NULL;
}
// /helpers

void init_waypoint(void) {
	waypoint* wp = malloc(sizeof(waypoint));
	wp->pos = malloc(sizeof(vector));
	wp->pos->x = curr_state->pos->x + (rand() % 1600);
	wp->pos->y = curr_state->pos->y + (rand() % 1600);
	wp->pos->z = curr_state->pos->z;
	wp->def_radius = 200;
	wp->near_radius = 400;
	wp->is_hit = 0;
	wp->next = NULL;

	push_tail_waypoint(wp);
	
	if (!nearest_waypoint) {
		nearest_waypoint = wp;
	} else {
		update_nearest_waypoint();
	}
}

void update_nearest_waypoint(void) {

	if (!nearest_waypoint) return;

	float target_distance;

	if (nearest_waypoint->is_hit) {
		target_distance = 0;
	} else {
		target_distance = calc_distance(nearest_waypoint->pos, curr_state->pos);
	}

	volatile waypoint* travel = waypoint_head;
	travel->next;

	while (travel) {
		if (!travel->is_hit) {
			float d = calc_distance(travel->pos, curr_state->pos);
			if (d < target_distance) {
				target_distance = d;
				nearest_waypoint = travel;
			}	
		}
		travel = travel->next;
	}
}

float is_near_waypoint(void) {
	float d = calc_distance(nearest_waypoint->pos, curr_state->pos);
	if (d <= nearest_waypoint->near_radius) {
		return d/nearest_waypoint->near_radius;
	} 
	return -1.;
}

int did_hit_waypoint(void) {
	if (calc_distance(nearest_waypoint->pos, curr_state->pos) <= nearest_waypoint->def_radius) {
		nearest_waypoint->is_hit = 1;
		waypoints_hit++;
		return 1;
	} else {
		return 0;
	}
}

/*
int is_on_waypoint(void) {
	int i = calc_distance(nearest_waypoint->pos, curr_state->pos) <= nearest_waypoint->def_radius;
	return i;
}*/
