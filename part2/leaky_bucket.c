#include <stdio.h>

// Function to find the minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int bucketSize, leakRate, time, packetsDropped = 0;
    int packetsInBucket = 0; // Current packets in the bucket
    int incomingPackets;     // Packets arriving at the current second

    // Input: Bucket size and leak rate
    printf("Enter the bucket size: ");
    scanf("%d", &bucketSize);

    printf("Enter the leak rate (packets sent per second): ");
    scanf("%d", &leakRate);

    // Input: Simulation time
    printf("Enter the number of seconds to simulate: ");
    scanf("%d", &time);

    printf("\nSecond | Incoming Packets | Sent Packets | Remaining Packets | Dropped Packets\n");
    printf("-------|-------------------|--------------|--------------------|-----------------\n");

    // Simulate for each second
    for (int t = 1; t <= time; t++) {
        // Input packets arriving in the current second
        printf("Enter packets arriving at second %d: ", t);
        scanf("%d", &incomingPackets);

        // Add incoming packets to the bucket
        packetsInBucket += incomingPackets;

        // Check for overflow
        if (packetsInBucket > bucketSize) {
            packetsDropped = packetsInBucket - bucketSize; // Calculate dropped packets
            packetsInBucket = bucketSize;                 // Bucket is full
        } else {
            packetsDropped = 0; // No packets dropped
        }

        // Send packets at the leak rate
        int packetsSent = min(leakRate, packetsInBucket);
        packetsInBucket -= packetsSent; // Update remaining packets in the bucket

        // Print the current state
        printf("%6d | %17d | %12d | %18d | %16d\n",
               t, incomingPackets, packetsSent, packetsInBucket, packetsDropped);
    }

    // Process remaining packets in the bucket after time ends
    while (packetsInBucket > 0) {
        int packetsSent = min(leakRate, packetsInBucket);
        packetsInBucket -= packetsSent;

        // Print the remaining state
        printf("%6d | %17d | %12d | %18d | %16d\n",
               ++time, 0, packetsSent, packetsInBucket, 0);
    }

    return 0;
}
