/* repair_cif.c */
#include <rpc/rpc.h>
#include <repair.h>
#include <repair_structures.h>
extern CLIENT *handle;

void QueueCar(unsigned long timeToRepair, float estimatedCost, unsigned long VIN) {
	struct queue_car_param * qcp;
	qcp.time_to_repair = timeToRepair;
	qcp.estimated_cost = estimatedCost;
	qcp.vin = VIN;
	(void) queue_car_1(&queue_car_param,handle);

}

void RepairCar(unsigned long unsigned long VIN, long *timeToRepair, float *costToRepair) {
	struct repair_car_param * rcp;
	struct repair_car_return * rct;
	rcp.vim = VIN;
	repair_car_return = repair_car_1(&rcp,handle);
	memcpy(&timeToRepair,rct->time_to_repair,sizeof(long));
	memcpy(&costToRepair,rct->cost_to_repair,sizeof(float));

}

void CarsInGarage(unsigned long answer[]) {
	struct cars_in_garage * carg;
	carg = cars_in_garage_1(void, handle);
        long * apt = answer; 
	memcpy(&apt,&carg,sizeof(answer[]));
}

int WorkTimeLeft() {
	int * wtl;
	wtl = work_time_left(wtl);
	return &wtl;
}

void ClearGarage() {
	int * blah;
	(void) clear_garage_1(blah);
}

int GarageEmpty() {
	int *ge;
	ge = garage_empty_1(ge);
	return &ge;
}
