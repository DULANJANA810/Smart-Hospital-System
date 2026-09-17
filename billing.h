#ifndef BILLING_H
#define BILLING_H

float calculateWaitTime(int specialtyIdx);
float calculateEmergencySurcharge(int urgency, float baseFee);
float calculateWardCost(int wardIdx, int days);
float calculateGrossTotal(float base, float surcharge, float wardCost);
float calculateDiscount(int age, float grossTotal);
float calculateFinalAmount(float grossTotal, float discount);
void printBill(int patientIdx);

#endif
