struct Shipment {
  unsigned long id;
  unsigned short boxes;
  float weight;
};
struct Shipment train[5] = { {0, 0, 0.0},  {0, 0, 0.0},  {0, 0, 0.0},  
                           {0, 0, 0.0},  {0, 0, 0.0} } ;

/* train configuration: if the count of boxes is 0, then the shipment
   slot in the train is empty */

void LoadTrain(long id, unsigned short boxes, float weight ){
  /* Load a shipment onto the train */
  /* We receive three parameters.*/
  int i;
  /* find an empty slot */
  for (i=0 ; i<5; i++ ) {
    if ( train[i].boxes ==0 ) break;
  };
  train[i].id = id;
  train[i].boxes = boxes;
  train[i].weight = weight;
};

void UnloadTrain(long id, unsigned short *boxes, float *weight){
  /* Unload a shipment from the train */
  /* We receive one parameters, we return values in two.*/
  int i;
  for (i=0 ; i<5; i++ ) {
    if ( train[i].id == id ) break;
  }
  if (5 == i) {
    /* didn't find the shipment */
    *boxes = 0;
    *weight = 0.0;
  } else {
    *boxes = train[i].boxes;
    *weight = train[i].weight;
    /* We've unloaded, clean out the train slot */
    train[i].id = 0;
    train[i].boxes = 0;
    train[i].weight = 0.0;
  }
};

void GetWeights(float answer[]){
  /* Summarize the weights of each of the shipments */
  /* We receive no parameter, we return values in an array parameter. */
  int i;
  for (i=0 ; i<5; i++) {
     answer[i] = train[i].weight;
  }
};

int CountBoxes() { /* Count the total number of boxes on the train */
  /* We receive no parameter, we return an integer.*/
  int i, total = 0;
  for (i=0 ; i<5; i++) {
     total = total + train[i].boxes;
  }
  return total;
};
  
int IsTrainFull() {
  /* Return 1 if the train is full, 0 if it is not */
  int i;
  for (i=0 ; i<5; i++) {
    if ( 0 == train[i].boxes ) {
      /* found an empty slot, so we are not full */
      return 0;
    }
  }
  /* Searched but didn't find any empty slots, we're full */
  return 1;
}

void ClearTrain() {
  /* Clear out the train (so we can conduct more tests) */
  int i;
  for (i=0 ; i<5; i++) {
     train[i].id = 0;
     train[i].boxes = 0;
     train[i].weight = 0.0;
  }

}

