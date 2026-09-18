#include <stdio.h>
#include "file_handler.h"
#include "patient.h"

void saveBedStatus() {
    FILE *fp = fopen("beds_status.txt", "w");
    if (!fp) { printf("Error saving beds!\n"); return; }

    for (int w = 0; w < MAX_WARDS; w++) {
        for (int b = 0; b < WARD_CAPACITY[w]; b++) {
            fprintf(fp, "%d ", bedOccupancy[w][b]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Bed status saved to beds_status.txt\n");
}

void loadBedStatus() {
    FILE *fp = fopen("beds_status.txt", "r");
    if (!fp) { printf("No saved bed data found.\n"); return; }

    for (int w = 0; w < MAX_WARDS; w++) {
        for (int b = 0; b < WARD_CAPACITY[w]; b++) {
            fscanf(fp, "%d", &bedOccupancy[w][b]);
        }
    }
    fclose(fp);
    printf("Bed status loaded.\n");
}

void appendPatientRecord(int i) {
    FILE *fp = fopen("patient_records.txt", "a");
    if (!fp) { printf("Error saving record!\n"); return; }

    float base = SPECIALTY_FEES[patientSpecialty[i]];
    float surcharge = (patientUrgency[i] == 3) ? base * 0.5 :
                      (patientUrgency[i] == 2) ? base * 0.25 : 0;
    float wardCost = (patientWard[i] >= 0) ? patientDays[i] * WARD_RATES[patientWard[i]] : 0;
    float gross = base + surcharge + wardCost;
    float disc = (patientAges[i] < 5 || patientAges[i] > 65) ? gross * 0.15 : 0;

    fprintf(fp, "PAT-%d | %s | Age:%d | Urgency:%d | Final:LKR %.2f\n",
            1000 + i, patientNames[i], patientAges[i],
            patientUrgency[i], gross - disc);
    fclose(fp);
}
