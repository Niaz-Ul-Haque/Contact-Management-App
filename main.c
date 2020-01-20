#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

void printSectionHeader(const char *testName);

int main(void) {
    printSectionHeader("Niaz's Contact Management App Test");
    contactManagerSystem();
    return 0;
}

void printSectionHeader(const char *testName) {
    printf("\n");
    printf("------------------------------------------\n");
    printf("Testing: %s\n", testName);
    printf("------------------------------------------\n");
}

