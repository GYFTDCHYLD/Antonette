#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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


typedef struct{
	int roomNumber;
   	char respirator[10];
	int numberOfBeds;
	char assignedPersonel[6];
	int IdNumber[5];	
}Room;
Room ROOMS[MaxRooms];

FILE*Patient_pointer;

void Menu();
void ViewPatients();// function used to display patent(s) details
void AddPatient(); 
void AddRoom();
void AIassign(int index);
void removeFromRoom(int patientID);
void addToRoom(int room_index, int patientID);
void ChangePatientStatus();
void roomAdmittanceByAgeReport();
void admittedPatientListReport();
void covidStatusReport();

int patient_index = 0, room_index = 0, room_Number = 10;



int main(){
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
                return 0;
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
      
   patient_index++; 
   AIassign(patient_index);  
}


void AddRoom(){
	 ROOMS[room_index].roomNumber = room_Number;
      
      printf("\n\n Enter respirator or None:\n\t");
      scanf("%s",ROOMS[room_index].respirator);
      
      printf("\n\n Enter number of bed(s):\n\t");
      scanf("%d",&ROOMS[room_index].numberOfBeds);
      
      printf("\n\n Enter assigned Personel:\n\t");
      scanf("%s",ROOMS[room_index].assignedPersonel);
      
    room_index++;
}


void AIassign(int index){
	
	if(PATIENTS[index].covidStatus == "none"){
		strcpy(PATIENTS[index].status,"Descharged");
	}else{
		int i;
		for(i = 0; i <= room_index; i++){
	      	if(PATIENTS[i].covidStatus == "critical" && ROOMS[i].respirator == "respirator" && ROOMS[i].assignedPersonel == "doctor" && ROOMS[i].numberOfBeds > 0){
	      		addToRoom(room_index, PATIENTS[index].IdNumber);
	      	}else if(currentYear - PATIENTS[i].birthYear > 60){
			      if(PATIENTS[i].covidStatus == "severe" ){
						if(ROOMS[i].respirator == "respirator" && ROOMS[i].assignedPersonel == "nurse" ){	
							addToRoom(room_index, PATIENTS[index].IdNumber);
						}else if(ROOMS[i].respirator == "respirator" ){
				      		addToRoom(room_index, PATIENTS[index].IdNumber);
						}else if(ROOMS[i].assignedPersonel == "nurse" ){
				      		addToRoom(room_index, PATIENTS[index].IdNumber);
						}
				}else if(PATIENTS[i].covidStatus == "mild" ||  PATIENTS[i].covidStatus == "average"){
					addToRoom(room_index, PATIENTS[index].IdNumber);
				}
			}else if(currentYear - PATIENTS[i].birthYear >= 40 && currentYear - PATIENTS[i].birthYear <= 60){
				if(PATIENTS[i].covidStatus == "severe" ||  PATIENTS[i].covidStatus == "average"){
					if(ROOMS[i].assignedPersonel == "nurse" ){
				      	addToRoom(room_index, PATIENTS[index].IdNumber);
					}else{
						addToRoom(room_index, PATIENTS[index].IdNumber);	
					}
				}else if(PATIENTS[i].covidStatus == "mild"){
					addToRoom(room_index, PATIENTS[index].IdNumber);
				}	
			}else if(currentYear - PATIENTS[i].birthYear >= 20 && currentYear - PATIENTS[i].birthYear <= 39){
				if(PATIENTS[i].covidStatus == "severe" ){
					if(ROOMS[i].assignedPersonel == "doctor"){
						addToRoom(room_index, PATIENTS[index].IdNumber);
					}
				}else if(PATIENTS[i].covidStatus == "mild" ||  PATIENTS[i].covidStatus == "average"){
					addToRoom(room_index, PATIENTS[index].IdNumber);
				}
			}else if(currentYear - PATIENTS[i].birthYear < 20){
					if(PATIENTS[i].covidStatus == "severe" ||  PATIENTS[i].covidStatus == "average"){
					if(ROOMS[i].assignedPersonel == "nurse" ){
				      	addToRoom(room_index, PATIENTS[index].IdNumber);
					}else if(PATIENTS[i].covidStatus == "mild"){
				      	addToRoom(room_index, PATIENTS[index].IdNumber);
					}
				}
			}	
	   	}
	}
	
}

void addToRoom(int room_index, int patientID){
	int i;
	for (i = 0; i <= 4; i++){
		if(ROOMS[room_index].IdNumber[i] == 0){
			ROOMS[room_index].IdNumber[i] = patientID;
			ROOMS[room_index].numberOfBeds-=1;
			break;
		}	
	}
}

void removeFromRoom(int patientID){
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

void sort(int patient_index){/* bubble sort struct */
	int i, index;

	for(i = 1; i < patient_index; i++){
		for(index = 0; index < patient_index - i; index++){
			if(PATIENTS[index].birthYear > PATIENTS[index+1].birthYear){
				TempPatient = PATIENTS[index];
				PATIENTS[index] = PATIENTS[index+1];
				PATIENTS[index+1] = TempPatient;
			}	
		}
	}
}

void ChangePatientStatus(){// function used to update oatient(s) status
   ViewPatients();// display patients to select from
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


void ViewPatients(){// function used to display patent(s) details
	int i;
   for (i = 0; i < MaxPatients; i++){
      
      if((strcmp(PATIENTS[i].Name.FirstName, "")!=0) && (strcmp(PATIENTS[i].Name.LastName, "")!=0)){
         printf("\n\n  --------------------------------------- ");
         printf("\n  Patient's ID#: %d", PATIENTS[i].IdNumber);
         printf("\n  Name: %s %s " ,PATIENTS[i].Name.FirstName, PATIENTS[i].Name.LastName);
         printf("\n  Covid Status: %s ",PATIENTS[i].covidStatus);
         printf("\n  Birth year: %d " ,PATIENTS[i].birthYear);
         printf("\n  Status: %s " ,PATIENTS[i].status);
        printf("\n  --------------------------------------- ");
      }
     
   }
}

void roomAdmittanceByAgeReport(){
	
	
}


void admittedPatientListReport(){
	
	
}

void covidStatusReport(){
	
	
}
