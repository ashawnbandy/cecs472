#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <rpc/rpc.h>
#include "db.h"

void createGradeRecord();      /* This could have been put in db.h */

static dbrecord *gradeRecord;

main(argc, argv)
int argc;
char *argv[];
{
	CLIENT   *clientHandle; 
	dbrecord *record;
	int       key = atol(argv[2]);

	/* Create the client handle used for calling the DBPROG program on
	   the server and use the TCP protocol when contacting the server  */ 

	if (!(clientHandle = clnt_create(argv[1], DBPROG, DBVER, "tcp"))) {
		clnt_pcreateerror(argv[1]);  /* couldn't find server */
		exit(1);
	}
	switch(key)  {
	
	case GET_BY_NAME:  
		/* retrieve the record with the name specified on the command line */
		record = get_by_name_2(&argv[3], clientHandle);
		/* a zero means the record wasn't found */
		if (!strcasecmp(record->Name, "0"))
			printf("Record not found\n");		
		else
			printf("%s   %s   %s\n",record->Name, record->SSN, record->Grade);
		break;
		
	case GET_BY_SSN:
		/* retrieve the record with the ssn specified on the command line */
		record = get_by_ssn_2(&argv[3], clientHandle);
		/* a zero means the record wasn't found */
		if (!strcasecmp(record->Name, "0"))
			printf("Record not found\n");		
		else
			printf("%s   %s   %s\n",record->Name, record->SSN, record->Grade);
		break;
		
	case CHANGE_GRADE_BY_NAME:  {
		/* locate the record with the specified name and change the grade */		
		createGradeRecord();		/* create a record buffer for the data */

		/* put the name and the grade in the buffer */
		strcpy(gradeRecord->Name, argv[3]);
		strcpy(gradeRecord->Grade, argv[4]);

		/* call the server */
		record = change_grade_by_name_2(gradeRecord, clientHandle);

		if (!strcasecmp(record->Name, "0"))
			printf("Record not found\n");		
		else
			printf("%s   %s   %s\n",record->Name, record->SSN, record->Grade);
		break;
	}
	case CHANGE_GRADE_BY_SSN:  {	
		/* locate the record with the specified ssn and change the grade */		
		createGradeRecord();		/* create a record buffer for the data */ 

		/* put the ssn and the grade in the buffer */
		strcpy(gradeRecord->SSN, argv[3]);
		strcpy(gradeRecord->Grade, argv[4]);

		record = change_grade_by_ssn_2(gradeRecord, clientHandle);

		if (!strcasecmp(record->Name, "0"))
			printf("Record not found\n");		
		else
			printf("%s   %s   %s\n",record->Name, record->SSN, record->Grade);
		break;
	}
	default:
		printf("Error: invalid key\n");
	}	
}
void createGradeRecord()
{		
		/* create a buffer for the student record data */
		gradeRecord = (dbrecord *) malloc(sizeof(dbrecord));
		gradeRecord->Name = (char *) malloc(NAME_LEN);
		gradeRecord->Grade = (char *) malloc(GRADE_LEN);
		gradeRecord->SSN  = (char *) malloc(SSN_LEN);
}
