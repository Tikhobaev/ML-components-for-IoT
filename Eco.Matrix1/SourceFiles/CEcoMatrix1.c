/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoMatrix1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoMatrix1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoMatrix1.h"
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
 *   Функция QueryInterface для интерфейса IEcoMatrix1
 * </описание>
 *
 */
int16_t CEcoMatrix1_QueryInterface(/* in */ struct IEcoMatrix1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoMatrix1) ) {
        *ppv = &pCMe->m_pVTblIEcoMatrix1;
        pCMe->m_pVTblIEcoMatrix1->AddRef((IEcoMatrix1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoMatrix1;
        pCMe->m_pVTblIEcoMatrix1->AddRef((IEcoMatrix1*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoMatrix1
 * </описание>
 *
 */
uint32_t CEcoMatrix1_AddRef(/* in */ struct IEcoMatrix1* me) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;

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
 *   Функция Release для интерфейса IEcoMatrix1
 * </описание>
 *
 */
uint32_t CEcoMatrix1_Release(/* in */ struct IEcoMatrix1* me) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoMatrix1((IEcoMatrix1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция InitBySize
 * </сводка>
 *
 * <описание>
 *   Функция инициализирует матрицу размером
 * </описание>
 *
 */
int16_t CEcoMatrix1_InitBySize(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t sizeX, uint32_t sizeY) {
	CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	IEcoVector1** tmp = 0;

    /* Проверка указателей */
    if (me == 0 || sizeX == 0 || sizeY == 0) {
        return -1;
    }

	pCMe->vectors = (IEcoVector1**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(IEcoVector1*) * sizeX);
	pCMe->sizeX = sizeX;
	pCMe->sizeY = sizeY;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция CreateVectorAtIndex
 * </сводка>
 *
 * <описание>
 *   Функция создаёт вектор из массива на позиции с заданным индексом
 * </описание>
 *
 */
int16_t CEcoMatrix1_CreateVectorAtIndex(/* in */ struct IEcoMatrix1* me, /* in */ void* sourceArray, uint32_t size, uint32_t index, uchar_t type) {
	CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t result = 0;
	IEcoVector1* pIEcoVector1 = 0;
    
	/* Проверка указателей и входных аргументов*/
	if (me == 0 || sourceArray == 0 || size == 0 || size != pCMe->sizeY || index > pCMe->sizeX || type > 4) {
        return -1;
    }

	result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoVector1, 0, &IID_IEcoVector1, (void**) &pIEcoVector1);
    if (result != 0 && pIEcoVector1 == 0) {
        return -1;
    }

	result = pIEcoVector1->pVTbl->InitByType(pIEcoVector1, type);
	if (result != 0) {
		return -1;
	}
	result = pIEcoVector1->pVTbl->FromArray(pIEcoVector1, sourceArray, size);
	if (result != 0) {
		return -1;
	}
	pCMe->vectors[index] = pIEcoVector1;
    return 0;
}


/*
 *
 * <сводка>
 *   Функция CreateVectorAtIndex
 * </сводка>
 *
 * <описание>
 *   Функция присваивает заданный вектор массиву векторов на позиции с заданным индексом.
     Вектор присваивается без глубокого копирования.
 * </описание>
 *
 */
int16_t CEcoMatrix1_SetVectorAtIndex(/* in */ struct IEcoMatrix1* me, /* in */ IEcoVector1* sourceVector, uint32_t index) {
	CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t result = 0;
    
	/* Проверка указателей и входных аргументов*/
	if (me == 0 || sourceVector == 0 || index > pCMe->sizeX || sourceVector->pVTbl->Size(sourceVector) != pCMe->sizeY) {
        return -1;
    }

	pCMe->vectors[index] = sourceVector;
    return 0;
}


/*
 *
 * <сводка>
 *   Функция InsertVectorAtIndex
 * </сводка>
 *
 * <описание>
 *   Функция добавляет заданный вектор на позицию с заданным индексом.
     Вектор присваивается без глубокого копирования.
 * </описание>
 *
 */
int16_t CEcoMatrix1_InsertVectorAtIndex(/* in */ struct IEcoMatrix1* me, /* in */ IEcoVector1* sourceVector, uint32_t index) {
	CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t result = 0;
	IEcoVector1* pIEcoVector1 = 0;
    uint32_t i = 0;

	/* Проверка указателей и входных аргументов*/
	if (me == 0 || sourceVector == 0 || index > pCMe->sizeX || sourceVector->pVTbl->Size(sourceVector) != pCMe->sizeY) {
        return -1;
    }
	pCMe->sizeX += 1;
	pCMe->vectors = pCMe->m_pIMem->pVTbl->Realloc(pCMe->m_pIMem, pCMe->vectors, (uint32_t)(sizeof(IEcoVector1*) * pCMe->sizeX));
	for (i = pCMe->sizeX; i > index; i--) {
		pCMe->vectors[i] = pCMe->vectors[i - 1];
	}
	pCMe->vectors[index] = sourceVector;
    return 0;
}


/*
 *
 * <сводка>
 *   Функция PrintVector
 * </сводка>
 *
 * <описание>
 *   Функция выводит на stdout элементы матрицы
 * </описание>
 *
 */
void CEcoMatrix1_PrintMatrix(/* in */ struct IEcoMatrix1* me) {
	CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
    uint32_t i = 0;

	/* Проверка указателей */
	if (me == 0) {
        return;
    }

	if (pCMe->vectors == 0) {
		printf("Matrix is empty");
	}

	for (i = 0; i < pCMe->sizeX; i++) {
		if (pCMe->vectors[i] != 0) {
			pCMe->vectors[i]->pVTbl->PrintVector(pCMe->vectors[i]);
		} else {
			printf("NA");
		}
		printf("\n");
	}

    return;
}


/*
 *
 * <сводка>
 *   Функция Size
 * </сводка>
 *
 * <описание>
 *   Функция присваивает значение, равное количеству строк (количеству векторов) первому из переданных указателей,
 *   и присваивает количество столбцов (размерность одного вектора) второму из переданных указателей
 * </описание>
 *
 */
int16_t CEcoMatrix1_Size(/* in */ struct IEcoMatrix1* me, /* out */ uint32_t* sizeX, /* out */ uint32_t* sizeY) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;

    /* Проверка указателей */
    if (me == 0 || sizeX == 0 || sizeY == 0) {
        return -1;
    }

	*sizeX = pCMe->sizeX;
	*sizeY = pCMe->sizeY;
    
	return 0;
}


/*
 *
 * <сводка>
 *   Функция isEmpty
 * </сводка>
 *
 * <описание>
 *   Функция возвращает 1 в случае если матрица пуста и 0 если в матрице есть хотя бы один вектор
 *   В случае ошибки возвращается -1
 * </описание>
 *
 */
int16_t CEcoMatrix1_IsEmpty(/* in */ struct IEcoMatrix1* me) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

	if (pCMe->vectors == 0) {
		return 1;
	}

	for (i = 0; i < pCMe->sizeX; i++) {
		if (pCMe->vectors[i] != 0) {
			return 0;
		}
	}
    return 1;
}


/*
 *
 * <сводка>
 *   Функция At
 * </сводка>
 *
 * <описание>
 *   Функция возвращает элемент, находящийся на позиции с заданным индексом
 * </описание>
 *
 */
void* CEcoMatrix1_At(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t ix,  /* in */ uint32_t iy) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;

    /* Проверка указателей */
	if (me == 0 || ix >= pCMe->sizeX || iy >= pCMe->sizeY || pCMe->vectors == 0 || pCMe->vectors[ix] == 0) {
        return 0;
    }

	return pCMe->vectors[ix]->pVTbl->At(pCMe->vectors[ix], iy);
}


/*
 *
 * <сводка>
 *   Функция Set
 * </сводка>
 *
 * <описание>
 *   Функция устанавливает значение элементу, находящемуся на позиции с заданным индексом
 * </описание>
 *
 */
int16_t CEcoMatrix1_Set(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t ix,  /* in */ uint32_t iy, void* value) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;

    /* Проверка указателей */
	if (me == 0 || ix >= pCMe->sizeX || iy >= pCMe->sizeY || pCMe->vectors == 0 || pCMe->vectors[ix] == 0 || value == 0) {
        return -1;
    }

	pCMe->vectors[ix]->pVTbl->Set(pCMe->vectors[ix], iy, value);
	return 0;
}


/*
 *
 * <сводка>
 *   Функция IndexOf
 * </сводка>
 *
 * <описание>
 *   Функция возвращает индекс элемента с заданным значением. Если такого элемента нет, возвращается -1.
 * </описание>
 *
 */
int16_t CEcoMatrix1_IndexOf(/* in */ struct IEcoMatrix1* me, /* in */ void* value, /* out */ uint32_t* ix, /* out */ uint32_t* iy) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	uint32_t i = 0;
	int32_t foundIndex = -1;

    /* Проверка указателей */
	if (me == 0 || value == 0 || ix == 0 || iy == 0 || pCMe->vectors == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		foundIndex = pCMe->vectors[i]->pVTbl->IndexOf(pCMe->vectors[i], value);
		if (foundIndex != -1) {
			*ix = i;
			*iy = foundIndex;
			break;
		}
	}

	return foundIndex == -1 ? -1 : 0;
}


/*
 *
 * <сводка>
 *   Функция Clear
 * </сводка>
 *
 * <описание>
 *   Функция полностью очищает матрицу с освобождением памяти под все вектора
 * </описание>
 *
 */
int16_t CEcoMatrix1_Clear(/* in */ struct IEcoMatrix1* me) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

	if (pCMe->sizeX == 0 || pCMe->sizeY == 0 || pCMe->vectors == 0) {
		return 0;
	}

	for (i = 0; i < pCMe->sizeX; i++) {
		if (pCMe->vectors[i] != 0) {
			pCMe->vectors[i]->pVTbl->Release(pCMe->vectors[i]);
		}
	}
	pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCMe->vectors);
	pCMe->vectors = 0;
	pCMe->sizeX = 0;
	pCMe->sizeY = 0;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция Transpose
 * </сводка>
 *
 * <описание>
 *   Функция транспонирует матрицу с условием что все вектора заполнены и имеют один тип
 * </описание>
 *
 */
int16_t CEcoMatrix1_Transpose(/* in */ struct IEcoMatrix1* me) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	int16_t type = -1;
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t maxSize = 0;
	IEcoVector1* pIEcoVector1 = 0;
	void* elem1 = 0;
	void* elem2 = 0;

    /* Проверка указателей */
	if (me == 0 || pCMe->vectors == 0) {
        return -1;
    }

	/* Проверка заполненности всех векторов и проверка типов */
	for (i = 0; i < pCMe->sizeX; i++) {
		if (pCMe->vectors[i] == 0) {
			return -1;
		} else {
			if (type == -1) {
				type = pCMe->vectors[i]->pVTbl->Get_Type(pCMe->vectors[i]);
			}
			if (type != pCMe->vectors[i]->pVTbl->Get_Type(pCMe->vectors[i])) {
				return -1;
			}
		}
	}
	
	maxSize = pCMe->sizeX;
	switch (pCMe->vectors[0]->pVTbl->Get_Type(pCMe->vectors[0])) {
		case ECO_SET_1_STRING_TYPE:
			// TODO implement
			break;
		case ECO_SET_1_INTEGER_TYPE:
			elem1 = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(int32_t));
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			elem1 = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(double_t));
			break;
		case ECO_SET_1_POINTER_TYPE:
			// TODO implement
			break;
		case ECO_SET_1_OBJECT_TYPE:
			// TODO implement
			break;
    }

	/* Create more vectors if needed to create a square matrix */
	if (pCMe->sizeX < pCMe->sizeY) {
		maxSize =  pCMe->sizeY;
		pCMe->vectors = (IEcoVector1**)pCMe->m_pIMem->pVTbl->Realloc(
			pCMe->m_pIMem, pCMe->vectors, (uint32_t)(sizeof(IEcoVector1*) * pCMe->sizeY)
		);
		for (i = pCMe->sizeX; i < pCMe->sizeY; i++) {
			pIEcoVector1 = pCMe->vectors[0]->pVTbl->DeepCopy(pCMe->vectors[0]);
			if (pIEcoVector1 == 0) {
				return -1;
			}
			pCMe->vectors[i] = pIEcoVector1;
		}
	}


	/* Reshape vectors if needed to create a square matrix */
	if (pCMe->sizeX > pCMe->sizeY) {
		for (i = 0; i < pCMe->sizeX; i++) {
			isSuccess = pCMe->vectors[i]->pVTbl->Reshape(pCMe->vectors[i], pCMe->sizeX);
			if (isSuccess != 0) {
				return -1;
			}
		}
	}

	/* Transpose a square matrix */
	for (i = 0; i < maxSize; i++) {
		for (j = i; j < maxSize; j++) {
			elem2 = pCMe->vectors[i]->pVTbl->At(pCMe->vectors[i], j);
			if (elem2 == 0) {
				return -1;
			}

			switch (pCMe->vectors[0]->pVTbl->Get_Type(pCMe->vectors[0])) {
				case ECO_SET_1_STRING_TYPE:
					// TODO implement
					break;
				case ECO_SET_1_INTEGER_TYPE:
					*((int32_t*)elem1) = *((int32_t*)elem2);
					break;
				case ECO_SET_1_DOUBLE_TYPE:
					*((double_t*)elem1) = *((double_t*)elem2);
					break;
				case ECO_SET_1_POINTER_TYPE:
					// TODO implement
					break;
				case ECO_SET_1_OBJECT_TYPE:
					// TODO implement
					break;
			}

			elem2 = pCMe->vectors[j]->pVTbl->At(pCMe->vectors[j], i);
			if (elem2 == 0) {
				return -1;
			}

			isSuccess = pCMe->vectors[i]->pVTbl->Set(pCMe->vectors[i], j, elem2);
			if (isSuccess != 0) {
				return -1;
			}

			isSuccess = pCMe->vectors[j]->pVTbl->Set(pCMe->vectors[j], i, elem1);
			if (isSuccess != 0) {
				return -1;
			}
		}
	}

	/* Reshape vectors if needed to make vectors the right size */
	if (pCMe->sizeX < pCMe->sizeY) {
		for (i = 0; i < pCMe->sizeY; i++) {
			isSuccess = pCMe->vectors[i]->pVTbl->Reshape(pCMe->vectors[i], pCMe->sizeX);
			if (isSuccess != 0) {
				return -1;
			}
		}
	}

	/* Remove some vectors if needed to make vectors the right size */
	if (pCMe->sizeX > pCMe->sizeY) {
		for (i = pCMe->sizeY; i < pCMe->sizeX; i++) {
			pCMe->vectors[i]->pVTbl->Release(pCMe->vectors[i]);
		}
		pCMe->vectors = (IEcoVector1**)pCMe->m_pIMem->pVTbl->Realloc(
			pCMe->m_pIMem, pCMe->vectors, (uint32_t)(sizeof(IEcoVector1*) * pCMe->sizeY)
		);
	}

	/* Set new sizes */
	i = pCMe->sizeX;
	pCMe->sizeX = pCMe->sizeY;
	pCMe->sizeY = i;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция reshape
 * </сводка>
 *
 * <описание>
 *   Функция меняет размерность матрицы, 
	 Если новая размерность больше текущей, создаются новые элементы и заполняются нулями
     Если новая размерность меньше текущей, то некоторые элементы будут удалены
 * </описание>
 *
 */
int16_t CEcoMatrix1_Reshape(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t dimX, /* in */ uint32_t dimY) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	IEcoVector1* pIEcoVector1 = 0;
	uint32_t i = 0;
	uint32_t j = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

	if (dimX > pCMe->sizeX) {
		// Add vectors
		pCMe->vectors = (IEcoVector1**)pCMe->m_pIMem->pVTbl->Realloc(
			pCMe->m_pIMem, pCMe->vectors, (uint32_t)(sizeof(IEcoVector1*) * dimX)
		);
		for (i = pCMe->sizeX; i < dimX; i++) {
			pIEcoVector1 = pCMe->vectors[0]->pVTbl->DeepCopy(pCMe->vectors[0]);
			if (pIEcoVector1 == 0) {
				return -1;
			}
			pCMe->vectors[i] = pIEcoVector1;
		}
	}
	if (dimX < pCMe->sizeX) {
		for (i = dimX; i < pCMe->sizeX; i++) {
			pCMe->vectors[i]->pVTbl->Release(pCMe->vectors[i]);
		}
		pCMe->vectors = (IEcoVector1**)pCMe->m_pIMem->pVTbl->Realloc(
			pCMe->m_pIMem, pCMe->vectors, (uint32_t)(sizeof(IEcoVector1*) * dimX)
		);
	}

	if (dimY != pCMe->sizeY) {
		for (i = 0; i < dimX; i++) {
			pCMe->vectors[i]->pVTbl->Reshape(pCMe->vectors[i], dimY);
		}
	}

	pCMe->sizeX = dimX;
	pCMe->sizeY = dimY;
    return 0;
}


/*
 *
 * <сводка>
 *   Функция DeepCopy
 * </сводка>
 *
 * <описание>
 *   Функция производит глубокое копирование исходной матрицы и возвращает указатель на новую
 * </описание>
 *
 */
struct IEcoMatrix1* CEcoMatrix1_DeepCopy(/* in */ struct IEcoMatrix1* me) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	CEcoMatrix1* pNewMatrix = 0;
	IEcoMatrix1* newPIEcoMatrix = 0;
	IEcoVector1* copiedVector = 0;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

	/* Получение интерфейса */
	isSuccess = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoMatrix1, 0, &IID_IEcoMatrix1, (void**) &newPIEcoMatrix);
    if (isSuccess != 0 && newPIEcoMatrix == 0) {
        return 0;
    }

	isSuccess = newPIEcoMatrix->pVTbl->InitBySize(newPIEcoMatrix, pCMe->sizeX, pCMe->sizeY);
	if (isSuccess != 0) {
		return 0;
	}

	pNewMatrix = (CEcoMatrix1*) newPIEcoMatrix;
	for (i = 0; i < pCMe->sizeX; i++) {
		copiedVector = pCMe->vectors[i]->pVTbl->DeepCopy(pCMe->vectors[i]);
		if (copiedVector == 0) {
			return 0;
		}
		pNewMatrix->vectors[i] = copiedVector;
	}
    return newPIEcoMatrix;
}


/*
 *
 * <сводка>
 *   Функция map
 * </сводка>
 *
 * <описание>
 *   Функция применяет заданную функцию ко всем элементам матрицы
 * </описание>
 *
 */
int16_t CEcoMatrix1_Map(/* in */ struct IEcoMatrix1*me, /* in */ void (*func)(void*)) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || func == 0 || pCMe->vectors == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->Map(pCMe->vectors[i], func);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция replaceValue
 * </сводка>
 *
 * <описание>
 *   Функция заменяет все элементы с заданным значением на новое значение
 * </описание>
 *
 */
int16_t CEcoMatrix1_ReplaceValue(/* in */ struct IEcoMatrix1* me, /* in */ void* oldValue, void* newValue) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || oldValue == 0 || newValue == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->ReplaceValue(pCMe->vectors[i], oldValue, newValue);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция addValue
 * </сводка>
 *
 * <описание>
 *   Функция добавляет заданное значение ко всем элементам матрицы.
     Доступно только для типов Int и Double
 * </описание>
 *
 */
int16_t CEcoMatrix1_AddValue(/* in */ struct IEcoMatrix1* me, /* in */ void* value) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->AddValue(pCMe->vectors[i], value);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция subValue
 * </сводка>
 *
 * <описание>
 *   Функция вычитает заданное значение из всех элементов матрицы.
     Доступно только для типов Int и Double
 * </описание>
 *
 */
int16_t CEcoMatrix1_SubValue(/* in */ struct IEcoMatrix1* me, /* in */ void* value) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->SubValue(pCMe->vectors[i], value);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция mulValue
 * </сводка>
 *
 * <описание>
 *   Функция умножает каждый элемент матрицы на заданное значение.
     Доступно только для типов Int и Double
 * </описание>
 *
 */
int16_t CEcoMatrix1_MulValue(/* in */ struct IEcoMatrix1* me, /* in */ void* value) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->MulValue(pCMe->vectors[i], value);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция divValue
 * </сводка>
 *
 * <описание>
 *   Функция заменяет каждый элемент матрицы частным от заданного значения.
     Доступно только для типов Int и Double
 * </описание>
 *
 */
int16_t CEcoMatrix1_DivValue(/* in */ struct IEcoMatrix1* me, /* in */ void* value) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->DivValue(pCMe->vectors[i], value);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция modValue
 * </сводка>
 *
 * <описание>
 *   Функция заменяет каждый элемент матрицы остатком от деления на заданное число.
     Доступно только для типа Int.
 * </описание>
 *
 */
int16_t CEcoMatrix1_ModValue(/* in */ struct IEcoMatrix1* me, /* in */ void* value) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->ModValue(pCMe->vectors[i], value);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция addMatrix
 * </сводка>
 *
 * <описание>
 *   Функция складывает исходную матрицу с матрицей, переданной в параметры.
     Размерности матриц должны совпадать.
 * </описание>
 *
 */
int16_t CEcoMatrix1_AddMatrix(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	CEcoMatrix1* pCMatrix = (CEcoMatrix1*)matrix;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || matrix == 0 || pCMatrix->sizeX != pCMe->sizeX || pCMatrix->sizeY != pCMe->sizeY) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->AddVector(pCMe->vectors[i], pCMatrix->vectors[i]);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция subMatrix
 * </сводка>
 *
 * <описание>
 *   Функция вычитает матрицу, переданную в параметры из исходной матрицы.
     Размерности матриц должны совпадать.
 * </описание>
 *
 */
int16_t CEcoMatrix1_SubMatrix(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	CEcoMatrix1* pCMatrix = (CEcoMatrix1*)matrix;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || matrix == 0 || pCMatrix->sizeX != pCMe->sizeX || pCMatrix->sizeY != pCMe->sizeY) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->SubVector(pCMe->vectors[i], pCMatrix->vectors[i]);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция mulMatrix
 * </сводка>
 *
 * <описание>
 *   Функция умножает исходную матрицу на матрицу, переданную в параметры из исходной матрицы.
     Размерности матриц должны быть подходящими для умножение. Доступно для типов Int и Double.
 * </описание>
 *
 */
int16_t CEcoMatrix1_MulMatrix(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	CEcoMatrix1* pCMatrix = (CEcoMatrix1*)matrix;
	CEcoMatrix1* pCMeCopy = 0;
	IEcoMatrix1* meCopy = 0;
	int16_t isSuccess = 0;
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t k = 0;
	int32_t int_acc = 0;
	double_t double_t_acc = 0;

    /* Проверка указателей и размерности */
	if (me == 0 || matrix == 0 || pCMatrix->sizeX != pCMe->sizeY) {
        return -1;
    }

	meCopy = me->pVTbl->DeepCopy(me);
	pCMeCopy = (CEcoMatrix1*)meCopy;
	if (pCMe->sizeY < pCMatrix->sizeY) {
		me->pVTbl->Reshape(me, pCMe->sizeX, pCMatrix->sizeY);
	}

	for (i = 0; i < pCMe->sizeX; i++) {
		for (j = 0; j < pCMe->sizeY; j++) {
			switch (pCMe->vectors[i]->pVTbl->Get_Type(pCMe->vectors[i])) {
				case ECO_SET_1_INTEGER_TYPE:
					for (k = 0; k < pCMeCopy->sizeY; k++) {
						int_acc += *((int32_t*)(pCMeCopy->vectors[i]->pVTbl->At(pCMeCopy->vectors[i], k))) * *((int32_t*)(pCMatrix->vectors[k]->pVTbl->At(pCMatrix->vectors[k], j)));
					}
					pCMe->vectors[i]->pVTbl->Set(pCMe->vectors[i], j, &int_acc);
					int_acc = 0;
					break;
				case ECO_SET_1_DOUBLE_TYPE:
					for (k = 0; k < pCMeCopy->sizeY; k++) {
						double_t_acc += *((double_t*)(pCMeCopy->vectors[i]->pVTbl->At(pCMeCopy->vectors[i], k))) * *((double_t*)(pCMatrix->vectors[i]->pVTbl->At(pCMatrix->vectors[i], j)));
					}
					pCMe->vectors[i]->pVTbl->Set(pCMe->vectors[i], j, &double_t_acc);
					double_t_acc = 0;
					break;
			}
		}
	}
	meCopy->pVTbl->Release(meCopy);
    return 0;
}


/*
 *
 * <сводка>
 *   Функция mulMatrixElementwise
 * </сводка>
 *
 * <описание>
 *   Функция умножает (поэлементно умножает элементы матрицы) исходную матрицу на матрицу, переданную в параметры из исходной матрицы.
     Размерности матриц должны быть подходящими для умножения.
 * </описание>
 *
 */
int16_t CEcoMatrix1_MulMatrixElementwise(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	CEcoMatrix1* pCMatrix = (CEcoMatrix1*)matrix;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || matrix == 0 || pCMatrix->sizeX != pCMe->sizeX || pCMatrix->sizeY != pCMe->sizeY) {
        return -1;
    }

	for (i = 0; i < pCMe->sizeX; i++) {
		isSuccess = pCMe->vectors[i]->pVTbl->MulVector(pCMe->vectors[i], pCMatrix->vectors[i]);
		if (isSuccess != 0) {
			return -1;
		}
	}

    return 0;
}


/*
 *
 * <сводка>
 *   Функция join
 * </сводка>
 *
 * <описание>
 *   Функция объединяет матрицы.
     @Параметр isAppend: определяет, новая матрица добавляется в начало либо слева (любое число != 0) или в конец либо справа (0)
	 @Параметр isAlongAxisX: определяет, вдоль какой оси проводить объединение
 * </описание>
 *
 */
int16_t CEcoMatrix1_Join(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix,    
        /* in */ int8_t isAppend, /* in */ int8_t isAlongAxisX) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	CEcoMatrix1* pCMatrix = (CEcoMatrix1*)matrix;
	IEcoVector1* pIEcoVector1 = 0;
	int16_t isSuccess = 0;
	uint32_t i = 0;

    /* Проверка указателей и размерностей */
	if (me == 0 || matrix == 0 || 
			isAlongAxisX != 0 && pCMe->sizeY != pCMatrix->sizeY ||
			isAlongAxisX == 0 && pCMe->sizeX != pCMatrix->sizeX) {
        return -1;
    }

	if (isAlongAxisX == 0) {  // Join along axis Y
		for (i = 0; i < pCMe->sizeX; i++) {
			isSuccess = pCMe->vectors[i]->pVTbl->Join(pCMe->vectors[i], pCMatrix->vectors[i], isAppend);
			if (isSuccess != 0) {
				return -1;
			}
		}
		pCMe->sizeY += pCMatrix->sizeY;
	} else {  // Join along axis X
		/* Create more vectors */
		pCMe->vectors = (IEcoVector1**)pCMe->m_pIMem->pVTbl->Realloc(
			pCMe->m_pIMem, pCMe->vectors, (uint32_t)(sizeof(IEcoVector1*) * (pCMe->sizeX + pCMatrix->sizeX))
		);
		if (isAppend != 0) {  // Append to the end of original matrix
			for (i = 0; i < pCMatrix->sizeX; i++) {
				pIEcoVector1 = pCMatrix->vectors[i]->pVTbl->DeepCopy(pCMatrix->vectors[i]);
				if (pIEcoVector1 == 0) {
					return -1;
				}
				pCMe->vectors[pCMe->sizeX + i] = pIEcoVector1;
			}
		} else {  // Insert new matrix to the beginning of the original one
			for (i = pCMe->sizeX; i > 0; i--) {
				pCMe->vectors[pCMatrix->sizeX + i - 1] = pCMe->vectors[i - 1];
			}
			for (i = 0; i < pCMatrix->sizeX; i++) {
				pIEcoVector1 = pCMatrix->vectors[i]->pVTbl->DeepCopy(pCMatrix->vectors[i]);
				if (pIEcoVector1 == 0) {
					return -1;
				}
				pCMe->vectors[i] = pIEcoVector1;
			}
		}
		pCMe->sizeX += pCMatrix->sizeX;
	}
    return 0;
}


/*
 *
 * <сводка>
 *   Функция Mean
 * </сводка>
 *
 * <описание>
 *   Функция считает среднее арифметическое из всех элементов матрицы и возвращает его в double_t.
	 Доступно только для типов Int и Double.
 * </описание>
 *
 */
double_t CEcoMatrix1_Mean(/* in */ struct IEcoMatrix1* me) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	uint32_t i = 0;
	double_t acc = 0;

    /* Проверка указателей */
	if (me == 0 || pCMe->vectors == 0 || pCMe->sizeX == 0) {
        return 0;
    }
	
	for (i = 0; i < pCMe->sizeX; i++) {
		acc += pCMe->vectors[i]->pVTbl->Mean(pCMe->vectors[i]);
	}

    return acc / pCMe->sizeX;
}


/*
 *
 * <сводка>
 *   Функция GetCol
 * </сводка>
 *
 * <описание>
 *   Функция возвращает вектор, находящийся на позиции с заданном индексом.
 * </описание>
 *
 */
struct IEcoVector1* CEcoMatrix1_GetCol(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t colIndex) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;

    /* Проверка указателей */
	if (me == 0 || colIndex >= pCMe->sizeX || pCMe->vectors == 0) {
        return 0;
    }

    return pCMe->vectors[colIndex];
}


/*
 *
 * <сводка>
 *   Функция RemoveCol
 * </сводка>
 *
 * <описание>
 *   Функция удаляет вектор на заданной позиции
 * </описание>
 *
 */
struct IEcoVector1* CEcoMatrix1_RemoveCol(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t colIndex) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
	IEcoVector1* removedVector = 0;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || pCMe->sizeX == 0 || colIndex >= pCMe->sizeX || pCMe->vectors == 0) {
        return 0;
    }

	removedVector = pCMe->vectors[colIndex];
	for (i = colIndex + 1; i < pCMe->sizeX; i++) {
		pCMe->vectors[i - 1] = pCMe->vectors[i];
	}
	pCMe->vectors = (IEcoVector1**)pCMe->m_pIMem->pVTbl->Realloc(
		pCMe->m_pIMem, pCMe->vectors, (uint32_t)(sizeof(IEcoVector1*) * (pCMe->sizeX - 1))
	);
	pCMe->sizeX -= 1;
    return removedVector;
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
int16_t initCEcoMatrix1(/*in*/ struct IEcoMatrix1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

	/* Получение интерфейс для работы с вектором */
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoVector1, 0, &IID_IEcoVector1, (void**)&pCMe->m_pIVector);
    if (result != 0 || pCMe->m_pIVector == 0) {
        return result;
    }

    return result;
}

/* Create Virtual Table */
IEcoMatrix1VTbl g_x23F199B61FA041DC821769E891FC30F6VTbl = {
    CEcoMatrix1_QueryInterface,
    CEcoMatrix1_AddRef,
    CEcoMatrix1_Release,
	CEcoMatrix1_InitBySize,
	CEcoMatrix1_CreateVectorAtIndex,
	CEcoMatrix1_SetVectorAtIndex,
	CEcoMatrix1_InsertVectorAtIndex,
	CEcoMatrix1_PrintMatrix,
    CEcoMatrix1_Size,
    CEcoMatrix1_IsEmpty,
    CEcoMatrix1_At,
	CEcoMatrix1_Set,
    CEcoMatrix1_IndexOf,
    CEcoMatrix1_Clear,
    CEcoMatrix1_Transpose,
    CEcoMatrix1_Reshape,
    CEcoMatrix1_DeepCopy,
    CEcoMatrix1_Map,
    CEcoMatrix1_ReplaceValue,
    CEcoMatrix1_AddValue,
    CEcoMatrix1_SubValue,
    CEcoMatrix1_MulValue,
    CEcoMatrix1_DivValue,
    CEcoMatrix1_ModValue,
    CEcoMatrix1_AddMatrix,
    CEcoMatrix1_SubMatrix,
    CEcoMatrix1_MulMatrix,
    CEcoMatrix1_MulMatrixElementwise,
    CEcoMatrix1_Join,
    CEcoMatrix1_Mean,
    CEcoMatrix1_GetCol,
	CEcoMatrix1_RemoveCol
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
int16_t createCEcoMatrix1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoMatrix1** ppIEcoMatrix1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoMatrix1* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoMatrix1 == 0 || pIUnkSystem == 0) {
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
    pCMe = (CEcoMatrix1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoMatrix1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

	 /* Сохранение указателя на интерфейс для работы с интерфейсной шиной */
    pCMe->m_pIBus = pIBus;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoMatrix1 */
    pCMe->m_pVTblIEcoMatrix1 = &g_x23F199B61FA041DC821769E891FC30F6VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoMatrix1 = (IEcoMatrix1*)pCMe;

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
void deleteCEcoMatrix1(/* in */ IEcoMatrix1* pIEcoMatrix1) {
    CEcoMatrix1* pCMe = (CEcoMatrix1*)pIEcoMatrix1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoMatrix1 != 0 ) {
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
