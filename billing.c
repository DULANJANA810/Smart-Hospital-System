#include <stdio.h>
#include "billing.h"
#include "patient.h"

float calculateWaitTime(int specialtyIdx) {
    return specialtyQueue[specialtyIdx] * SPECIALTY_TIMES[specialtyIdx];
}

float calculateEmergencySurcharge(int urgency, float baseFee) {
    if (urgency == 3) return baseFee * 0.50;
    if (urgency == 2) return baseFee * 0.25;
    return 0.0;
}

float calculateWardCost(int wardIdx, int days) {
    if (wardIdx < 0 || days <= 0) return 0.0;
    return days * WARD_RATES[wardIdx];
}

float calculateGrossTotal(float base, float surcharge, float wardCost) {
    return base + surcharge + wardCost;
}

float calculateDiscount(int age, float grossTotal) {
    if (age < 5 || age > 65) return grossTotal * 0.15;
    return 0.0;
}

float calculateFinalAmount(float grossTotal, float discount) {
    return grossTotal - discount;
}

void printBill(int i) {
    float base = SPECIALTY_FEES[patientSpecialty[i]];
    float surcharge = calculateEmergencySurcharge(patientUrgency[i], base);
    float wardCost = calculateWardCost(patientWard[i], patientDays[i]);
    float gross = calculateGrossTotal(base, surcharge, wardCost);
    float discount = calculateDiscount(patientAges[i], gross);
    float final = calculateFinalAmount(gross, discount);
    float wait = calculateWaitTime(patientSpecialty[i]);

    printf("\n========================================\n");
    printf("   SMART HOSPITAL ADMISSION & BILL\n");
    printf("========================================\n");
    printf("Patient ID      : PAT-%d\n", 1000 + i);
    printf("Patient Name    : %s\n", patientNames[i]);
    printf("Age             : %d Years", patientAges[i]);
    if (patientAges[i] < 5 || patientAges[i] > 65)
        printf(" (15%% Subsidy Eligible)");
    printf("\n");
    printf("Specialty       : %s\n", SPECIALTY_NAMES[patientSpecialty[i]]);

    if (patientWard[i] >= 0)
        printf("Assigned Ward   : %s (Bed #%02d)\n",
               WARD_NAMES[patientWard[i]], patientBedNum[i] + 1);
    else
        printf("Assigned Ward   : OPD (Not Admitted)\n");

    const char *urgLabels[] = {"Normal", "Urgent", "Critical"};
    printf("Urgency Level   : Level %d (%s)\n",
           patientUrgency[i], urgLabels[patientUrgency[i] - 1]);

    printf("\nBase Consultation Fee    : LKR %.2f\n", base);
    printf("Emergency Surcharge      : LKR %.2f (%d%%)\n",
           surcharge, patientUrgency[i] == 3 ? 50 : patientUrgency[i] == 2 ? 25 : 0);
    printf("Ward Stay Cost (%d Days) : LKR %.2f\n", patientDays[i], wardCost);
    printf("----------------------------------------\n");
    printf("Gross Total Bill         : LKR %.2f\n", gross);
    printf("Age Subsidy Discount     : LKR -%.2f (15%%)\n", discount);
    printf("----------------------------------------\n");
    printf("Final Payable Amount     : LKR %.2f\n", final);

    if (wait == 0)
        printf("Estimated Waiting Time   : 0.00 mins (Immediate Attention)\n");
    else
        printf("Estimated Waiting Time   : %.2f mins\n", wait);
    printf("========================================\n");
}
