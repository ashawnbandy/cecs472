/* repair.x */


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



program REPAIRPROG {
	version	REPAIR {
		void 				QUEUE_CAR(queue_car_param) 	= 1;
		void 				REPAIR_CAR(repair_car_param) 	= 2;
		cars_in_garage_return 		CARS_IN_GARAGE(void) 	= 3;
		int 				WORKTIME_LEFT(void) = 4;
		void				CLEAR_GARAGE(void) = 5;
		int				GARAGE_EMPTY(void) = 6;
	} = 1;
} = 0x20000064;
