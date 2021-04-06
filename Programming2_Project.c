#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#define MaxPatients 35 //define the maximum amount of patient the syste can keep track of
#define MaxRooms 21
#define currentYear 2021

typedef struct{
   	char FirstName[15];
	char LastName[15];	
}FullName;

// add patient				
typedef struct{
	int IdNumber;
   	FullName Name;
   	char covidStatus[9];
	int birthYear;
   	char status[9];	
}Patient; 
Patient PATIENTS[MaxPatients], TempPatient;// array for Maximum number of  PATIENTS"
FILE*Patient_pointer;

typedef struct{
	int roomNumber;
   	char respirator[10];
	int numberOfBeds;
	char assignedPersonel[6];
	int IdNumber[5];	
}Room;
Room ROOMS[MaxRooms];

FILE*Room_pointer;

void Menu();
void ViewPatients(char viewBy[]);// function used to display patent(s) details
void Display(int i);
void printStar(int n);
void sort(int patient_index, char sortBy[]);
void roomAdmittedTo(int patientID);
void AddPatient(); 
void AddRoom();
void AIassign(int index);
void removeFromRoom(int patientID);
void addToRoom(int room_index, int patientID);
void ChangePatientStatus();
void roomAdmittanceByAgeReport();
void admittedPatientListReport();
void covidStatusReport();
void write_to_file();// write data to sequential file
void read_from_file();// read data from sequential file

int patient_index = 0, room_index = 0;
char roomFile[200];
char patientFile[200];



int main(){
	read_from_file();
   	Menu();
   	return 0;
}

//____________________________________________
void Menu(){    // main menu
	int option;
	
  	printf("\n");
   	printf("+===================================+\n");
  	printf("|                                   |\n");
   	printf("|  1. Add a Patient                 |\n");
   	printf("|  2. Add a Room                    |\n");
   	printf("|  3. Change Patient Status         |\n");
   	printf("|  4. Room Admittance By Age Report |\n");
   	printf("|  5. Admitted Patient List Report  |\n");
   	printf("|  6. Covid Status Report           |\n");
   	printf("|  0. Save & Exit                   |\n");
   	printf("|                                   |\n");
  	printf("+===================================+\n");
   	printf("|  Select an Option [0..6]          |\n");
   	printf("+===================================+\n");
   	scanf("%d", &option);

	switch (option){ 
         case 0:
                write_to_file();
				break;
      	case 1: 
			    AddPatient(); 
                Menu();
				break;
      	case 2: 
                AddRoom(); 
                Menu();
				break;
      	case 3: 
		        ChangePatientStatus();
                Menu();
		        break;
		case 4: 
		        roomAdmittanceByAgeReport();
                Menu();
		        break;
		case 5: 
		        admittedPatientListReport();
                Menu();
		        break;
		case 6: 
		        covidStatusReport();
                Menu();
		        break;
		   default:
				printf("\n  INVALID OPTION*");
	}
}  

void AddPatient(){
      
      printf("\n\n Enter Id Number:\n\t");
      scanf("%d",&PATIENTS[patient_index].IdNumber);
      
      printf("\n\n Enter Firstname:\n\t");
      scanf("%s",PATIENTS[patient_index].Name.FirstName);
      
      printf("\n\n Enter Lastname:\n\t");
      scanf("%s",PATIENTS[patient_index].Name.LastName);
      
      printf("\n\n Enter covid status:\n\t");
      scanf("%s",PATIENTS[patient_index].covidStatus);
      
      printf("\n\n Enter birth year:\n\t");
      scanf("%d",&PATIENTS[patient_index].birthYear);
      
      printf("\n\n Enter status:\n\t");
      scanf("%s",PATIENTS[patient_index].status);
    
	
	AIassign(patient_index);   
   	patient_index++;  
}


void AddRoom(){
	 system("cls");
	 ROOMS[room_index].roomNumber = room_index+10;
      
      printf("\n\n Enter respirator or None:\n\t");
      scanf("%s",ROOMS[room_index].respirator);
      
      printf("\n\n Enter number of bed(s):\n\t");
      scanf("%d",&ROOMS[room_index].numberOfBeds);
      
      printf("\n\n Enter assigned Personel:\n\t");
      scanf("%s",ROOMS[room_index].assignedPersonel);
      
    room_index++;
}


void AIassign(int index){
	if(strcmp(PATIENTS[index].covidStatus, "none") == 0){
		strcpy(PATIENTS[index].status,"descharged");
	}else{
		int i;
		for(i = 0; i <= room_index; i++){
	      	if(strcmp(PATIENTS[i].covidStatus, "critical") == 0 && strcmp(ROOMS[i].respirator, "respirator") == 0 && strcmp(ROOMS[i].assignedPersonel, "doctor") == 0 && ROOMS[i].numberOfBeds > 0){
	      		addToRoom(i, PATIENTS[index].IdNumber);
	      	}else if(currentYear - PATIENTS[i].birthYear > 60){
			      if(strcmp(PATIENTS[i].covidStatus, "severe") == 0){
						if(strcmp(ROOMS[i].respirator, "respirator") == 0 && strcmp(ROOMS[i].assignedPersonel, "nurse") == 0){	
							addToRoom(i, PATIENTS[index].IdNumber);
						}else if(strcmp(ROOMS[i].respirator, "respirator") == 0){
				      		addToRoom(i, PATIENTS[index].IdNumber);
						}else if(strcmp(ROOMS[i].assignedPersonel, "nurse") == 0){
				      		addToRoom(i, PATIENTS[index].IdNumber);
						}
				}else if(strcmp(PATIENTS[i].covidStatus, "mild") == 0 ||  strcmp(PATIENTS[i].covidStatus, "average") == 0){
					addToRoom(i, PATIENTS[index].IdNumber);
				}
			}else if(currentYear - PATIENTS[i].birthYear >= 40 && currentYear - PATIENTS[i].birthYear <= 60){
				if(strcmp(PATIENTS[i].covidStatus, "severe") == 0 ||  strcmp(PATIENTS[i].covidStatus, "average") == 0){
					if(strcmp(ROOMS[i].assignedPersonel, "nurse") == 0){
				      	addToRoom(i, PATIENTS[index].IdNumber);
					}else{
						addToRoom(i, PATIENTS[index].IdNumber);	
					}
				}else if(strcmp(PATIENTS[i].covidStatus, "mild") == 0){
					addToRoom(i, PATIENTS[index].IdNumber);
				}	
			}else if(currentYear - PATIENTS[i].birthYear >= 20 && currentYear - PATIENTS[i].birthYear <= 39){
				if(strcmp(PATIENTS[i].covidStatus, "severe") == 0){
					if(strcmp(ROOMS[i].assignedPersonel, "doctor") == 0){
						addToRoom(i, PATIENTS[index].IdNumber);
					}
				}else if(strcmp(PATIENTS[i].covidStatus, "mild") == 0 ||  strcmp(PATIENTS[i].covidStatus, "average") == 0){
					addToRoom(i, PATIENTS[index].IdNumber);
				}
			}else if(currentYear - PATIENTS[i].birthYear < 20){
				if(strcmp(PATIENTS[i].covidStatus, "severe") == 0 ||  strcmp(PATIENTS[i].covidStatus, "average") == 0){
					if(strcmp(ROOMS[i].assignedPersonel, "nurse") == 0){
				      	addToRoom(i, PATIENTS[index].IdNumber);
					}else if(strcmp(PATIENTS[i].covidStatus,  "mild") == 0){
				      	addToRoom(i, PATIENTS[index].IdNumber);
					}
				}
			}	
	   	}
	}
	
}

void addToRoom(int room_index, int patientID){
	system("cls");
	int i;
	for (i = 0; i <= 4; i++){
		if(ROOMS[room_index].IdNumber[i] == 0){
			ROOMS[room_index].IdNumber[i] = patientID;
			ROOMS[room_index].numberOfBeds-=1;
			printf("Added to room %d, bed #%d", room_index, i);
			break;
		}	
	}
}

void removeFromRoom(int patientID){
	system("cls");
	int i, x;
	for (i = 0; i <= room_index; i++){
		for (x = 0; x <= 4; x++){
			if(ROOMS[i].IdNumber[x] == patientID){
				ROOMS[i].IdNumber[x] = 0;
				ROOMS[i].numberOfBeds+=1;
				break;
			}
		}
	}
}


void ChangePatientStatus(){// function used to update oatient(s) status
   ViewPatients("All");// display patients to select from
   int id, i;
   	int birthYear;
   	char statusUpdate[9];	
   printf("\n\n Enter ID Number:\n\t");
   scanf("%d",&id);
   for (i = 0; i <= patient_index; i++){
      if(PATIENTS[i].IdNumber == id){// locate the patient to update their status
      printf("\n\n Enter status update:\n\t");
	      	scanf("%s",statusUpdate);
	      	strcpy(PATIENTS[i].covidStatus,statusUpdate);
	      	removeFromRoom(PATIENTS[i].IdNumber);
	        AIassign(i);
	        break;
      }
   }
}


void ViewPatients(char viewBy[]){// function used to display patent(s) details
	int i;
	printf("\n\n  -------------------------------------------------------------------------------------------------------------------------------- ");
   	for (i = 0; i < MaxPatients; i++){
      
      	if((strcmp(PATIENTS[i].Name.FirstName, "")!=0) && (strcmp(PATIENTS[i].Name.LastName, "")!=0)){
         	if(strcmp(viewBy, "All")==0){
        		Display(i);
         	}
			else if(strcmp(viewBy, "Admitted")==0){
         		if(strcmp(PATIENTS[i].status, "admitted")==0){
         			Display(i);
         			roomAdmittedTo(PATIENTS[i].IdNumber);
				}
			}
			else if(strcmp(viewBy, "descharged")==0){
          		if(strcmp(PATIENTS[i].status, "Descharged")==0){
         			Display(i);
				}        		
			}
       
      	}
   	}
    printf("\n  --------------------------------------------------------------------------------------------------------------------------------");
    
}

void Display(int i){
	printf("\n  Patient's ID#: %d", PATIENTS[i].IdNumber);
    printf("\t  Name: %s %s " ,PATIENTS[i].Name.FirstName, PATIENTS[i].Name.LastName);
    printf("\t  Covid Status: %s ",PATIENTS[i].covidStatus);
    printf("\t  Birth year: %d " ,PATIENTS[i].birthYear);
    printf("\t  Status: %s " ,PATIENTS[i].status);
}


void roomAdmittedTo(int patientID){
	int i, x;
	for (i = 0; i <= room_index; i++){
		for (x = 0; x <= 4; x++){
			if(ROOMS[i].IdNumber[x] == patientID){
				printf("\t Room # %d, Bed # %d",ROOMS[i].roomNumber,x+1);
				break;
			}
		}
	}
}


void roomAdmittanceByAgeReport(){
	int overSixty=0;
	int fortyToSixty=0;
	int twentyToThirtyNine=0;
	int underTwenty=0;
	
	system("cls");
	printf("\n Room Admittance By Age Report \n");
	//printf("\n Patients: %d", patient_index);
	//printf("\n Rooms: %d", room_index);
	int r, b, p, i;
	for (r = 0; r < room_index; r++){
		//printf("\n Checking Room #: %d",ROOMS[r].roomNumber);
		for (b = 0; b<= 4; b++){
			//printf("\n Checking Bed #: %d",b+1);
			if(ROOMS[r].IdNumber[b] != 0){
				for(p = 0; p < patient_index; p++){
					if(PATIENTS[p].IdNumber == ROOMS[r].IdNumber[b]){
						if(currentYear - PATIENTS[p].birthYear > 60){
							//printf("\n Found patient over 60");
							overSixty++;
						}else if(currentYear - PATIENTS[p].birthYear >= 40 && currentYear - PATIENTS[p].birthYear <= 60){
							//printf("\n Found patient 40 - 60");
							fortyToSixty++;
						}else if(currentYear - PATIENTS[p].birthYear >= 20 && currentYear - PATIENTS[p].birthYear <= 39){
							//printf("\n Found patient 20 - 39");
							twentyToThirtyNine++;
						}else if(currentYear - PATIENTS[p].birthYear < 20){
							//printf("\n Found patient under 20");
							underTwenty++;
						}
					}
				}
			}
		}
	}
	
	printf("\n  Over 60 |");
	printStar(overSixty);
	printf("\n  40 - 60 |");
	printStar(fortyToSixty);
	printf("\n  20 - 39 |");
	printStar(twentyToThirtyNine);
	printf("\n Under 20 |");
	printStar(underTwenty);

	//printf("\n Found patient 40 - 60");
}

void printStar(int n){
	int i;
	for(i = 0; i < n; i++)
		printf("*");
}


void admittedPatientListReport(){
	system("cls");
	printf("\n Admitted Patient List Report");
	
	sort(patient_index, "Id");
	ViewPatients("Admitted");// display patients to select 
}

void covidStatusReport(){
	system("cls");
	printf("\n Covid Status Report");
	
	
}

 void sort(int patient_index, char sortBy[]){/* bubble sort struct */
	int i, index;

	for(i = 1; i < patient_index; i++){
		for(index = 0; index < patient_index - i; index++){
			if(strcmp(sortBy, "Id")==0){// id assending
        		if(PATIENTS[index].IdNumber > PATIENTS[index+1].IdNumber){
					TempPatient = PATIENTS[index];
					PATIENTS[index] = PATIENTS[index+1];
					PATIENTS[index+1] = TempPatient;
				}	
         	}else if(strcmp(sortBy, "Age")==0){// age assending
        		if(PATIENTS[index].birthYear < PATIENTS[index+1].birthYear){
					TempPatient = PATIENTS[index];
					PATIENTS[index] = PATIENTS[index+1];
					PATIENTS[index+1] = TempPatient;
				}	
         	}
		}
	}
}

 
void write_to_file(){// write patents data to squential files 

    Room_pointer=fopen(roomFile,"w"); 
   	int i; 
    if(Room_pointer!=NULL){
         for(i = 0; i < room_index; i++) {
            fprintf(Room_pointer,"%d %s %d %s %d %d %d %d %d\n", ROOMS[i].roomNumber, ROOMS[i].respirator, ROOMS[i].numberOfBeds, ROOMS[i].assignedPersonel, ROOMS[i].IdNumber[0], ROOMS[i].IdNumber[1], ROOMS[i].IdNumber[2], ROOMS[i].IdNumber[3], ROOMS[i].IdNumber[4]);
        }
        fclose(Room_pointer); 	
	}else{
        printf("\n Rooms File could not be created");
    }
    
    fflush(stdin);
    
    Patient_pointer=fopen(patientFile,"w"); 
   	if(Patient_pointer!=NULL){
         for(i = 0; i < patient_index; i++) {
            fprintf(Patient_pointer,"%d %s %s %s %d  %s \n", PATIENTS[i].IdNumber, PATIENTS[i].Name.FirstName, PATIENTS[i].Name.LastName, PATIENTS[i].covidStatus , PATIENTS[i].birthYear, PATIENTS[i].status);
        }
        fclose(Patient_pointer); 	
	}else{
        printf("\n Patients File could not be created");
    }
}


   			      
void read_from_file(){ // read booking from sequential files
/*
	printf("Enter Location and Name of Patient File: ");
	scanf("%s", patientFile);
	
	printf("Enter Location and Name of Room File: ");
	scanf("%s", roomFile);
	*/
	strcpy(patientFile,"patient.txt");
	strcpy(roomFile,"room.txt");
	system("cls");

  	Room_pointer=fopen(roomFile,"r"); 
  	Patient_pointer=fopen( patientFile ,"r");
  	
   	int i;
   	if(Room_pointer!=NULL){
      	for(i = 0; i < MaxRooms; i++){
        		fscanf(Room_pointer,"%d %s %d %s %d %d %d %d %d\n", &ROOMS[i].roomNumber, ROOMS[i].respirator, &ROOMS[i].numberOfBeds, ROOMS[i].assignedPersonel, &ROOMS[i].IdNumber[0], &ROOMS[i].IdNumber[1], &ROOMS[i].IdNumber[2], &ROOMS[i].IdNumber[3], &ROOMS[i].IdNumber[4]);
        	 if((strcmp(ROOMS[i].respirator, "")!=0) && (strcmp(ROOMS[i].assignedPersonel, "")!=0)){
           	 	room_index = room_index +1;// iterate index to add the next room
         	}
      	}	
      	fclose(Room_pointer); 
   }else{
      	printf("\n Rooms File could not be opened/found");
   }
   
   
    if(Patient_pointer!=NULL){
      for(i = 0; i < MaxPatients; i++){
         fscanf(Patient_pointer,"%d %s %s %s %d  %s \n",&PATIENTS[i].IdNumber, PATIENTS[i].Name.FirstName, PATIENTS[i].Name.LastName, PATIENTS[i].covidStatus , &PATIENTS[i].birthYear, PATIENTS[i].status);
         if((strcmp(PATIENTS[i].Name.FirstName, "")!=0) && (strcmp(PATIENTS[i].Name.LastName, "")!=0)){
            patient_index = patient_index +1;// iterate index to add the next patient
         }
      }
      fclose(Patient_pointer); 
   }else{
      printf("\n Patients File could not be opened/found");
   }
}


