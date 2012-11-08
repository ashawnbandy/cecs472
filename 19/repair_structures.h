/* repair.h */
struct queue_car_param {

	unsigned long time_to_repair;
	float cost_to_repair;
	unsigned long vin;

}

struct repair_car_param {

	unsigned long vim;

}

struct repair_car_return {

	long time_to_repair;
	float cost_to_repair;
}

struct cars_in_garage_return {
	unsigned long_answer;
}


