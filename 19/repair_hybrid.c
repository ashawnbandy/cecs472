

#include <stdlib.h>
#include <stdio.h>
void QueueCar(unsigned long timeToRepair, float estimatedCost,
    unsigned long VIN );
void RepairCar(unsigned long VIN, long *timeToRepair, float *costToRepair);
void CarsInGarage(unsigned long answer[]);
int WorkTimeLeft();
void ClearGarage();
int GarageEmpty();
int main () {
  char user_input[20];
  unsigned long VIN;
  unsigned long repairTime;
  float repairCost;
  unsigned long VINs[5];
  while (1) {
    printf( "a)queue, b)repair, c)cars in d)time left, e)clear f)is empty q)quit \n");
    fgets(user_input,sizeof(user_input)-1, stdin);
    switch (user_input[0]) {
      case 'a':
        printf("VIN? ");
        fgets(user_input,sizeof(user_input)-1, stdin);
        VIN = atoi( user_input );
        printf( "time to repair? " );
        fgets(user_input,sizeof(user_input)-1, stdin);
        repairTime = atoi( user_input );
        printf( "estimated cost? " );
        fgets(user_input,sizeof(user_input)-1, stdin);
        repairCost = (float) atof( user_input );
        QueueCar(repairTime,repairCost,VIN);
        break;
      case 'b':
        printf( "id? " );
      fgets(user_input,sizeof(user_input)-1, stdin);
        VIN = atoi( user_input );
        RepairCar(VIN, &repairTime, &repairCost);
        printf( "Repaired %d Time: %d, Cost: %f\n", VIN,  repairTime, 
          repairCost);
        break;
      case 'c':
        CarsInGarage(VINs);
        { int i;
          printf("Cars in Garage: " );
          for (i=0 ; i<5; i++) {
            printf(" %d ", VINs[i] );
          }
          printf("\n");
        }
        break;
      case 'd':
        printf("Amount of Work left %d \n", WorkTimeLeft() ) ;
        break;
      case 'e':
        ClearGarage();
        break;
      case 'f':
        if ( GarageEmpty() ) {
          printf("Garage is empty\n" );
        } else {
          printf("Garage is not empty\n" );
        };
        break;
      case 'q':
        exit(1);
      default: 
        printf( "Unrecognized option\n" );
    }
  }
  return 0;
}


struct CarEntry {
  unsigned long timeToRepair; /* Minutes */
  float costToRepair;
  unsigned long VIN; /* Vehicle Identification Number */
};
struct CarEntry garage[5] = { {0, 0.0, 0},  {0, 0.0, 0},  {0, 0.0, 0},  
                           {0, 0.0, 0},  {0, 0.0, 0} } ;

/* garage rule: if the VIN is 0, then the slot is empty */

void QueueCar(unsigned long timeToRepair, float estimatedCost,
    unsigned long VIN ){
  /* Accept a car for repair */
  int i;
  /* find an empty slot */
  for (i=0 ; i<5; i++ ) {
    if ( garage[i].VIN == 0 ) break;
  };
  garage[i].VIN = VIN;
  garage[i].timeToRepair = timeToRepair;
  garage[i].costToRepair = estimatedCost;
};

void RepairCar(unsigned long VIN, long *timeToRepair, float *costToRepair){
  /* remove a car from the repair queue */
  /* We receive one parameter, we return values in two.*/
  int i;
  for (i=0 ; i<5; i++ ) {
    if ( garage[i].VIN == VIN ) break;
  }
  if (5 == i) {
    /* didn't find the car */
    *timeToRepair = 0;
    *costToRepair = 0.0;
  } else {
    *timeToRepair = garage[i].timeToRepair;
    *costToRepair = garage[i].costToRepair;
    /* We've fixed it, clean out the garage slot */
    garage[i].VIN = 0;
    garage[i].timeToRepair = 0;
    garage[i].costToRepair = 0.0;
  }
};

void CarsInGarage(unsigned long answer[]){
  /* Give the VIN of each of the cars in the garage */
  /* We receive no parameter, we return 5 values in an array parameter. */
  int i;
  for (i=0 ; i<5; i++) {
     answer[i] = garage[i].VIN;
  }
};

int WorkTimeLeft() {
  /* Total waiting time till repairs are done */
  /* We receive no parameter, we return an integer.*/
  int i, total = 0;
  for (i=0 ; i<5; i++) {
     if (garage[i].VIN != 0)
       total = total + garage[i].timeToRepair;
  }
  return total;
};
  
void ClearGarage() {
  /* Clear out the list of cars to repair (so we can conduct more tests) */
  int i;
  for (i=0 ; i<5; i++) {
     garage[i].VIN = 0;
     garage[i].timeToRepair = 0;
     garage[i].costToRepair = 0.0;
  }
};

int GarageEmpty() {
  /* Return 1 if the garage is full, 0 if it is not */
  int i;
  for (i=0 ; i<5; i++) {
    if ( 0 != garage[i].VIN ) {
      /* found a car, we are not empty */
      return 0;
    }
  }
  /* Searched but didn't find any cars, we're empty */
  return 1;

};
