/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoVector1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoVector1.h"
#include "IdEcoLog1.h"
#include "IdEcoString1.h"
#include "IEcoLog1FileAffiliate.h"
#include "IdEcoDateTime1.h"
#include "IdEcoComparator1.h"

#include <stdio.h>
#include <time.h>


void zeroOddNumbers(void* elem) {
	int32_t value = *(int32_t*)elem;
	if (value % 2 == 0) {
		*(int32_t*)elem = 0;
	}
	return;
}

void zeroOddDoubleNumbers(void* elem) {
	double_t value = *(double_t*)elem;
	if ((int32_t)value % 2 == 0) {
		*(double_t*)elem = 0.0;
	}
	return;
}


void capitalize(void* elem) {
	char_t* value = *(char_t**)elem;
	if (value == 0) {
		return;
	}
	
	if (value[0] >= 'a' && value[0] <= 'z') {
		value[0] += 'A' - 'a';
	}
	return;
}


void testIntVector(IEcoVector1* pIEcoVector, IEcoMemoryAllocator1* pIMem) {
	char result = 's';
	int32_t sourceArray[] = {1, 2, 3, 4, 5};
	void* curValue = 0;
	int32_t index = 0;
	int32_t* pInt = 0;
	int32_t* pInt1 = 0;
	IEcoVector1* newPIEcoVector1 = 0;
	int16_t isSuccess = 0;
	double_t mean = 0;

	uint32_t size = 0;
	uint32_t i = 0;
	clock_t begin = 0, end = 0;
    double_t time_spent = 0;
	
	printf("***********************************\n");
	printf("Begining of test for integer vector\n");
	pIEcoVector->pVTbl->InitByType(pIEcoVector, ECO_SET_1_INTEGER_TYPE);
	printf("Init is done\n");

	if (pIEcoVector->pVTbl->Get_Comparator(pIEcoVector) != 0) {
        printf("Comparator exist for set\n");
    }
    else {
        printf("Comparator doesn't exist for set\n");
    }

    if (pIEcoVector->pVTbl->IsEmpty(pIEcoVector)) {
        printf("Set is empty\n");
    }
    else {
        printf("Set is not empty\n");
    }

	// Test init from array
	pIEcoVector->pVTbl->FromArray(pIEcoVector, (void**)&sourceArray, sizeof(sourceArray) / sizeof(int32_t));
	printf("\nInit vector from array, size of initialized vector = %d\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	printf("Vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	
	// Test Clear and init from array again
	pIEcoVector->pVTbl->Clear(pIEcoVector);
	printf("\n\nClear vector, new size = %d\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->FromArray(pIEcoVector, (void**)&sourceArray, sizeof(sourceArray) / sizeof(int32_t));

	// Test access by index
	printf("\n\nTest access by index\n");
	curValue = pIEcoVector->pVTbl->At(pIEcoVector, 1);
	if (curValue != 0) {
		printf("Index = 1, found value = %d\n", *(int32_t*)curValue);
	} else {
		printf("Element with this index doesn't exists\n");
	}


	// Test IndexOf
    pInt = (int32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t));
	pInt1 = (int32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t));
    *pInt = 4;
	printf("\n\nTest IndexOf\n");
	
	index = pIEcoVector->pVTbl->IndexOf(pIEcoVector, pInt);
	printf("Value = %d, found index = %d\n", *pInt, index);


	printf("\n\nVector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Insert
	*pInt = 99;
	pIEcoVector->pVTbl->Insert(pIEcoVector, pInt);
	printf("\n\nInsert value %d:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Push
	*pInt = 100;
	pIEcoVector->pVTbl->Push(pIEcoVector, pInt);
	printf("\n\nPush value %d:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test InsertAt
	*pInt = 28;
	pIEcoVector->pVTbl->InsertAt(pIEcoVector, 3, pInt);
	printf("\n\nInsert value %d at index %d:\n", *pInt, 3);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test RemoveAt
	pIEcoVector->pVTbl->RemoveAt(pIEcoVector, 3);
	printf("\n\nRemove value from index %d:\n", 3);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Reverse
	pIEcoVector->pVTbl->Reverse(pIEcoVector);
	printf("\n\nReverse vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Reshape
	pIEcoVector->pVTbl->Reshape(pIEcoVector, pIEcoVector->pVTbl->Size(pIEcoVector) + 2);
	printf("\n\nReshaped vector to %d size:\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	pIEcoVector->pVTbl->Reshape(pIEcoVector, pIEcoVector->pVTbl->Size(pIEcoVector) - 3);
	printf("\n\nReshaped vector to %d size:\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);


	// Test DeepCopy
	newPIEcoVector1 = pIEcoVector->pVTbl->DeepCopy(pIEcoVector);
	printf("\n\nDeep copy of vector:\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);

	// Change an element in new vector
	curValue = newPIEcoVector1->pVTbl->At(newPIEcoVector1, 1);
	if (curValue != 0) {
		*(int32_t*)curValue = 21;
	} else {
		printf("Element with this index doesn't exists\n");
	}
	printf("\nChange value of element from copied vector with index 1 to 21\n");

	// Check that value changed only in new array
	printf("Check that value changed only in new array\n");
	printf("Copy of vector:\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf("\nOld vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Map
	pIEcoVector->pVTbl->Map(pIEcoVector, zeroOddNumbers);
	printf("\n\nMap function that zero odd numbers:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Replace value
	*pInt = 0;
	*pInt1 = -1;
	pIEcoVector->pVTbl->ReplaceValue(pIEcoVector, pInt, pInt1);
	printf("\n\nReplace %d with %d:\n", *pInt, *pInt1);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test AddValue
	*pInt = 100;
	pIEcoVector->pVTbl->AddValue(pIEcoVector, pInt);
	printf("\n\nAdd %d to every element of vector:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test SubValue
	*pInt = 100;
	pIEcoVector->pVTbl->SubValue(pIEcoVector, pInt);
	printf("\n\nSubstract %d from each element of vector:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test MulValue
	*pInt = 100;
	pIEcoVector->pVTbl->MulValue(pIEcoVector, pInt);
	printf("\n\nMultiply by %d each element of vector:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test DivValue
	// Try to divide by zero
	*pInt = 0;
	pIEcoVector->pVTbl->DivValue(pIEcoVector, pInt);
	printf("\n\nDivide each element of vector by %d:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	*pInt = 10;
	pIEcoVector->pVTbl->DivValue(pIEcoVector, pInt);
	printf("\n\nDivide each element of vector by %d:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test ModValue
	*pInt = 3;
	pIEcoVector->pVTbl->ModValue(pIEcoVector, pInt);
	printf("\n\nModValue %d:\n", *pInt);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test AddVector
	*pInt = 3;
	printf("\n\nAdd two vectors | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->AddVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("Error: cannot add vectors:\n");
	}

	// Test SubVector
	*pInt = 3;
	printf("\n\nSub two vectors | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->SubVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("Error: cannot substract vectors:\n");
	}

	// Test MulVector
	printf("\n\nMul two vectors | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->MulVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot multiply vectors:\n");
	}

	isSuccess = newPIEcoVector1->pVTbl->RemoveAt(newPIEcoVector1, 0);
	if (isSuccess == 0) {
		printf("\n\nTry to mul two vectors with different dimentions | ");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
		printf(" | ");
		newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
		printf(" |");
		isSuccess = pIEcoVector->pVTbl->MulVector(pIEcoVector, newPIEcoVector1);
		if (isSuccess == 0) {
			printf("Result:\n");
			pIEcoVector->pVTbl->PrintVector(pIEcoVector);
		} else {
			printf("\nError: cannot multiply vectors\n");
		}
		*pInt = 10;
		isSuccess = newPIEcoVector1->pVTbl->Insert(newPIEcoVector1, pInt);
	}


	printf("\n\nJoin two vectors in append mode | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->Join(pIEcoVector, newPIEcoVector1, 1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot join vectors:\n");
	}

	printf("\n\nJoin two vectors in prepend mode | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->Join(pIEcoVector, newPIEcoVector1, 0);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot join vectors:\n");
	}

	mean = pIEcoVector->pVTbl->Mean(pIEcoVector);
	printf("\n\nCalculate mean of vector %lf:\n", mean);

	pIEcoVector->pVTbl->Clear(pIEcoVector);
	printf("\n\nCheck working time:\n");
	for (size = 1000; size <= 16000; size *= 2) {
		// Test Push
		begin = clock();
		for (i = 0; i < size; i++) {
			pIEcoVector->pVTbl->Push(pIEcoVector, &i);
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("%d PUSHes: %lf s.\n", size, time_spent);
		printf("%d elems PUSH average: %lf s.\n", size, time_spent / size);

		// Test Set
		begin = clock();
		for (i = 0; i < size; ++i) {
			pIEcoVector->pVTbl->Set(pIEcoVector, i, &i);
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("%d Set calls: %lf s.\n", size, time_spent);
		printf("%d elems Set average: %lf s.\n", size, time_spent / size);

		// Test IndexOf
		begin = clock();
		for (i = 0; i < size; ++i) {
			if (pIEcoVector->pVTbl->IndexOf(pIEcoVector, &i) == -1) {
				printf("Value %d not found in vector\n", i);
			}
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("%d IndexOf calls: %lf s.\n", size, time_spent);
		printf("%d elems IndexOf average: %lf s.\n", size, time_spent / size);

		// Test At
		begin = clock();
		for (i = 0; i < size; ++i) {
			pIEcoVector->pVTbl->At(pIEcoVector, i);
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("%d At calls: %lf s.\n", size, time_spent);
		printf("%d elems At average: %lf s.\n", size, time_spent / size);


		// Test Remove
		begin = clock();
		for (i = 0; i < size; ++i) {
			pIEcoVector->pVTbl->RemoveAt(pIEcoVector, i);
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("%d RemoveAt calls: %lf s.\n", size, time_spent);
		printf("%d elems RemoveAt average: %lf s.\n", size, time_spent / size);
		
		pIEcoVector->pVTbl->Clear(pIEcoVector);
	}
}


void testDoubleVector(IEcoVector1* pIEcoVector, IEcoMemoryAllocator1* pIMem) {
	char result = 's';
	double_t sourceArray[] = {1.2, 2.2, 3.2, 4.2, 5.2};
	void* curValue = 0;
	uint32_t index = 0;
	int32_t* pIndex = 0;
	double_t* pDouble = 0;
	double_t* pDouble1 = 0;
	IEcoVector1* newPIEcoVector1 = 0;
	int16_t isSuccess = 0;
	double_t mean = 0;
	
	printf("***********************************\n");
	printf("Begining of test for double vector\n");
	pIEcoVector->pVTbl->InitByType(pIEcoVector, ECO_SET_1_DOUBLE_TYPE);
	printf("Init is done\n");

	if (pIEcoVector->pVTbl->Get_Comparator(pIEcoVector) != 0) {
        printf("Comparator exist for set\n");
    }
    else {
        printf("Comparator doesn't exist for set\n");
    }

    if (pIEcoVector->pVTbl->IsEmpty(pIEcoVector)) {
        printf("Set is empty\n");
    }
    else {
        printf("Set is not empty\n");
    }

	// Test init from array
	pIEcoVector->pVTbl->FromArray(pIEcoVector, (void**)&sourceArray, sizeof(sourceArray) / sizeof(double_t));
	printf("\nInit vector from array, size of initialized vector = %d\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	printf("Vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	
	// Test Clear and init from array again
	pIEcoVector->pVTbl->Clear(pIEcoVector);
	printf("\n\nClear vector, new size = %d\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->FromArray(pIEcoVector, (void**)&sourceArray, sizeof(sourceArray) / sizeof(double_t));

	// Test access by index
	printf("\n\nTest access by index\n");
	curValue = pIEcoVector->pVTbl->At(pIEcoVector, 1);
	if (curValue != 0) {
		printf("Index = 1, found value = %f\n", *(double_t*)curValue);
	} else {
		printf("Element with this index doesn't exists\n");
	}


	// Test IndexOf
    pDouble1 = (double_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(double_t));
	pDouble = (double_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(double_t));
    *pDouble = 2.2;
	printf("\n\nTest IndexOf\n");
	
	index = pIEcoVector->pVTbl->IndexOf(pIEcoVector, pDouble);
	printf("Value = %f, found index = %d\n", *pDouble, index);


	printf("\n\nVector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Insert
	*pDouble = 99;
	pIEcoVector->pVTbl->Insert(pIEcoVector, pDouble);
	printf("\n\nInsert value %f:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Push
	*pDouble = 100;
	pIEcoVector->pVTbl->Push(pIEcoVector, pDouble);
	printf("\n\nPush value %f:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test InsertAt
	*pDouble = 28;
	pIEcoVector->pVTbl->InsertAt(pIEcoVector, 3, pDouble);
	printf("\n\nInsert value %f at index %d:\n", *pDouble, 3);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test RemoveAt
	pIEcoVector->pVTbl->RemoveAt(pIEcoVector, 3);
	printf("\n\nRemove value from index %d:\n", 3);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Reverse
	pIEcoVector->pVTbl->Reverse(pIEcoVector);
	printf("\n\nReverse vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Reshape
	pIEcoVector->pVTbl->Reshape(pIEcoVector, pIEcoVector->pVTbl->Size(pIEcoVector) + 2);
	printf("\n\nReshaped vector to %d size:\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	pIEcoVector->pVTbl->Reshape(pIEcoVector, pIEcoVector->pVTbl->Size(pIEcoVector) - 3);
	printf("\n\nReshaped vector to %d size:\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);


	// Test DeepCopy
	newPIEcoVector1 = pIEcoVector->pVTbl->DeepCopy(pIEcoVector);
	printf("\n\nDeep copy of vector:\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);

	// Change an element in new vector
	curValue = newPIEcoVector1->pVTbl->At(newPIEcoVector1, 1);
	if (curValue != 0) {
		*(double_t*)curValue = 21;
	} else {
		printf("Element with this index doesn't exists\n");
	}
	printf("\nChange value of element from copied vector with index 1 to 21\n");

	// Check that value changed only in new array
	printf("Check that value changed only in new array\n");
	printf("Copy of vector:\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf("\nOld vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Map
	pIEcoVector->pVTbl->Map(pIEcoVector, zeroOddDoubleNumbers);
	printf("\n\nMap function that zero odd numbers:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Replace value
	*pDouble = 0;
	*pDouble1 = -1;
	pIEcoVector->pVTbl->ReplaceValue(pIEcoVector, pDouble, pDouble1);
	printf("\n\nReplace %f with %f:\n", *pDouble, *pDouble1);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test AddValue
	*pDouble = 100;
	pIEcoVector->pVTbl->AddValue(pIEcoVector, pDouble);
	printf("\n\nAdd %f to every element of vector:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test SubValue
	*pDouble = 100;
	pIEcoVector->pVTbl->SubValue(pIEcoVector, pDouble);
	printf("\n\nSubstract %f from each element of vector:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test MulValue
	*pDouble = 100;
	pIEcoVector->pVTbl->MulValue(pIEcoVector, pDouble);
	printf("\n\nMultiply by %f each element of vector:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test DivValue
	// Try to divide by zero
	*pDouble = 0;
	pIEcoVector->pVTbl->DivValue(pIEcoVector, pDouble);
	printf("\n\nDivide each element of vector by %f:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	*pDouble = 10;
	pIEcoVector->pVTbl->DivValue(pIEcoVector, pDouble);
	printf("\n\nDivide each element of vector by %f:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test ModValue
	*pDouble = 3;
	pIEcoVector->pVTbl->ModValue(pIEcoVector, pDouble);
	printf("\n\nModValue %f:\n", *pDouble);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test AddVector
	printf("\n\nAdd two vectors | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->AddVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("Error: cannot add vectors:\n");
	}

	// Test SubVector
	printf("\n\nSub two vectors | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->SubVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("Error: cannot substract vectors:\n");
	}

	// Test MulVector
	printf("\n\nMul two vectors | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->MulVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot multiply vectors:\n");
	}

	isSuccess = newPIEcoVector1->pVTbl->RemoveAt(newPIEcoVector1, 0);
	if (isSuccess == 0) {
		printf("\n\nTry to mul two vectors with different dimentions | ");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
		printf(" | ");
		newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
		printf(" |");
		isSuccess = pIEcoVector->pVTbl->MulVector(pIEcoVector, newPIEcoVector1);
		if (isSuccess == 0) {
			printf("Result:\n");
			pIEcoVector->pVTbl->PrintVector(pIEcoVector);
		} else {
			printf("\nError: cannot multiply vectors\n");
		}
		*pDouble = 10;
		isSuccess = newPIEcoVector1->pVTbl->Insert(newPIEcoVector1, pDouble);
	}


	printf("\n\nJoin two vectors in append mode | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->Join(pIEcoVector, newPIEcoVector1, 1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot join vectors:\n");
	}

	printf("\n\nJoin two vectors in prepend mode | ");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf(" | ");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf(" |\n");
	isSuccess = pIEcoVector->pVTbl->Join(pIEcoVector, newPIEcoVector1, 0);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot join vectors:\n");
	}

	mean = pIEcoVector->pVTbl->Mean(pIEcoVector);
	printf("\n\nCalculate mean of vector %lf:\n", mean);
}


void testCharVector(IEcoVector1* pIEcoVector, IEcoMemoryAllocator1* pIMem) {
	char_t* sourceArray[] = {"one", "two", "three", "four", "five", "six"};
	void* curValue = 0;
	uint32_t index = 0;
	int32_t* pIndex = 0;
	char_t** ppChar = 0;
	char_t** ppChar1 = 0;
	IEcoVector1* newPIEcoVector1 = 0;
	int16_t isSuccess = 0;
	
	printf("***********************************\n");
	printf("Begining of test for string vector\n");
	pIEcoVector->pVTbl->InitByType(pIEcoVector, ECO_SET_1_STRING_TYPE);
	printf("Init is done\n");

	if (pIEcoVector->pVTbl->Get_Comparator(pIEcoVector) != 0) {
        printf("Comparator exist for set\n");
    }
    else {
        printf("Comparator doesn't exist for set\n");
    }

    if (pIEcoVector->pVTbl->IsEmpty(pIEcoVector)) {
        printf("Set is empty\n");
    }
    else {
        printf("Set is not empty\n");
    }

	// Test init from array
	pIEcoVector->pVTbl->FromArray(pIEcoVector, (void**)&sourceArray, sizeof(sourceArray) / sizeof(char_t*));
	printf("\nInit vector from array, size of initialized vector = %d\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	printf("Vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Clear and init from array again
	pIEcoVector->pVTbl->Clear(pIEcoVector);
	printf("\n\nClear vector, new size = %d\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->FromArray(pIEcoVector, (void**)&sourceArray, sizeof(sourceArray) / sizeof(char_t*));

	// Test access by index
	printf("\n\nTest access by index\n");
	curValue = pIEcoVector->pVTbl->At(pIEcoVector, 1);
	if (curValue != 0) {
		printf("Index = 1, found value = %s\n", *((char_t**)curValue));
	} else {
		printf("Element with this index doesn't exists\n");
	}


	// Test IndexOf
    ppChar = (char_t**)pIMem->pVTbl->Alloc(pIMem, sizeof(char_t*));
	ppChar1 = (char_t**)pIMem->pVTbl->Alloc(pIMem, sizeof(char_t*));
    *ppChar = "two";
	printf("\n\nTest IndexOf\n");
	
	index = pIEcoVector->pVTbl->IndexOf(pIEcoVector, ppChar);
	printf("Value = %s, found index = %d\n", *ppChar, index);


	printf("\n\nVector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Insert
	*ppChar = "hundred";
	pIEcoVector->pVTbl->Insert(pIEcoVector, ppChar);
	printf("\n\nInsert value %s:\n", *ppChar);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Push
	*ppChar = "million";
	pIEcoVector->pVTbl->Push(pIEcoVector, ppChar);
	printf("\n\nPush value %s:\n", *ppChar);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test InsertAt
	*ppChar = "twenty";
	pIEcoVector->pVTbl->InsertAt(pIEcoVector, 3, ppChar);
	printf("\n\nInsert value %s at index %d:\n", *ppChar, 3);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test RemoveAt
	pIEcoVector->pVTbl->RemoveAt(pIEcoVector, 3);
	printf("\n\nRemove value from index %d:\n", 3);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Reverse
	pIEcoVector->pVTbl->Reverse(pIEcoVector);
	printf("\n\nReverse vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Reshape
	pIEcoVector->pVTbl->Reshape(pIEcoVector, pIEcoVector->pVTbl->Size(pIEcoVector) + 2);
	printf("\n\nReshaped vector to %d size:\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	pIEcoVector->pVTbl->Reshape(pIEcoVector, pIEcoVector->pVTbl->Size(pIEcoVector) - 3);
	printf("\n\nReshaped vector to %d size:\n", pIEcoVector->pVTbl->Size(pIEcoVector));
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);


	// Test DeepCopy
	newPIEcoVector1 = pIEcoVector->pVTbl->DeepCopy(pIEcoVector);
	printf("\n\nDeep copy of vector:\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);

	// Change an element in new vector
	printf("\nChange value of element from copied vector with index 1 to 'fifty'\n");
	*ppChar = "fifty";
	isSuccess = newPIEcoVector1->pVTbl->Set(newPIEcoVector1, 1, ppChar);
	if (isSuccess != 0) {
		printf("Cannot set value 'fifty' to element with index 1\n");
	}

	// Check that value changed only in new array
	printf("Check that value changed only in new array\n");
	printf("Copy of vector:\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf("\nOld vector:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Map
	pIEcoVector->pVTbl->Map(pIEcoVector, capitalize);
	printf("\n\nMap function that capitalize strings:\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test Replace value
	*ppChar = "Three";
	*ppChar1 = "Thirty";
	pIEcoVector->pVTbl->ReplaceValue(pIEcoVector, ppChar, ppChar1);
	printf("\n\nReplace %s with %s:\n", *ppChar, *ppChar1);
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);

	// Test AddValue
	*ppChar = "three";
	isSuccess = pIEcoVector->pVTbl->AddValue(pIEcoVector, ppChar);
	if (isSuccess != 0) {
		printf("\nAddValue is not enabled for String data type\n");
	}

	// Test SubValue
	isSuccess =pIEcoVector->pVTbl->SubValue(pIEcoVector, ppChar);
	if (isSuccess != 0) {
		printf("\nSubValue is not enabled for String data type\n");
	}

	// Test MulValue
	isSuccess = pIEcoVector->pVTbl->MulValue(pIEcoVector, ppChar);
	if (isSuccess != 0) {
		printf("\nMulValue is not enabled for String data type\n");
	}

	// Test DivValue
	isSuccess = pIEcoVector->pVTbl->DivValue(pIEcoVector, ppChar);
	if (isSuccess != 0) {
		printf("\nDivValue is not enabled for String data type\n");
	}

	// Test ModValue
	isSuccess = pIEcoVector->pVTbl->ModValue(pIEcoVector, ppChar);
	if (isSuccess != 0) {
		printf("\nModValue is not enabled for String data type\n");
	}

	// Test AddVector
	isSuccess = pIEcoVector->pVTbl->AddVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess != 0) {
		printf("\nAddVector is not enabled for String data type\n");
	}

	// Test SubVector
	isSuccess = pIEcoVector->pVTbl->SubVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess != 0) {
		printf("\nSubVector is not enabled for String data type\n");
	}

	// Test MulVector
	isSuccess = pIEcoVector->pVTbl->MulVector(pIEcoVector, newPIEcoVector1);
	if (isSuccess != 0) {
		printf("\nMulVector is not enabled for String data type\n");
	}


	printf("\n\nJoin two vectors in append mode\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf("\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf("\n");
	isSuccess = pIEcoVector->pVTbl->Join(pIEcoVector, newPIEcoVector1, 1);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot join vectors:\n");
	}

	printf("\n\nJoin two vectors in prepend mode\n");
	pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	printf("\n");
	newPIEcoVector1->pVTbl->PrintVector(newPIEcoVector1);
	printf("\n");
	isSuccess = pIEcoVector->pVTbl->Join(pIEcoVector, newPIEcoVector1, 0);
	if (isSuccess == 0) {
		printf("Result:\n");
		pIEcoVector->pVTbl->PrintVector(pIEcoVector);
	} else {
		printf("\nError: cannot join vectors:\n");
	}
}


/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
	/* Указатель на интерфейс работы со строкой */
    IEcoString1* pIString = 0;

    /* Указатель на тестируемый интерфейс */
    IEcoVector1* pIEcoVector1Int = 0;
	IEcoVector1* pIEcoVector1Double = 0;
	IEcoVector1* pIEcoVector1String = 0;



    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

#ifdef ECO_LIB
    /* Регистрация статического компонента для работы с вектором */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoVector1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2A3866FF01C74D03819CFD138812B4A1);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с интерфейсом сравнения */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoComparator1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_C7ED3BA4B6EB4385BBDB3C6AC5C7A394);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
	/* Регистрация статического компонента для работы со строкой */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoString1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_84CC0A7DBABD44EEBE749C9A8312D37E);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoVector1, 0, &IID_IEcoVector1, (void**) &pIEcoVector1Int);
    if (result != 0 && pIEcoVector1Int == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
	
	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoVector1, 0, &IID_IEcoVector1, (void**) &pIEcoVector1Double);
    if (result != 0 && pIEcoVector1Double == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoVector1, 0, &IID_IEcoVector1, (void**) &pIEcoVector1String);
    if (result != 0 && pIEcoVector1String == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	testIntVector(pIEcoVector1Int, pIMem);
	testDoubleVector(pIEcoVector1Double, pIMem);
	testCharVector(pIEcoVector1String, pIMem);


Release:
	/* Освобождение интерфейса работы с строкой */
    if (pIString != 0) {
        pIString->pVTbl->Release(pIString);
    }

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoVector1Int != 0) {
        pIEcoVector1Int->pVTbl->Release(pIEcoVector1Int);
    }
	if (pIEcoVector1Double != 0) {
        pIEcoVector1Double->pVTbl->Release(pIEcoVector1Double);
    }
	if (pIEcoVector1String != 0) {
        pIEcoVector1String->pVTbl->Release(pIEcoVector1String);
    }



    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

