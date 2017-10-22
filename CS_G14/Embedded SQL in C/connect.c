/* Processed by ecpg (4.11.0) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "connect.pgc"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* exec sql begin declare section */
    
   
   
   
   

     

#line 6 "connect.pgc"
 char * a , * b , * c , * d ;
 
#line 7 "connect.pgc"
 char * query = NULL ;
 
#line 8 "connect.pgc"
 char * name = NULL ;
 
#line 9 "connect.pgc"
 char * insertS = NULL ;
 
#line 10 "connect.pgc"
 char * secondD = NULL ;
 
#line 12 "connect.pgc"
 int yearno , ht , wt , chest , sex ;
/* exec sql end declare section */
#line 13 "connect.pgc"


void execute() {
  { ECPGprepare(__LINE__, NULL, 0, "myst", query);}
#line 16 "connect.pgc"

  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_execute, "myst", ECPGt_EOIT, 
	ECPGt_char,&(c),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 17 "connect.pgc"

}

void execute_loaction() {
  size_t len = 500;
  getline(&query, &len, stdin);
  { ECPGprepare(__LINE__, NULL, 0, "myst", query);}
#line 23 "connect.pgc"

  /* declare cursor1 cursor for $1 */
#line 24 "connect.pgc"

  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor1 cursor for $1", 
	ECPGt_char_variable,(ECPGprepared_statement(NULL, "myst", __LINE__)),(long)1,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 25 "connect.pgc"

  /* exec sql whenever not found  break ; */
#line 26 "connect.pgc"

  while (1) {
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor1", ECPGt_EOIT, 
	ECPGt_char,&(a),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(b),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(c),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(d),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 28 "connect.pgc"

if (sqlca.sqlcode == ECPG_NOT_FOUND) break;}
#line 28 "connect.pgc"

    printf("%s %s %s %s\n", a, b, c, d);
  }
  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor1", ECPGt_EOIT, ECPGt_EORT);}
#line 31 "connect.pgc"

  { ECPGdeallocate(__LINE__, 0, NULL, "myst");}
#line 32 "connect.pgc"

}

void insert_data() {

  query = malloc(sizeof(char) * 1000);
  name = malloc(sizeof(char) * 1000);
  insertS = malloc(sizeof(char) * 1000);
  secondD = malloc(sizeof(char) * 1000);

  size_t len = 500;
  char *id = NULL;
  id = malloc(sizeof(char) * 1000);
  getline(&id, &len, stdin);
  strcpy(insertS, "Insert into soldier values ( '");
  strcat(insertS, id);
  strcat(insertS, "', ");
  getline(&name, &len, stdin);
  strcpy(secondD, " , 'soldier', '2017-04-15', '1999-06-29', '2045-02-21', '34th Mountain Division', 2011, '298144', 0, 175, 90, 75);");
  printf("%s %s\n", name, insertS);
  strcat(insertS, name);
  printf("%s\n", insertS );
  strcat(insertS, secondD);
  printf("%s\n", insertS);
  { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_exec_immediate, insertS, ECPGt_EOIT, ECPGt_EORT);}
#line 56 "connect.pgc"

}

int main() {

    { ECPGconnect(__LINE__, 0, "dbms" , "yashladha" , "iamstudious10" , NULL, 0); }
#line 61 "connect.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set search_path to armydb", ECPGt_EOIT, ECPGt_EORT);}
#line 62 "connect.pgc"

    printf("Set search path to armydb\n");

    /* EXEC SQL select count(pincode) into :c from location; */
    /* printf("%d\n", c); */
    /* EXEC SQL select count(soldier.id) into :c from soldier inner join soldier as sold2 on soldier.birthplacepincode = sold2.birthplacepincode where soldier.squadno in ( */
    /* select squadno from soldier where soldier.id = 49158 ); */
    // execute_loaction();
    insert_data();
    { ECPGtrans(__LINE__, NULL, "commit");}
#line 71 "connect.pgc"

    { ECPGdisconnect(__LINE__, "ALL");}
#line 72 "connect.pgc"

    return 0;
}
