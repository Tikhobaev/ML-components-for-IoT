/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoMatrix1
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
#include "IdEcoString1.h"
#include "IdEcoMatrix1.h"
#include "IdEcoComparator1.h"
#include "IdEcoVector1.h"
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
	int32_t value = (int32_t)*(double_t *)elem;
	if (value % 2 == 0) {
		*(double_t *)elem = 0;
	}
	return;
}


void testIntMatrix(IEcoMatrix1* pIEcoMatrix1Int, IEcoMemoryAllocator1* pIMem) {
	int16_t isSuccess = 0;
	int16_t result = 0;

	int32_t intArray[] = {1, 2};
	int32_t intArray1[] = {3, 4};
	int32_t intArray2[] = {5, 6};
	int32_t intArray3[] = {1, 2, 3};
	int32_t intArray4[] = {4, 5, 6};
	uint32_t* pInt = 0;
	uint32_t* pInt1 = 0;
	uint32_t* pInt2 = 0;

	int32_t i = 0;
	int32_t j = 0;
	int32_t size = 0;

	void* tmp = 0;
	IEcoMatrix1* newPIEcoMatrix1Int = 0;
	double_t mean = 0.0;

	clock_t begin = 0;
	clock_t end = 0;
	double_t time_spent = 0;
	int32_t* sourceArray = 0;
	
	// Test init
	isSuccess = pIEcoMatrix1Int->pVTbl->InitBySize(pIEcoMatrix1Int, 2, 2);
	if (isSuccess == 0) {
		printf("Matrix initialized successfully\n");
	} else {
		printf("Error while initializing matrix\n");
	}

	// Test CreateVectorAtIndex
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray, 2, 0, ECO_SET_1_INTEGER_TYPE);
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray1, 2, 1, ECO_SET_1_INTEGER_TYPE);
	printf("\nFully initialized matrix\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	pInt = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));
	pInt1 = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));
	pInt2 = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));

	// Test Size
	pIEcoMatrix1Int->pVTbl->Size(pIEcoMatrix1Int, pInt, pInt1);
	printf("\n\nSize of matrix: %dx%d", *pInt, *pInt1);

	// Test isEmpty
	result = pIEcoMatrix1Int->pVTbl->IsEmpty(pIEcoMatrix1Int);
	printf("\n\nIs matrix empty: %d", result);

	// Test Clear
	pIEcoMatrix1Int->pVTbl->Clear(pIEcoMatrix1Int);
	printf("\n\nClear matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Fill matrix again
	isSuccess = pIEcoMatrix1Int->pVTbl->InitBySize(pIEcoMatrix1Int, 2, 2);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray, 2, 0, ECO_SET_1_INTEGER_TYPE);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray1, 2, 1, ECO_SET_1_INTEGER_TYPE);
	printf("\n\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test At
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			tmp = pIEcoMatrix1Int->pVTbl->At(pIEcoMatrix1Int, i, j);
			if (tmp != 0) {
				printf("\nElement with index %d %d = %d\n", i, j, *((int32_t*)tmp));
			} else {
				printf("\nElement with index %d %d not found\n", i, j);
			}
		}
	}

	// Test IndexOf
	*pInt = 2;
	isSuccess = pIEcoMatrix1Int->pVTbl->IndexOf(pIEcoMatrix1Int, pInt, pInt1, pInt2);
	if (isSuccess == 0) {
		printf("\n\nIndex of element with value %d: %d %d\n", *pInt, *pInt1, *pInt2);
	} else {
		printf("\n\nElement with value %d is not found\n", *pInt);
	}

	*pInt = 0;
	isSuccess = pIEcoMatrix1Int->pVTbl->IndexOf(pIEcoMatrix1Int, pInt, pInt1, pInt2);
	if (isSuccess == 0) {
		printf("\n\nIndex of element with value %d: %d %d\n", *pInt, *pInt1, *pInt2);
	} else {
		printf("\n\nElement with value %d is not found\n", *pInt);
	}

	*pInt = 4;
	isSuccess = pIEcoMatrix1Int->pVTbl->IndexOf(pIEcoMatrix1Int, pInt, pInt1, pInt2);
	if (isSuccess == 0) {
		printf("\n\nIndex of element with value %d: %d %d\n", *pInt, *pInt1, *pInt2);
	} else {
		printf("\n\nElement with value %d is not found\n", *pInt);
	}

	// Test Transpose
	pIEcoMatrix1Int->pVTbl->Transpose(pIEcoMatrix1Int);
	printf("\n\nTranspose matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	pIEcoMatrix1Int->pVTbl->Clear(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->InitBySize(pIEcoMatrix1Int, 3, 2);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray, 2, 0, ECO_SET_1_INTEGER_TYPE);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray1, 2, 1, ECO_SET_1_INTEGER_TYPE);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray2, 2, 2, ECO_SET_1_INTEGER_TYPE);
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->Transpose(pIEcoMatrix1Int);
	printf("\n\nTranspose matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	pIEcoMatrix1Int->pVTbl->Clear(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->InitBySize(pIEcoMatrix1Int, 2, 3);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray3, 3, 0, ECO_SET_1_INTEGER_TYPE);
	pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, intArray4, 3, 1, ECO_SET_1_INTEGER_TYPE);
	printf("\n\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->Transpose(pIEcoMatrix1Int);
	printf("\n\nTranspose matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test Reshape
	pIEcoMatrix1Int->pVTbl->Reshape(pIEcoMatrix1Int, 4, 4);
	printf("\n\nReshape matrix to size 4x4:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	pIEcoMatrix1Int->pVTbl->Reshape(pIEcoMatrix1Int, 2, 2);
	printf("\n\nReshape matrix to size 2x2:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test DeepCopy
	newPIEcoMatrix1Int = pIEcoMatrix1Int->pVTbl->DeepCopy(pIEcoMatrix1Int);
	printf("\n\nDeep copy of the matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);

	*pInt = 22;
	newPIEcoMatrix1Int->pVTbl->Set(newPIEcoMatrix1Int, 0, 0, pInt);
	printf("\n\nSet value of new matrix elem with index (0, 0):\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);

	printf("\n\nOld matrix is not changed:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test Map
	isSuccess = pIEcoMatrix1Int->pVTbl->Map(pIEcoMatrix1Int, zeroOddNumbers);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully apply function that zero odd numbers\n");
	} else {
		printf("\n\nError while applying function that zero odd numbers\n");
	}
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test ReplaceValue
	*pInt = 0;
	*pInt1 = -1;
	isSuccess = pIEcoMatrix1Int->pVTbl->ReplaceValue(pIEcoMatrix1Int, pInt, pInt1);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully replace value %d with value %d\n", *pInt, *pInt1);
	} else {
		printf("\n\nError while replacing value %d with value %d\n", *pInt, *pInt1);
	}
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test AddValue
	*pInt = 2;
	isSuccess = pIEcoMatrix1Int->pVTbl->AddValue(pIEcoMatrix1Int, pInt);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully added value %d to all elements of matrix\n", *pInt);
	} else {
		printf("\n\nError while adding value to elements of matrix\n");
	}
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test SubValue
	*pInt = 2;
	isSuccess = pIEcoMatrix1Int->pVTbl->SubValue(pIEcoMatrix1Int, pInt);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully substracted value %d from all elements of matrix\n", *pInt);
	} else {
		printf("\n\nError while substracting value from all elements of matrix\n");
	}
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test MulValue
	*pInt = 2;
	isSuccess = pIEcoMatrix1Int->pVTbl->MulValue(pIEcoMatrix1Int, pInt);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully multiplied value %d from all elements of matrix\n", *pInt);
	} else {
		printf("\n\nError while substracting value from all elements of matrix\n");
	}
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test DivValue
	*pInt = 2;
	isSuccess = pIEcoMatrix1Int->pVTbl->DivValue(pIEcoMatrix1Int, pInt);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully divided elements of matrix by %d\n", *pInt);
	} else {
		printf("\n\nError while dividing all elements of matrix by value\n");
	}
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test ModValue
	*pInt = 2;
	isSuccess = pIEcoMatrix1Int->pVTbl->ModValue(pIEcoMatrix1Int, pInt);
	if (isSuccess == 0) {
		printf("\n\nMod value %d\n", *pInt);
	} else {
		printf("\n\nError while testing ModValue\n");
	}
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test AddMatrix
	printf("\n\n Add matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\nWith the following matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);

	isSuccess = pIEcoMatrix1Int->pVTbl->AddMatrix(pIEcoMatrix1Int, newPIEcoMatrix1Int);
	printf("\nResult:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test SubMatrix
	printf("\n\n Sub matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\nWith the following matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);

	isSuccess = pIEcoMatrix1Int->pVTbl->SubMatrix(pIEcoMatrix1Int, newPIEcoMatrix1Int);
	printf("\nResult:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test MulMatrixElementwise
	printf("\n\nMultiply matrix elementwise\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\nWith the following matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);

	isSuccess = pIEcoMatrix1Int->pVTbl->MulMatrixElementwise(pIEcoMatrix1Int, newPIEcoMatrix1Int);
	printf("\nResult:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	// Test MulMatrix
	printf("\n\nMultiply matrix\n");
	pIEcoMatrix1Int->pVTbl->Reshape(pIEcoMatrix1Int, 2, 3);
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\nWith the following matrix:\n");
	newPIEcoMatrix1Int->pVTbl->Reshape(newPIEcoMatrix1Int, 3, 4);
	pIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);

	isSuccess = pIEcoMatrix1Int->pVTbl->MulMatrix(pIEcoMatrix1Int, newPIEcoMatrix1Int);
	printf("\nResult:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);

	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);
	printf("\nJoin along X axis in append mode:\n");
	isSuccess = pIEcoMatrix1Int->pVTbl->Join(pIEcoMatrix1Int, newPIEcoMatrix1Int, 1, 1);
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->Reshape(pIEcoMatrix1Int, 2, 4);

	newPIEcoMatrix1Int->pVTbl->Reshape(newPIEcoMatrix1Int, 2, 3);
	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);
	isSuccess = pIEcoMatrix1Int->pVTbl->Join(pIEcoMatrix1Int, newPIEcoMatrix1Int, 1, 0);
	printf("\nJoin along Y axis in append mode:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->Reshape(pIEcoMatrix1Int, 2, 4);

	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Int->pVTbl->Reshape(newPIEcoMatrix1Int, 2, 4);
	newPIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);
	isSuccess = pIEcoMatrix1Int->pVTbl->Join(pIEcoMatrix1Int, newPIEcoMatrix1Int, 0, 1);
	printf("\nJoin along X axis in prepend mode:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->Reshape(pIEcoMatrix1Int, 2, 4);

	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Int->pVTbl->PrintMatrix(newPIEcoMatrix1Int);
	isSuccess = pIEcoMatrix1Int->pVTbl->Join(pIEcoMatrix1Int, newPIEcoMatrix1Int, 0, 0);
	printf("\nJoin along Y axis in prepend mode:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	pIEcoMatrix1Int->pVTbl->Reshape(pIEcoMatrix1Int, 2, 4);

	// Test Mean
	printf("\n\nMean of matrix:\n");
	pIEcoMatrix1Int->pVTbl->PrintMatrix(pIEcoMatrix1Int);
	mean = pIEcoMatrix1Int->pVTbl->Mean(pIEcoMatrix1Int);
	printf("\n\nMean = %f:", mean);


	pIEcoMatrix1Int->pVTbl->Clear(pIEcoMatrix1Int);
	printf("\n\nCheck working time:\n");
	for (size = 10; size <= 160; size *= 2) {
		// Fill matrix
		isSuccess = pIEcoMatrix1Int->pVTbl->InitBySize(pIEcoMatrix1Int, size, size);
		sourceArray = (int32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t) * size);
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				sourceArray[j] = j + (i * size);
			}
			pIEcoMatrix1Int->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Int, sourceArray, size, i, ECO_SET_1_INTEGER_TYPE);
		}

		// Test IndexOf
		begin = clock();
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				*pInt = j + (i * size);
				pIEcoMatrix1Int->pVTbl->IndexOf(pIEcoMatrix1Int, pInt, pInt1, pInt2);
				if (*pInt1 == -1 || *pInt2 == -1) {
					printf("\nError, value %d is not found in matrix\n", *pInt);
				}
			}
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("\n%d IndexOf calls: %lf s.\n", size * size, time_spent);
		printf("%d elems IndexOf average: %lf s.\n", size * size, time_spent / size);

		// Test At
		begin = clock();
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				tmp = pIEcoMatrix1Int->pVTbl->At(pIEcoMatrix1Int, i, j);
				if (tmp == 0) {
					printf("\nError, value with index (%d, %d) is not found in matrix\n", i, j);
				}
			}
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("\n%d At calls: %lf s.\n", size * size, time_spent);
		printf("%d elems At average: %lf s.\n", size * size, time_spent / size);

		// Test Set
		begin = clock();
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				*pInt = j + (i * size) + 1;
				result = pIEcoMatrix1Int->pVTbl->Set(pIEcoMatrix1Int, i, j, pInt);
				if (result != 0) {
					printf("\nError, value with index (%d, %d) is not found in matrix\n", i, j);
				}
			}
		}
		end = clock();
		time_spent = (double_t)(end - begin) / CLOCKS_PER_SEC;
		printf("\n%d Set calls: %lf s.\n", size * size, time_spent);
		printf("%d elems Set average: %lf s.\n", size * size, time_spent / size);
	}
}


void testDoubleMatrix(IEcoMatrix1* pIEcoMatrix1Double, IEcoMemoryAllocator1* pIMem) {
	int16_t isSuccess = 0;
	int16_t result = 0;

	double_t doubleArray[] = {1.0, 2.0};
	double_t doubleArray1[] = {3.0, 4.0};
	double_t doubleArray2[] = {5.0, 6.0};
	double_t doubleArray3[] = {1.0, 2.0, 3.0};
	double_t doubleArray4[] = {4.0, 5.0, 6.0};
	double_t* pDouble = 0;
	double_t* pDouble1= 0;
	double_t* pDouble2 = 0;

	uint32_t* pInt = 0;
	uint32_t* pInt1= 0;
	uint32_t* pInt2 = 0;

	int32_t i = 0;
	int32_t j = 0;

	void* tmp = 0;
	IEcoMatrix1* newPIEcoMatrix1Double = 0;
	double_t mean = 0.0;
	
	// Test init
	isSuccess = pIEcoMatrix1Double->pVTbl->InitBySize(pIEcoMatrix1Double, 2, 2);
	if (isSuccess == 0) {
		printf("Matrix initialized successfully\n");
	} else {
		printf("Error while initializing matrix\n");
	}

	// Test CreateVectorAtIndex
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray, 2, 0, ECO_SET_1_DOUBLE_TYPE);
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray1, 2, 1, ECO_SET_1_DOUBLE_TYPE);
	printf("\nFully initialized matrix\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	pInt = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));
	pInt1 = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));
	pInt2 = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));
	pDouble = (double_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(double_t));
	pDouble1 = (double_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(double_t));
	pDouble2 = (double_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(double_t));

	// Test Size
	pIEcoMatrix1Double->pVTbl->Size(pIEcoMatrix1Double, pInt, pInt1);
	printf("\n\nSize of matrix: %dx%d", *pInt, *pInt1);

	// Test isEmpty
	result = pIEcoMatrix1Double->pVTbl->IsEmpty(pIEcoMatrix1Double);
	printf("\n\nIs matrix empty: %d", result);

	// Test Clear
	pIEcoMatrix1Double->pVTbl->Clear(pIEcoMatrix1Double);
	printf("\n\nClear matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Fill matrix again
	isSuccess = pIEcoMatrix1Double->pVTbl->InitBySize(pIEcoMatrix1Double, 2, 2);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray, 2, 0, ECO_SET_1_DOUBLE_TYPE);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray1, 2, 1, ECO_SET_1_DOUBLE_TYPE);
	printf("\n\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test At
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			tmp = pIEcoMatrix1Double->pVTbl->At(pIEcoMatrix1Double, i, j);
			if (tmp != 0) {
				printf("\nElement with index %d %d = %f\n", i, j, *((double_t*)tmp));
			} else {
				printf("\nElement with index %d %d not found\n", i, j);
			}
		}
	}

	// Test IndexOf
	*pDouble = 2.0;
	isSuccess = pIEcoMatrix1Double->pVTbl->IndexOf(pIEcoMatrix1Double, pDouble, pInt1, pInt2);
	if (isSuccess == 0) {
		printf("\n\nIndex of element with value %f: %d %d\n", *pDouble, *pInt1, *pInt2);
	} else {
		printf("\n\nElement with value %f is not found\n", *pDouble);
	}

	*pDouble = 2.0;
	isSuccess = pIEcoMatrix1Double->pVTbl->IndexOf(pIEcoMatrix1Double, pDouble, pInt1, pInt2);
	if (isSuccess == 0) {
		printf("\n\nIndex of element with value %f: %d %d\n", *pDouble, *pInt1, *pInt2);
	} else {
		printf("\n\nElement with value %f is not found\n", *pDouble);
	}

	*pDouble = 4.0;
	isSuccess = pIEcoMatrix1Double->pVTbl->IndexOf(pIEcoMatrix1Double, pDouble, pInt1, pInt2);
	if (isSuccess == 0) {
		printf("\n\nIndex of element with value %f: %d %d\n", *pDouble, *pInt1, *pInt2);
	} else {
		printf("\n\nElement with value %f is not found\n", *pDouble);
	}

	// Test Transpose
	printf("\n\nMatrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->Transpose(pIEcoMatrix1Double);
	printf("\n\nTranspose matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	pIEcoMatrix1Double->pVTbl->Clear(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->InitBySize(pIEcoMatrix1Double, 3, 2);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray, 2, 0, ECO_SET_1_DOUBLE_TYPE);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray1, 2, 1, ECO_SET_1_DOUBLE_TYPE);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray2, 2, 2, ECO_SET_1_DOUBLE_TYPE);
	printf("\n\nNew matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->Transpose(pIEcoMatrix1Double);
	printf("\n\nTransposed matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	pIEcoMatrix1Double->pVTbl->Clear(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->InitBySize(pIEcoMatrix1Double, 2, 3);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray3, 3, 0, ECO_SET_1_DOUBLE_TYPE);
	pIEcoMatrix1Double->pVTbl->CreateVectorAtIndex(pIEcoMatrix1Double, doubleArray4, 3, 1, ECO_SET_1_DOUBLE_TYPE);
	printf("\n\nNew matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->Transpose(pIEcoMatrix1Double);
	printf("\n\nTranspose matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test Reshape
	pIEcoMatrix1Double->pVTbl->Reshape(pIEcoMatrix1Double, 4, 4);
	printf("\n\nReshape matrix to size 4x4:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	pIEcoMatrix1Double->pVTbl->Reshape(pIEcoMatrix1Double, 2, 2);
	printf("\n\nReshape matrix to size 2x2:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test DeepCopy
	newPIEcoMatrix1Double = pIEcoMatrix1Double->pVTbl->DeepCopy(pIEcoMatrix1Double);
	printf("\n\nDeep copy of the matrix:\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);

	*pDouble = 22;
	newPIEcoMatrix1Double->pVTbl->Set(newPIEcoMatrix1Double, 0, 0, pDouble);
	printf("\n\nSet value of new matrix elem with index (0, 0):\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);

	printf("\n\nOld matrix is not changed:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test Map
	isSuccess = pIEcoMatrix1Double->pVTbl->Map(pIEcoMatrix1Double, zeroOddDoubleNumbers);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully apply function that zero odd numbers\n");
	} else {
		printf("\n\nError while applying function that zero odd numbers\n");
	}
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test ReplaceValue
	*pDouble = 0;
	*pDouble1 = -1;
	isSuccess = pIEcoMatrix1Double->pVTbl->ReplaceValue(pIEcoMatrix1Double, pDouble, pDouble1);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully replace value %f with value %f\n", *pDouble, *pDouble1);
	} else {
		printf("\n\nError while replacing value %f with value %f\n", *pDouble, *pDouble1);
	}
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test AddValue
	*pDouble = 2;
	isSuccess = pIEcoMatrix1Double->pVTbl->AddValue(pIEcoMatrix1Double, pDouble);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully added value %f to all elements of matrix\n", *pDouble);
	} else {
		printf("\n\nError while adding value to elements of matrix\n");
	}
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test SubValue
	*pDouble = 2;
	isSuccess = pIEcoMatrix1Double->pVTbl->SubValue(pIEcoMatrix1Double, pDouble);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully substracted value %f from all elements of matrix\n", *pDouble);
	} else {
		printf("\n\nError while substracting value from all elements of matrix\n");
	}
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test MulValue
	*pDouble = 2;
	isSuccess = pIEcoMatrix1Double->pVTbl->MulValue(pIEcoMatrix1Double, pDouble);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully multiplied value %f from all elements of matrix\n", *pDouble);
	} else {
		printf("\n\nError while substracting value from all elements of matrix\n");
	}
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test DivValue
	*pDouble = 2;
	isSuccess = pIEcoMatrix1Double->pVTbl->DivValue(pIEcoMatrix1Double, pDouble);
	if (isSuccess == 0) {
		printf("\n\nSuccessfully divided elements of matrix by %f\n", *pDouble);
	} else {
		printf("\n\nError while dividing all elements of matrix by value\n");
	}
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test ModValue
	*pDouble = 2;
	isSuccess = pIEcoMatrix1Double->pVTbl->ModValue(pIEcoMatrix1Double, pDouble);
	if (isSuccess == 0) {
		printf("\n\nMod value %d\n", *pInt);
	} else {
		printf("\n\nError while testing ModValue\n");
	}
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);


	// Test AddMatrix
	printf("\n\n Add matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\nWith the following matrix:\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);

	isSuccess = pIEcoMatrix1Double->pVTbl->AddMatrix(pIEcoMatrix1Double, newPIEcoMatrix1Double);
	printf("\nResult:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test SubMatrix
	printf("\n\n Sub matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\nWith the following matrix:\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);

	isSuccess = pIEcoMatrix1Double->pVTbl->SubMatrix(pIEcoMatrix1Double, newPIEcoMatrix1Double);
	printf("\nResult:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test MulMatrixElementwise
	printf("\n\nMultiply matrix elementwise\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\nWith the following matrix:\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);

	isSuccess = pIEcoMatrix1Double->pVTbl->MulMatrixElementwise(pIEcoMatrix1Double, newPIEcoMatrix1Double);
	printf("\nResult:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	// Test MulMatrix
	printf("\n\nMultiply matrix\n");
	pIEcoMatrix1Double->pVTbl->Reshape(pIEcoMatrix1Double, 2, 3);
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\nWith the following matrix:\n");
	newPIEcoMatrix1Double->pVTbl->Reshape(newPIEcoMatrix1Double, 3, 4);
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);

	isSuccess = pIEcoMatrix1Double->pVTbl->MulMatrix(pIEcoMatrix1Double, newPIEcoMatrix1Double);
	printf("\nResult:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);

	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);
	printf("\nJoin along X axis in append mode:\n");
	isSuccess = pIEcoMatrix1Double->pVTbl->Join(pIEcoMatrix1Double, newPIEcoMatrix1Double, 1, 1);
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->Reshape(pIEcoMatrix1Double, 2, 4);

	newPIEcoMatrix1Double->pVTbl->Reshape(newPIEcoMatrix1Double, 2, 3);
	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);
	isSuccess = pIEcoMatrix1Double->pVTbl->Join(pIEcoMatrix1Double, newPIEcoMatrix1Double, 1, 0);
	printf("\nJoin along Y axis in append mode:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->Reshape(pIEcoMatrix1Double, 2, 4);

	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Double->pVTbl->Reshape(newPIEcoMatrix1Double, 2, 4);
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);
	isSuccess = pIEcoMatrix1Double->pVTbl->Join(pIEcoMatrix1Double, newPIEcoMatrix1Double, 0, 1);
	printf("\nJoin along X axis in prepend mode:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->Reshape(pIEcoMatrix1Double, 2, 4);

	printf("\n\n1 matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	printf("\n2 matrix:\n");
	newPIEcoMatrix1Double->pVTbl->PrintMatrix(newPIEcoMatrix1Double);
	isSuccess = pIEcoMatrix1Double->pVTbl->Join(pIEcoMatrix1Double, newPIEcoMatrix1Double, 0, 0);
	printf("\nJoin along Y axis in prepend mode:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	pIEcoMatrix1Double->pVTbl->Reshape(pIEcoMatrix1Double, 2, 4);

	// Test Mean
	printf("\n\nMean of matrix:\n");
	pIEcoMatrix1Double->pVTbl->PrintMatrix(pIEcoMatrix1Double);
	mean = pIEcoMatrix1Double->pVTbl->Mean(pIEcoMatrix1Double);
	printf("\n\nMean = %f:", mean);
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
    IEcoMatrix1* pIEcoMatrix1Int = 0;
	IEcoMatrix1* pIEcoMatrix1Double = 0;

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
    /* Регистрация статического компонента для работы с матрицей */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMatrix1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_9A659401C9334EF6970F7F5FE68577AA);
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
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMatrix1, 0, &IID_IEcoMatrix1, (void**) &pIEcoMatrix1Int);
    if (result != 0 && pIEcoMatrix1Int == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMatrix1, 0, &IID_IEcoMatrix1, (void**) &pIEcoMatrix1Double);
    if (result != 0 && pIEcoMatrix1Double == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	/* Run rests */
	testIntMatrix(pIEcoMatrix1Int, pIMem);
	// testDoubleMatrix(pIEcoMatrix1Double, pIMem);


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
    if (pIEcoMatrix1Int != 0) {
        pIEcoMatrix1Int->pVTbl->Release(pIEcoMatrix1Int);
    }
	if (pIEcoMatrix1Double != 0) {
        pIEcoMatrix1Double->pVTbl->Release(pIEcoMatrix1Double);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

