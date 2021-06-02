/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLinearRegression1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLinearRegression1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoLinearRegression1.h"
#include "IdEcoVector1.h"
#include "IdEcoMatrix1.h"
#include <stdio.h>

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLinearRegression1
 * </описание>
 *
 */
int16_t CEcoLinearRegression1_QueryInterface(/* in */ struct IEcoLinearRegression1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLinearRegression1) ) {
        *ppv = &pCMe->m_VTblIEcoLinearRegression1;
        pCMe->m_VTblIEcoLinearRegression1->AddRef((IEcoLinearRegression1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_VTblIEcoLinearRegression1;
        pCMe->m_VTblIEcoLinearRegression1->AddRef((IEcoLinearRegression1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLinearRegression1
 * </описание>
 *
 */
uint32_t CEcoLinearRegression1_AddRef(/* in */ struct IEcoLinearRegression1* me) {
    CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLinearRegression1
 * </описание>
 *
 */
uint32_t CEcoLinearRegression1_Release(/* in */ struct IEcoLinearRegression1* me) {
    CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLinearRegression1(me);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция MSE
 * </сводка>
 *
 * <описание>
 *   Функция вычисляет метрику Mean Squared Error
 * </описание>
 *
 */

double_t TrainMSE(/* in */ struct IEcoLinearRegression1* me, IEcoMatrix1* X, IEcoVector1* y) {
	CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;
	uint32_t i = 0;
	uint32_t j = 0;
	double_t sum = 0;
	double_t result = 0;

	if (me == 0 || y == 0 || pCMe->weights == 0 || pCMe->size_x == 0) {
		return -1;
	}

	for (i = 0; i < pCMe->size_x; ++i) {  // Loop over every object
		sum = 0;
		// Loop over every feature of object to mul features on corresponding weights to make a prediction
		for (j = 0; j < pCMe->size_xi; ++j) {
			sum += *((double_t*)(X->pVTbl->At(X, j, i))) * pCMe->weights[j];
		}
		sum -= *(double_t*)y->pVTbl->At(y, i);
		sum *= sum;
		result += sum;
	}
	result /= pCMe->size_x;
	return result;
}


/*
 *
 * <сводка>
 *   Функция MSE
 * </сводка>
 *
 * <описание>
 *   Функция вычисляет метрику Mean Squared Error
 * </описание>
 *
 */

double_t CEcoLinearRegression1_MSE(/* in */ struct IEcoLinearRegression1* me, IEcoVector1* predictions, IEcoVector1* y) {
	CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;
	uint32_t i = 0;
	double_t sum = 0;
	double_t result = 0;
	uint32_t size_x = 0;

	if (me == 0 || y == 0 || pCMe->weights == 0 || pCMe->size_x == 0) {
		return -1;
	}
	
	size_x = y->pVTbl->Size(y);
	for (i = 0; i < size_x; ++i) {  // Loop over every object
		sum = *(double_t*)predictions->pVTbl->At(predictions, i) - *(double_t*)y->pVTbl->At(y, i);
		sum *= sum;
		result += sum;
	}
	result /= pCMe->size_x;
	return result;
}


/*
 *
 * <сводка>
 *   Функция Fit
 * </сводка>
 *
 * <описание>
 *   Функция обучает линейную регрессию по заданным данным.
 * </описание>
 *
 */
int16_t CEcoLinearRegression1_Fit(/* in */ struct IEcoLinearRegression1* me, IEcoMatrix1* X_origin, IEcoVector1* y,
								  uint32_t patience, uint32_t max_epochs, double_t eps, double_t lr) {

    CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;
	IEcoVector1* bias = 0;
	IEcoMatrix1* X = 0;
    int16_t index = 0;
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t k = 0;
	uint32_t m = 0;
	uint32_t l = 0;

	uint32_t regression_counter = 0;
	double_t prev_mse = 0;

	double_t* grad = 0;
	double_t sum = 0;
	double_t val_mse = 0;

	uint32_t* pInt = 0;
	uint32_t* pInt1 = 0;
	double_t* pDouble = 0;
	uint32_t size_x = 0;
	uint32_t size_xi = 0;

	/* Проверка указателей */
	if (me == 0 || X_origin == 0 || y == 0) {
		return -1;
	}
	
	X = X_origin->pVTbl->DeepCopy(X_origin);
	pInt = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(uint32_t));
	pInt1 = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(uint32_t));
	pDouble = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(double_t));
	X->pVTbl->Size(X, pInt, pInt1);
	size_xi = *pInt;
	size_x = *pInt1;

    
	if (size_x == 0 || size_xi == 0) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pInt);
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pInt1);
        return -1;
    }

	// Create bias vector
	bias = X->pVTbl->GetCol(X, 0)->pVTbl->DeepCopy(X->pVTbl->GetCol(X, 0));
	*pDouble = 1.0;
	for (i = 0; i < size_x; i++) {
		bias->pVTbl->Set(bias, i, pDouble);
	}

	X->pVTbl->InsertVectorAtIndex(X, bias, 0);
	X->pVTbl->Size(X, pInt, pInt1);
	size_xi = *pInt;
	size_x = *pInt1;
	pCMe->size_xi = *pInt;
	pCMe->size_x = *pInt1;

	// Init weights and gradient
	pCMe->weights = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(double_t) * size_xi);
	grad = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(double_t) * size_xi);
	for (i = 0; i < size_xi; i++) {
		pCMe->weights[i] = 0.0;
		grad[i] = 0;
	}

	// Calc initial MSE
	val_mse = TrainMSE(me, X, y);
	printf("Initial MSE = %.2f\n\n", val_mse);
	prev_mse = val_mse;
	
	/*Training Phase*/
	for (i = 0; i < max_epochs; i++) {  // Training epochs
		for (k = 0; k < size_xi; k++) {  // Loop over each weight to make a gradient (array)
			grad[k] = 0;
			for (j = 0; j < size_x; j++) {  // Loop over every object to make a sum
				sum = 0;
				for (m = 0; m < size_xi; m++) {  // Loop over each weight to mul vector of current object and weights
					sum += *((double_t*)X->pVTbl->At(X, m, j)) * pCMe->weights[m];
				}
				grad[k] += (sum - *(double_t*)y->pVTbl->At(y, j)) * *((double_t*)X->pVTbl->At(X, k, j));
			}
			grad[k] *= 2;
		}

		printf("\nGradient: ");
		for (k = 0; k < size_xi; k++) {  // Loop over each weight to sub the gradient
			printf("%.5f ", grad[k]);
		}
		printf("\n");

		printf("\nWeights: ");
		for (k = 0; k < size_xi; k++) {  // Loop over each weight to sub the gradient
			pCMe->weights[k] -= lr * grad[k];
			printf("%.5f ", pCMe->weights[k]);
		}
		printf("\n");

		// Calculate metric and check if we need to stop
		val_mse = TrainMSE(me, X, y);
		printf("Step %d, MSE = %.2f\n\n", i, val_mse);
		if (val_mse < 0) {
			val_mse *= -1;
		}
		if (prev_mse - val_mse < eps) {
			regression_counter += 1;
			if (regression_counter > patience) {
				printf("Delta between previous and current MSE = %.5f that is less than %.5f, early stopping", prev_mse - val_mse, eps);
				break;
			}
		} else {
			regression_counter = 0;
		}
		prev_mse = val_mse;
	}

    return 0;
}


IEcoVector1* CEcoLinearRegression1_Predict(/* in */ struct IEcoLinearRegression1* me, IEcoMatrix1* X_origin, IEcoVector1* y) {
    CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;
	IEcoVector1* bias = 0;
	IEcoVector1* predictions = 0;
	IEcoMatrix1* X = 0;
    int16_t index = 0;
	uint32_t i = 0;
	uint32_t j = 0;

	double_t current_pred = 0;

	uint32_t* pInt = 0;
	uint32_t* pInt1 = 0;
	double_t* pDouble = 0;
	uint32_t size_x = 0;
	uint32_t size_xi = 0;

	/* Проверка указателей */
	if (me == 0 || X_origin == 0 || y == 0 || pCMe->weights == 0) {
		return 0;
	}
	
	X = X_origin->pVTbl->DeepCopy(X_origin);
	pInt = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(uint32_t));
	pInt1 = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(uint32_t));
	pDouble = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(double_t));
	X->pVTbl->Size(X, pInt, pInt1);
	size_xi = *pInt;
	size_x = *pInt1;

    
	if (size_x == 0 || size_xi == 0 || y->pVTbl->Size(y) != size_x) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pInt);
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pInt1);
        return 0;
    }

	// Create bias vector
	bias = X->pVTbl->GetCol(X, 0)->pVTbl->DeepCopy(X->pVTbl->GetCol(X, 0));
	*pDouble = 1.0;
	for (i = 0; i < size_x; i++) {
		bias->pVTbl->Set(bias, i, pDouble);
	}

	// Init prediction vector
	predictions = bias->pVTbl->DeepCopy(bias);

	X->pVTbl->InsertVectorAtIndex(X, bias, 0);
	X->pVTbl->Size(X, pInt, pInt1);
	size_xi = *pInt;
	size_x = *pInt1;

	for (i = 0; i < size_x; i++) {
		current_pred = 0;
		for (j = 0; j < size_xi; j++) {  // Loop over each weight to mul vector of current object and weights
			current_pred += *((double_t*)X->pVTbl->At(X, j, i)) * pCMe->weights[j];
		}
		predictions->pVTbl->Set(predictions, i, &current_pred);
	}
	
    return predictions;
}


/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t initCEcoLinearRegression1(/*in*/ struct IEcoLinearRegression1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;


    return result;
}


IEcoLinearRegression1VTbl g_xFB377ED7D3194F848BC2AF19B762B739VTbl = {
	CEcoLinearRegression1_QueryInterface,
    CEcoLinearRegression1_AddRef,
    CEcoLinearRegression1_Release,
	CEcoLinearRegression1_MSE,
	CEcoLinearRegression1_Fit,
	CEcoLinearRegression1_Predict
};


/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t createCEcoLinearRegression1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLinearRegression1** ppIEcoLinearRegression1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLinearRegression1* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLinearRegression1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLinearRegression1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLinearRegression1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLinearRegression1 */
	pCMe->m_VTblIEcoLinearRegression1 = &g_xFB377ED7D3194F848BC2AF19B762B739VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLinearRegression1 = &pCMe->m_VTblIEcoLinearRegression1;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void deleteCEcoLinearRegression1(/* in */ IEcoLinearRegression1* pIEcoLinearRegression1) {
    CEcoLinearRegression1* pCMe = (CEcoLinearRegression1*)pIEcoLinearRegression1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLinearRegression1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
