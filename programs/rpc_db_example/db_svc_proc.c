#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "db.h"

void createBuffers();
void writeDataBuffer();

char *database = "grades.db";
static char *readBuffer;
static dbrecord *buffer[MAX_RECORDS];
static dbrecord *dummyRecord;
int records = 0;

dbrecord *get_by_name_2(name)
/* return the record with the name specified on the command line */
char **name;
{
	int i;
	/* create buffer if it hasn't already been created */
	if (!buffer[0])
		createBuffers();

	/* search for the record */
	for(i=0; i<records; ++i)
		if (!strcasecmp(buffer[i]->Name, *name)) 
			return(buffer[i]);

	/* the record wasn't found */
	return(dummyRecord);

}

dbrecord *get_by_ssn_2(ssn)
/* return the record with the ssn specified on the command line */
char **ssn;
{
	int i;
	
	/* create buffer if it hasn't already been created */
	if (!buffer[0])
		createBuffers(); 

	/* search for the record */
	for(i=0; i<records; ++i)
		if (!strcasecmp(buffer[i]->SSN, *ssn)) 
			return(buffer[i]);

	/* the record wasn't found */
	return(dummyRecord);
}

dbrecord *change_grade_by_name_2(gradeRecord)
/* locate the record with the specified name and change the grade */		
dbrecord *gradeRecord;
{
	int i;
	
	/* create buffer if it hasn't already been created */	
	if (!buffer[0])
		createBuffers();

	for(i=0; i<records; ++i)
		if (!strcasecmp(buffer[i]->Name, gradeRecord->Name)) 
			break;

	if (i == records)
		return(dummyRecord);
	else {
		strcpy(buffer[i]->Grade, gradeRecord->Grade);
		writeDataBuffer();
		return(buffer[i]);
	}
}

dbrecord *change_grade_by_ssn_2(gradeRecord)
/* locate the record with the specified ssn and change the grade */		
dbrecord *gradeRecord;
{
	int i;
	
	/* create buffer if it hasn't already been created */	
	if (!buffer[0])
		createBuffers();

	for(i=0; i<records; ++i)
		if (!strcasecmp(buffer[i]->SSN, gradeRecord->SSN)) 
			break;

	if (i == records)
		return(dummyRecord);
	else {
		strcpy(buffer[i]->Grade, gradeRecord->Grade);
		writeDataBuffer();
		return(buffer[i]);
	}
}


void createBuffers()
{		
	FILE *fp = fopen(database, "r");
		
	readBuffer = (char *)malloc(RECORD_LEN);
		
	while (fgets(readBuffer, RECORD_LEN-1, fp) && (records<MAX_RECORDS))  {

		buffer[records] = (dbrecord *)malloc(sizeof(dbrecord));
		buffer[records]->Name = (char *)malloc(NAME_LEN);
		buffer[records]->SSN = (char *)malloc(SSN_LEN);
		buffer[records]->Grade = (char *)malloc(GRADE_LEN);
		sscanf(readBuffer, "%s%s%s", buffer[records]->Name, 
			buffer[records]->SSN, buffer[records]->Grade);
		++records;
	}
	fclose(fp);
	dummyRecord = (dbrecord *)malloc(sizeof(dbrecord));
	dummyRecord->Name = (char *)malloc(NAME_LEN);
	dummyRecord->SSN = (char *)malloc(SSN_LEN);
	dummyRecord->Grade = (char *)malloc(GRADE_LEN);
	strcpy(dummyRecord->Name, "0");
}

void writeDataBuffer()
{
	int i;
			
	FILE *fp = fopen(database, "w");
		
	for(i=0; i<records; ++i)  
		fprintf(fp, "%s\t%s\t%s\n", buffer[i]->Name, 
			buffer[i]->SSN, buffer[i]->Grade);

	fclose(fp);
}
