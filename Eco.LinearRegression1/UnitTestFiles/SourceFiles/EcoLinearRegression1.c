/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLinearRegression1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLinearRegression1.h"
#include "IdEcoMatrix1.h"
#include "IdEcoVector1.h"
#include "IdEcoString1.h"
#include "IdEcoComparator1.h"
#include <stdio.h>


IEcoMatrix1* read_from_file(IEcoMemoryAllocator1* pIMem, IEcoInterfaceBus1* pIBus, int32_t size_x, int32_t size_xi, char_t* filename) {
	FILE* file = NULL;
	int32_t i, j;
	int16_t result = 0;
	double_t current_double = 0; 
	int32_t current_int = 0;
	char_t current_char = 'a';
	IEcoMatrix1* matrix = 0;
	double_t** tmpMatrix;


	tmpMatrix = (double_t**)pIMem->pVTbl->Alloc(pIMem, sizeof(double_t*) * size_xi);
	for (i = 0; i < size_xi; i++) {
		tmpMatrix[i] = (double_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(double_t) * size_x);
	}


	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMatrix1, 0, &IID_IEcoMatrix1, (void**) &matrix);
    if (result != 0 && matrix == 0) {
        return 0;
    }

	file = fopen(filename, "r+");
	if (file == 0) {
		printf("Cannot open file %s", filename);
		return 0; 
	}
	matrix->pVTbl->InitBySize(matrix, size_xi, size_x);

	// Read
	for (i = 0; i < size_x; i++) {
		for (j = 0; j < size_xi; j++) {
			fscanf(file, "%lf,", &current_double);
			tmpMatrix[j][i] = current_double;
		}
    }

	for (i = 0; i < size_xi; i++) {
		matrix->pVTbl->CreateVectorAtIndex(matrix, tmpMatrix[i], size_x, i, ECO_SET_1_DOUBLE_TYPE);
	}

    fclose(file);
	return matrix;
}


int16_t train_test_split(IEcoMemoryAllocator1* pIMem, IEcoInterfaceBus1* pIBus, IEcoMatrix1* X,
	                     IEcoVector1* y, IEcoMatrix1** X_test, IEcoVector1** y_test, double_t test_size) {
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t firstTestIndex = 0;
	uint32_t* psize_x = 0;
	uint32_t* psize_xi = 0;
	uint32_t size_x = 0;
	uint32_t size_xi = 0;

	psize_x = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));
	psize_xi = (uint32_t*)pIMem->pVTbl->Alloc(pIMem, sizeof(uint32_t));

	X->pVTbl->Size(X, psize_xi, psize_x);
	size_x = *psize_x;
	size_xi = *psize_xi;
	firstTestIndex = size_x * (1 - test_size);

	*X_test = X->pVTbl->DeepCopy(X);
	*y_test = y->pVTbl->DeepCopy(y);
	for (i = firstTestIndex; i < size_x; i++) {
		for (j = 0; j < size_xi; j++) {
			(*X_test)->pVTbl->Set((*X_test), i - firstTestIndex, j, X->pVTbl->At(X, i, j));
		}
		(*y_test)->pVTbl->Set((*y_test), i - firstTestIndex, y->pVTbl->At(y, i)); 
	}
	X->pVTbl->Reshape(X, size_xi, firstTestIndex);
	(*X_test)->pVTbl->Reshape((*X_test), size_xi, size_x - firstTestIndex);

	y->pVTbl->Reshape(y, firstTestIndex);
	(*y_test)->pVTbl->Reshape((*y_test), size_x - firstTestIndex);
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
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLinearRegression1* pIEcoLinearRegression1 = 0;
	IEcoMatrix1* matrix = 0;
	IEcoMatrix1* X = 0;
	IEcoVector1* y = 0;
	IEcoMatrix1** pX_test = 0;
	IEcoVector1** py_test = 0;
	IEcoVector1* predictions = 0;
	double_t mse = 0;

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
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLinearRegression1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_FB377ED7D3194F848BC2AF19B762B739);
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
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLinearRegression1, 0, &IID_IEcoLinearRegression1, (void**) &pIEcoLinearRegression1);
    if (result != 0 && pIEcoLinearRegression1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMatrix1, 0, &IID_IEcoMatrix1, (void**) &matrix);
    if (result != 0 && matrix == 0) {
        goto Release;
    }

	pX_test = (IEcoMatrix1**)pIMem->pVTbl->Alloc(pIMem, sizeof(IEcoMatrix1*));
	py_test = (IEcoVector1**)pIMem->pVTbl->Alloc(pIMem, sizeof(IEcoVector1*));

	/* Testing */
	matrix = read_from_file(pIMem, pIBus, 414, 7,
		"D:\\EcoProjects\\hse\\Eco.Framework\\Eco.LinearRegression1\\AssemblyFiles\\Windows\\VisualStudio_10\\Eco.LinearRegression1UnitTest\\StaticDebug\\Real_estate_prepared_scaled.csv"
	);
	y = matrix->pVTbl->RemoveCol(matrix, 6);
	train_test_split(pIMem, pIBus, matrix, y, pX_test, py_test, 0.25);
	pIEcoLinearRegression1->pVTbl->Fit(pIEcoLinearRegression1, matrix, y, 3, 100, 0.01, 0.001);
	predictions = pIEcoLinearRegression1->pVTbl->Predict(pIEcoLinearRegression1, *pX_test, *py_test);
	mse = pIEcoLinearRegression1->pVTbl->MSE(pIEcoLinearRegression1, predictions, *py_test);
	printf("\nMSE = %f", mse);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLinearRegression1 != 0) {
		pIEcoLinearRegression1->pVTbl->Release(pIEcoLinearRegression1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

