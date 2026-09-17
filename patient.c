#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "bed.h"
#include "billing.h"


const char SPECIALTY_NAMES[4][30] = {
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};
const float SPECIALTY_FEES[4] = {1500.00, 2500.00, 4500.00, 5000.00};
const int SPECIALTY_TIMES[4] = {15, 20, 30, 30};
const int SPECIALTY_CAPS[4] = {30, 20, 12, 10};

const char WARD_NAMES[4][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};
const float WARD_RATES[4] = {3000.00, 6000.00, 12000.00, 25000.00};
const int WARD_CAPACITY[4] = {20, 10, 10, 5};


char patientNames[MAX_PATIENTS][MAX_NAME_LEN];
int patientAges[MAX_PATIENTS];
int patientUrgency[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int patientDays[MAX_PATIENTS];
int patientBedNum[MAX_PATIENTS];
int patientCount = 0;

int bedOccupancy[MAX_WARDS][MAX_BEDS];
int specialtyQueue[MAX_SPECIALTIES] = {0, 0, 0, 0};


void registerPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient limit reached!\n");
        return;
    }

    int i = patientCount;

    printf("\n===== PATIENT REGISTRATION =====\n");
    printf("Patient Name: ");
    scanf(" %[^\n]", patientNames[i]);

    printf("Age: ");
    scanf("%d", &patientAges[i]);

    printf("Urgency Level (1=Normal, 2=Urgent, 3=Critical): ");
    scanf("%d", &patientUrgency[i]);

    printf("\nSpecialty Options:\n");
    for (int s = 0; s < 4; s++) {
        printf("%d. %s - LKR %.2f\n", s+1, SPECIALTY_NAMES[s], SPECIALTY_FEES[s]);
    }
    printf("Select Specialty ID (1-4): ");
    scanf("%d", &patientSpecialty[i]);
    patientSpecialty[i]--;

    printf("\nAdmitted to Ward? (1=Yes, 0=No): ");
    int admitted;
    scanf("%d", &admitted);

    if (admitted == 1) {
        printf("Ward ID (1=General, 2=Paediatric, 3=Surgical, 4=ICU): ");
        scanf("%d", &patientWard[i]);
        patientWard[i]--;

        printf("Days Admitted: ");
        scanf("%d", &patientDays[i]);

        int bed = findAvailableBed(patientWard[i]);
        if (bed == -1) {
            printf("No beds available in this ward!\n");
            patientWard[i] = -1;
            patientDays[i] = 0;
            patientBedNum[i] = -1;
        } else {
            bedOccupancy[patientWard[i]][bed] = 1;
            patientBedNum[i] = bed;
        }
    } else {
        patientWard[i] = -1;
        patientDays[i] = 0;
        patientBedNum[i] = -1;
    }

    patientCount++;
    printf("\nPatient registered successfully! ID: PAT-%d\n", 1000 + i);

    printBill(i);
    specialtyQueue[patientSpecialty[i]]++;
}


void sortPatientsByPriority() {
    int order[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) order[i] = i;

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            int a = order[j], b = order[j+1];
            if (patientUrgency[a] < patientUrgency[b] ||
               (patientUrgency[a] == patientUrgency[b] && a > b)) {
                int temp = order[j];
                order[j] = order[j+1];
                order[j+1] = temp;
            }
        }
    }

    printf("\n===== PATIENTS BY PRIORITY =====\n");
    for (int i = 0; i < patientCount; i++) {
        int p = order[i];
        printf("PAT-%d | %s | Urgency: %d | Specialty: %s\n",
               1000 + p, patientNames[p], patientUrgency[p],
               SPECIALTY_NAMES[patientSpecialty[p]]);
    }
}


void displayAllPatients() {
    printf("\n===== ALL REGISTERED PATIENTS =====\n");
    if (patientCount == 0) {
        printf("No patients registered yet.\n");
        return;
    }
    for (int i = 0; i < patientCount; i++) {
        printf("PAT-%d | %s | Age: %d | Urgency: %d\n",
               1000 + i, patientNames[i], patientAges[i], patientUrgency[i]);
    }
}
