#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_DONORS 100
#define MAX_BLOOD_TYPES 5

// Blood type enumeration
typedef enum {
    A_POSITIVE, A_NEGATIVE, B_POSITIVE, B_NEGATIVE, O_POSITIVE, O_NEGATIVE, AB_POSITIVE, AB_NEGATIVE
} BloodType;

// Blood type names
const char *bloodTypeNames[] = {
    "A Positive", "A Negative", "B Positive", "B Negative", 
    "O Positive", "O Negative", "AB Positive", "AB Negative"
};

// Donor structure
typedef struct {
    int id;
    char name[50];
    int age;
    BloodType bloodType;
} Donor;

// Blood bank structure
typedef struct {
    Donor donors[MAX_DONORS];
    int bloodInventory[MAX_BLOOD_TYPES];
    int donorCount;
} BloodBank;

// Function prototypes
void initializeBloodBank(BloodBank *bank);
void addDonor(BloodBank *bank);
void displayDonors(const BloodBank *bank);
void checkBloodAvailability(const BloodBank *bank);
void donateBlood(BloodBank *bank, int bloodType);

int main() {
    BloodBank bank;
    initializeBloodBank(&bank);

    int choice;
    while (1) {
        printf("\nBlood Bank Management System\n");
        printf("1. Add Donor\n");
        printf("2. Display Donors\n");
        printf("3. Check Blood Availability\n");
        printf("4. Donate Blood\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDonor(&bank);
                break;
            case 2:
                displayDonors(&bank);
                break;
            case 3:
                checkBloodAvailability(&bank);
                break;
            case 4:
                printf("Enter blood type to donate (0 - A Positive, 1 - A Negative, 2 - B Positive, 3 - B Negative, 4 - O Positive, 5 - O Negative, 6 - AB Positive, 7 - AB Negative): ");
                int bloodType;
                scanf("%d", &bloodType);
                if (bloodType < 0 || bloodType >= MAX_BLOOD_TYPES) {
                    printf("Invalid blood type.\n");
                } else {
                    donateBlood(&bank, bloodType);
                }
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

void initializeBloodBank(BloodBank *bank) {
    bank->donorCount = 0;
    for (int i = 0; i < MAX_BLOOD_TYPES; i++) {
        bank->bloodInventory[i] = 0;
    }
}

void addDonor(BloodBank *bank) {
    if (bank->donorCount >= MAX_DONORS) {
        printf("Donor list is full.\n");
        return;
    }

    Donor newDonor;
    newDonor.id = bank->donorCount + 1;
    printf("Enter donor name: ");
    scanf("%s", newDonor.name);
    printf("Enter donor age: ");
    scanf("%d", &newDonor.age);

    printf("Enter blood type (0 - A Positive, 1 - A Negative, 2 - B Positive, 3 - B Negative, 4 - O Positive, 5 - O Negative, 6 - AB Positive, 7 - AB Negative): ");
    int bloodType;
    scanf("%d", &bloodType);
    if (bloodType < 0 || bloodType >= MAX_BLOOD_TYPES) {
        printf("Invalid blood type.\n");
        return;
    }
    newDonor.bloodType = (BloodType)bloodType;

    bank->donors[bank->donorCount] = newDonor;
    bank->bloodInventory[bloodType]++;
    bank->donorCount++;

    printf("Donor added successfully.\n");
}

void displayDonors(const BloodBank *bank) {
    printf("Donor List:\n");
    for (int i = 0; i < bank->donorCount; i++) {
        printf("ID: %d, Name: %s, Age: %d, Blood Type: %s\n", 
               bank->donors[i].id, 
               bank->donors[i].name, 
               bank->donors[i].age, 
               bloodTypeNames[bank->donors[i].bloodType]);
    }
}

void checkBloodAvailability(const BloodBank *bank) {
    printf("Blood Inventory:\n");
    for (int i = 0; i < MAX_BLOOD_TYPES; i++) {
        printf("%s: %d units\n", bloodTypeNames[i], bank->bloodInventory[i]);
    }
}

void donateBlood(BloodBank *bank, int bloodType) {
    if (bloodType < 0 || bloodType >= MAX_BLOOD_TYPES) {
        printf("Invalid blood type.\n");
        return;
    }
    bank->bloodInventory[bloodType]++;
    printf("Blood donated successfully.\n");
}
