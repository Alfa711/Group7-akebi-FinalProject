#include <stdio.h>
#include <string.h>

#define DAYS 7

typedef enum {
    BAD, AVERAGE, GOOD, EXCELLENT
} HealthStatus;

typedef enum {
    MALE, FEMALE
} Gender;

typedef enum {
    CHILD, TEENAGER, ADULT, OLD
} AgeGroup;

typedef union {
    char reminder[100];
} Note;

typedef struct {
    int drinkWater;
    float sleepHours;
    float exerciseMinutes;
    HealthStatus status;
    Note notes;
} HealthRecord;

typedef struct {
    int minWater;
    float minSleep;
    float minExercise;
} HealthStandard;

AgeGroup getAgeGroup(int age); // nentuin batas umur pada tiap kelompok umur dan gender
HealthStandard getStandardByAgeGender(int age, Gender gender); // nentuin batas minimal minum air, tidur, dan olahraga pada tiap kelompok umur dan gender
void inputData(HealthRecord records[], int days, HealthStandard std); // utk input data
void printResult(HealthRecord records[], int days, char* name, int age, Gender gender, AgeGroup group); // utk nampilin hasil
void printGender(Gender gender); // print jenis kelamin dari enum Gender
void printAgeGroup(AgeGroup group); // print kelompok umur dari enum AgeGroup


int main() {
    HealthRecord records[DAYS];
    int age;
    char genderChar;
    Gender gender;
    char name[50];

    printf("\n====== Health Tracker After A Week ======\n");

    printf("Enter your name         : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your age          : ");
    scanf("%d", &age);

    while (age <= 0){
        printf("Age can't be 0 or less!\n");
        printf("Enter your age      : ");
        scanf("%d", &age);
    }

    printf("Enter your gender (M/F) : ");
    scanf(" %c", &genderChar);

    while (genderChar != 'M' && genderChar != 'm' && genderChar != 'F' && genderChar != 'f'){
        printf("Invalid input!\n");
        printf("Enter your gender (M/F) : ");
        scanf(" %c", &genderChar);
    }

    gender = (genderChar == 'M' || genderChar == 'm') ? MALE : FEMALE;
    AgeGroup group = getAgeGroup(age);
    //HealthStandard standard = getStandardByAgeGender(age, gender);

    //inputData(records, DAYS, standard);
    printResult(records, DAYS, name, age, gender, group);

    return 0;
}

AgeGroup getAgeGroup(int age) {
    if (age <= 12) return CHILD;
    else if (age <= 18) return TEENAGER;
    else if (age <= 64) return ADULT;
    else return OLD;
}

HealthStandard getStandardByAgeGender(int age, Gender gender) {
    HealthStandard standard;

    if (age <= 12) {
        standard.minWater = (gender == MALE) ? 7 : 6;
        standard.minSleep = (gender == MALE) ? 9.5 : 10.0;
        standard.minExercise = 60;
    } else if (age <= 18) {
        standard.minWater = (gender == MALE) ? 8 : 7;
        standard.minSleep = (gender == MALE) ? 8.5 : 9.0;
        standard.minExercise = 55;
    } else if (age <= 64) {
        standard.minWater = (gender == MALE) ? 10 : 8;
        standard.minSleep = (gender == MALE) ? 7.5 : 8.0;
        standard.minExercise = 30;
    } else {
        standard.minWater = (gender == MALE) ? 8 : 6;
        standard.minSleep = (gender == MALE) ? 7.0 : 7.5;
        standard.minExercise = 20;
    }

    return standard;
}

void inputData(HealthRecord records[], int days, HealthStandard standard) {
    for (int i = 0; i < days; i++) {
        printf("\n----------------- Day %d -----------------\n", i + 1);

        // Input Drink Water
        int valid = 0;
        while (!valid) {
            printf("Drink water (glasses, max 30)        : ");
            if (scanf("%d", &records[i].drinkWater) == 1 && 
                records[i].drinkWater >= 0 && records[i].drinkWater <= 30) {
                valid = 1;
            } else {
                printf("Invalid input!\n");
                while (getchar() != '\n'); // membersihkan buffer input
            }
        }


        // Input Sleep Hours
        valid = 0; 
        while (!valid) { 
            printf("Sleep hours (max 24)                 : ");
            if (scanf("%f", &records[i].sleepHours) == 1 && // sama dengan 1 agar hanya input angka yg bisa dimasukkan
                records[i].sleepHours >= 0 && records[i].sleepHours <= 24) {
                valid = 1;
            } else {
                printf("Invalid input! Please enter hours between 0-24.\n");
                while (getchar() != '\n'); // membersihkan buffer input
            }
        }

        // Input Exercise Minutes
        valid = 0;  
        while (!valid) {
            printf("Exercise duration (minutes, max 300) : ");
            if (scanf("%f", &records[i].exerciseMinutes) == 1 && 
                records[i].exerciseMinutes >= 0 && records[i].exerciseMinutes <= 300) {
                valid = 1;
            } else {
                printf("Invalid input! Please enter minutes between 0-300.\n");
                while (getchar() != '\n'); // membersihkan buffer input
            }
        }

        // menentukan health status
        if (records[i].drinkWater >= standard.minWater + 2 &&
            records[i].sleepHours >= standard.minSleep &&
            records[i].exerciseMinutes >= standard.minExercise) {
            records[i].status = EXCELLENT;
        } else if (records[i].drinkWater >= standard.minWater &&
                   records[i].sleepHours >= standard.minSleep - 1 &&
                   records[i].exerciseMinutes >= standard.minExercise - 15) {
            records[i].status = GOOD;
        } else if (records[i].drinkWater >= standard.minWater - 1 &&
                   records[i].sleepHours >= standard.minSleep - 2 &&
                   records[i].exerciseMinutes >= standard.minExercise - 20) {
            records[i].status = AVERAGE;
        } else {
            records[i].status = BAD;
        }
    }
}

void printResult(HealthRecord records[], int days, char* name, int age, Gender gender, AgeGroup group) {
    printf("\n========= Weekly Health Summary =========\n");
    printf("Name        : %s\n", name);
    printf("Age         : %d\n", age);
    printf("Gender      : "); printGender(gender);
    printf("Age Group   : "); printAgeGroup(group);

    for (int i = 0; i < days; i++) {
        printf("\nDay %d:\n", i + 1);
        printf(" Water    : %d glasses\n", records[i].drinkWater);
        printf(" Sleep    : %.2f hours\n", records[i].sleepHours);
        printf(" Exercise : %d minutes\n", (int)records[i].exerciseMinutes);
        printf(" Status   : ");
        printStatus(records[i].status);
    }

    printf("\nAverage Drink Water : %.2f glasses\n", calculateAverageDrink(records, days));
    printf("Average Sleep       : %.2f hours\n", calculateAverageSleep(records, days));
    printf("Average Exercise    : %.2f minutes\n", calculateAverageExercise(records, days));

    HealthStatus finalStatus = calculateFinalStatus(records, days);
    printf("Final Weekly Status : ");
    printStatus(finalStatus);

    HealthRecord finalRecord;
    finalRecord.status = finalStatus;
    analyzeStatus(&finalRecord);
}

void printGender(Gender gender) {
    if (gender == MALE)
        printf("Male\n");
    else
        printf("Female\n");
}

void printAgeGroup(AgeGroup group) {
    switch (group) {
        case CHILD: printf("Child\n"); break;
        case TEENAGER: printf("Teenager\n"); break;
        case ADULT: printf("Adult\n"); break;
        case OLD: printf("Old\n"); break;
    }
}
