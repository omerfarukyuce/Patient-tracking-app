#include <stdio.h>
#include <stdlib.h>

struct Patient {
    int id;
    char name[20];
    int age;
    char illness[20];
};

struct Patient emptyPatient = {0, "", 0, ""};
struct Patient patient;

FILE *filePtr;

void initializeRecords() {
    if ((filePtr = fopen("patientRecords.dat", "w")) != NULL) {
        for (int i = 0; i < 100; i++) {
            fwrite(&emptyPatient, sizeof(struct Patient), 1, filePtr);
        }
        printf("Space allocated for 100 patient records.\n");
        fclose(filePtr);
    } else {
        printf("Error creating file!\n");
    }
}

void addPatient() {
    int patientID;
    if ((filePtr = fopen("patientRecords.dat", "r+")) != NULL) {
        printf("Enter patient ID: ");
        scanf("%d", &patientID);
        fseek(filePtr, (patientID - 1) * sizeof(struct Patient), SEEK_SET);
        fread(&patient, sizeof(struct Patient), 1, filePtr);

        if (patient.id != 0) {
            printf("Patient with ID %d already exists.\n", patientID);
        } else if (patientID > 100 || patientID < 1) {
            printf("Patient IDs must be between 1 and 100.\n");
        } else {
            printf("Enter Name / Age / Illness: ");
            scanf("%s %d %s", patient.name, &patient.age, patient.illness);
            patient.id = patientID;
            fseek(filePtr, (patientID - 1) * sizeof(struct Patient), SEEK_SET);
            fwrite(&patient, sizeof(struct Patient), 1, filePtr);
            printf("Record added successfully.\n");
        }
        fclose(filePtr);
    } else {
        printf("Error opening file!\n");
    }
}

void deletePatient() {
    int patientID;
    if ((filePtr = fopen("patientRecords.dat", "r+")) != NULL) {
        printf("Enter patient ID to delete: ");
        scanf("%d", &patientID);
        fseek(filePtr, (patientID - 1) * sizeof(struct Patient), SEEK_SET);
        fread(&patient, sizeof(struct Patient), 1, filePtr);

        if (patient.id == 0) {
            printf("No record found for patient ID %d.\n", patientID);
        } else if (patientID > 100 || patientID < 1) {
            printf("Patient IDs must be between 1 and 100.\n");
        } else {
            fseek(filePtr, (patientID - 1) * sizeof(struct Patient), SEEK_SET);
            fwrite(&emptyPatient, sizeof(struct Patient), 1, filePtr);
            printf("Record deleted successfully.\n");
        }
        fclose(filePtr);
    } else {
        printf("Error opening file!\n");
    }
}

void updatePatient() {
    int patientID;
    if ((filePtr = fopen("patientRecords.dat", "r+")) != NULL) {
        printf("Enter patient ID to update: ");
        scanf("%d", &patientID);
        fseek(filePtr, (patientID - 1) * sizeof(struct Patient), SEEK_SET);
        fread(&patient, sizeof(struct Patient), 1, filePtr);

        if (patient.id == 0) {
            printf("No record found for patient ID %d.\n", patientID);
        } else if (patientID > 100 || patientID < 1) {
            printf("Patient IDs must be between 1 and 100.\n");
        } else {
            printf("\nCurrent details of patient ID %d:\n", patientID);
            printf("Name    : %s\n", patient.name);
            printf("Age     : %d\n", patient.age);
            printf("Illness : %s\n", patient.illness);

            printf("Enter new Name / Age / Illness: ");
            scanf("%s %d %s", patient.name, &patient.age, patient.illness);
            patient.id = patientID;
            fseek(filePtr, (patientID - 1) * sizeof(struct Patient), SEEK_SET);
            fwrite(&patient, sizeof(struct Patient), 1, filePtr);
            printf("Record updated successfully.\n");
        }
        fclose(filePtr);
    } else {
        printf("Error opening file!\n");
    }
}

void searchPatient() {
    int patientID;
    if ((filePtr = fopen("patientRecords.dat", "r")) != NULL) {
        printf("Enter patient ID to search: ");
        scanf("%d", &patientID);
        fseek(filePtr, (patientID - 1) * sizeof(struct Patient), SEEK_SET);
        fread(&patient, sizeof(struct Patient), 1, filePtr);

        if (patient.id == 0) {
            printf("No record found for patient ID %d.\n", patientID);
        } else {
            printf("\nDetails of patient ID %d:\n", patientID);
            printf("Name    : %s\n", patient.name);
            printf("Age     : %d\n", patient.age);
            printf("Illness : %s\n", patient.illness);
        }
        fclose(filePtr);
    } else {
        printf("Error opening file!\n");
    }
}

void printAllPatients() {
    if ((filePtr = fopen("patientRecords.dat", "r")) != NULL) {
        printf("ID\tName\t\t\tAge\tIllness\n");
        printf("-------------------------------\n");
        while (fread(&patient, sizeof(struct Patient), 1, filePtr)) {
            if (patient.id != 0) {
                printf("%d\t%-15s\t%d\t%s\n", patient.id, patient.name, patient.age, patient.illness);
            }
        }
        fclose(filePtr);
    } else {
        printf("Error opening file!\n");
    }
}

int main() {
    int choice = -1;
    while (choice != 0) {
        printf("\nHospital Patient Management System\n");
        printf("1. Add Patient\n");
        printf("2. Delete Patient\n");
        printf("3. Update Patient\n");
        printf("4. Search Patient\n");
        printf("5. Print All Patients\n");
        printf("6. Initialize Patient Records (Reset)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid selection. Please try again.\n");
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: addPatient(); break;
            case 2: deletePatient(); break;
            case 3: updatePatient(); break;
            case 4: searchPatient(); break;
            case 5: printAllPatients(); break;
            case 6: initializeRecords(); break;
            case 0: printf("Exiting the system...\n"); break;
            default: printf("Invalid selection. Please try again.\n");
        }
    }

    return 0;
}
