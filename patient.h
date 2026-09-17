#ifndef PATIENT_H
#define PATIENT_H


#define MAX_PATIENTS 100
#define MAX_NAME_LEN 50
#define MAX_SPECIALTIES 4
#define MAX_WARDS 4
#define MAX_BEDS 20


extern const char SPECIALTY_NAMES[4][30];
extern const float SPECIALTY_FEES[4];
extern const int SPECIALTY_TIMES[4];
extern const int SPECIALTY_CAPS[4];


extern const char WARD_NAMES[4][30];
extern const float WARD_RATES[4];
extern const int WARD_CAPACITY[4];


extern char patientNames[MAX_PATIENTS][MAX_NAME_LEN];
extern int patientAges[MAX_PATIENTS];
extern int patientUrgency[MAX_PATIENTS];
extern int patientSpecialty[MAX_PATIENTS];
extern int patientWard[MAX_PATIENTS];
extern int patientDays[MAX_PATIENTS];
extern int patientBedNum[MAX_PATIENTS];
extern int patientCount;


extern int bedOccupancy[MAX_WARDS][MAX_BEDS];


extern int specialtyQueue[MAX_SPECIALTIES];


void registerPatient();
void displayAllPatients();
void sortPatientsByPriority();

#endif
