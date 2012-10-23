#include <stdio.h>
#include <stdlib.h>
void LoadTrain(long id, unsigned short boxes, float weight );
void UnloadTrain(long id, unsigned short *boxes, float *weight);
void GetWeights(float answer[]);
int CountBoxes();
int IsTrainFull();
void ClearTrain();
int main () {
  char user_input[20];
  long id;
  unsigned short boxes;
  float weight, weights[5];
  while (1) {
    printf( "a)load, b)unload, c)get weights d)count boxes, e)is train full f)reset q)quit \n");
    fgets(user_input,sizeof(user_input)-1, stdin);
    switch (user_input[0]) {
      case 'a':
        printf("id? ");
        fgets(user_input,sizeof(user_input)-1, stdin);
        id = atoi( user_input );
        printf( "boxes? " );
        fgets(user_input,sizeof(user_input)-1, stdin);
        boxes = atoi( user_input );
        printf( "weight? " );
        fgets(user_input,sizeof(user_input)-1, stdin);
        weight = (float) atof( user_input );
        LoadTrain(id,boxes,weight);
        break;
      case 'b':
        printf( "id? " );
        fgets(user_input,sizeof(user_input)-1, stdin);
        id = atoi( user_input );
        UnloadTrain(id, &boxes, &weight);
        printf( "Unloaded %d  boxes, %f weight\n", (int) boxes, weight );
        break;
      case 'c':
        GetWeights(weights);
        { int i;
          printf("weight summary: " );
          for (i=0 ; i<5; i++) {
            printf(" %f ", weights[i] );
          }
          printf("\n");
        }
        break;
      case 'd':
        printf("Total boxes %d \n", CountBoxes() ) ;
        break;
      case 'e':
        if ( IsTrainFull() ) {
          printf("Train is full\n" );
        } else {
          printf("Train is not full\n" );
        };
        break;
      case 'f':
        ClearTrain();
        break;
      case 'q':
        exit(1);
      default: 
        printf( "Unrecognized option\n" );
    }
  }
  return 0;
}
