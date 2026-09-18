#include <stdio.h>
#include "bed.h"
#include "patient.h"

void initializeBeds() {
    for (int w = 0; w < MAX_WARDS; w++)
        for (int b = 0; b < MAX_BEDS; b++)
            bedOccupancy[w][b] = 0;
}

int findAvailableBed(int wardIdx) {
    for (int b = 0; b < WARD_CAPACITY[wardIdx]; b++) {
        if (bedOccupancy[wardIdx][b] == 0) return b;
    }
    return -1;
}

void displayBedOccupancy() {
    printf("\n===== BED OCCUPANCY STATUS =====\n");
    for (int w = 0; w < MAX_WARDS; w++) {
        printf("\n%s (Capacity: %d)\n", WARD_NAMES[w], WARD_CAPACITY[w]);
        printf("Beds: ");
        for (int b = 0; b < WARD_CAPACITY[w]; b++) {
            printf("[%s] ", bedOccupancy[w][b] ? "X" : " ");
        }
        printf("\n");
        printf("Occupancy: %.1f%%\n", getBedOccupancyPercentage(w));
    }
}

float getBedOccupancyPercentage(int wardIdx) {
    int occupied = 0;
    for (int b = 0; b < WARD_CAPACITY[wardIdx]; b++)
        if (bedOccupancy[wardIdx][b]) occupied++;
    return (occupied * 100.0) / WARD_CAPACITY[wardIdx];
}
