#ifndef BED_H
#define BED_H

void initializeBeds();
int findAvailableBed(int wardIdx);
void displayBedOccupancy();
float getBedOccupancyPercentage(int wardIdx);

#endif
