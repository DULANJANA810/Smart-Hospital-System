#include <stdio.h>
#include "patient.h"
#include "bed.h"
#include "file_handler.h"
#include "billing.h"

void displayMenu() {
    printf("\n===== SMART HOSPITAL SYSTEM =====\n");
    printf("1. Register New Patient\n");
    printf("2. View Bed Occupancy\n");
    printf("3. Display Patients by Priority\n");
    printf("4. Generate Reports\n");
    printf("5. Save Data to File\n");
    printf("6. Load Data from File\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

void generateReports() {
    printf("\n===== SYSTEM REPORTS =====\n");

    int crit = 0, urg = 0, norm = 0;
    float totalRevenue = 0, totalDiscount = 0;
    int topIdx = -1;
    float topBill = 0;

    for (int i = 0; i < patientCount; i++) {
        if (patientUrgency[i] == 3) crit++;
        else if (patientUrgency[i] == 2) urg++;
        else norm++;

        float base = SPECIALTY_FEES[patientSpecialty[i]];
        float sur = (patientUrgency[i]==3)?base*0.5:(patientUrgency[i]==2)?base*0.25:0;
        float wc = (patientWard[i]>=0)?patientDays[i]*WARD_RATES[patientWard[i]]:0;
        float gross = base + sur + wc;
        float disc = (patientAges[i]<5||patientAges[i]>65)?gross*0.15:0;

        totalRevenue += (gross - disc);
        totalDiscount += disc;

        if ((gross - disc) > topBill) {
            topBill = gross - disc;
            topIdx = i;
        }
    }

    printf("\n1. Total Patients: %d\n", patientCount);
    printf("   Critical: %d | Urgent: %d | Normal: %d\n", crit, urg, norm);

    printf("\n2. Total Revenue: LKR %.2f\n", totalRevenue);
    printf("   Total Discounts: LKR %.2f\n", totalDiscount);

    printf("\n3. Bed Occupancy per Ward:\n");
    for (int w = 0; w < MAX_WARDS; w++)
        printf("   %s: %.1f%%\n", WARD_NAMES[w], getBedOccupancyPercentage(w));

    if (topIdx >= 0)
        printf("\n4. Highest Payer: %s (LKR %.2f)\n",
               patientNames[topIdx], topBill);
}

int main() {
    initializeBeds();
    loadBedStatus();

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerPatient(); appendPatientRecord(patientCount-1); break;
            case 2: displayBedOccupancy(); break;
            case 3: sortPatientsByPriority(); break;
            case 4: generateReports(); break;
            case 5: saveBedStatus(); break;
            case 6: loadBedStatus(); break;
            case 7: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 7);

    return 0;
}
