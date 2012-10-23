#define NAME_LEN   80
#define SSN_LEN    11
#define GRADE_LEN  1
#define RECORD_LEN 100
#define MAX_RECORDS 10

struct dbrecord {
	char *Name;
	char *SSN;
	char *Grade;
};
typedef struct dbrecord dbrecord;
bool_t xdr_dbrecord();


#define DBPROG ((u_long)0x20000001)
#define DBVER ((u_long)2)
#define GET_BY_NAME ((u_long)1)
extern dbrecord *get_by_name_2();
#define GET_BY_SSN ((u_long)2)
extern dbrecord *get_by_ssn_2();
#define CHANGE_GRADE_BY_NAME ((u_long)3)
extern dbrecord *change_grade_by_name_2();
#define CHANGE_GRADE_BY_SSN ((u_long)4)
extern dbrecord *change_grade_by_ssn_2();

