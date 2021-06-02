/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoVector1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoVector1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "CEcoVector1.h"
#include "IdEcoVector1.h"
#include <stdio.h> 

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoVector1
 * </описание>
 *
 */
int16_t CEcoVector1_QueryInterface(/* in */ struct IEcoVector1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoVector1) ) {
        *ppv = &pCMe->m_pVTblIEcoVector1;
        pCMe->m_pVTblIEcoVector1->AddRef((IEcoVector1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoVector1;
        pCMe->m_pVTblIEcoVector1->AddRef((IEcoVector1*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoVector1
 * </описание>
 *
 */
uint32_t CEcoVector1_AddRef(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;

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
 *   Функция Release для интерфейса IEcoVector1
 * </описание>
 *
 */
uint32_t CEcoVector1_Release(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoVector1((IEcoVector1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция InitByType
 * </сводка>
 *
 * <описание>
 *   Функция инициализирует вектор согласно используемому типу
 * </описание>
 *
 */
int16_t CEcoVector1_InitByType(/* in */ struct IEcoVector1* me,  /* in */ uchar_t type) {
	CEcoVector1* pCMe = (CEcoVector1*) me;
    int16_t result = -1;

	/* Проверка указателей */
	if (me == 0 || type > 4 || pCMe->type != -1) {
		return -1;
	}

	/* Выбираем дефолтовый интерфейс сравнения в зависимости от используемого типа */
    pCMe->size = 0;
	pCMe->type = type;
    switch (type) 
    {
    case ECO_SET_1_STRING_TYPE:
        result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoComparator1, 0, &IID_IEcoComparator1String, (void**)&pCMe->m_pIComparator);
        if (result != 0 || pCMe->m_pIComparator == 0) {
            /* Ошибка */
            return result;
        }
        break;
    case ECO_SET_1_INTEGER_TYPE:
        result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoComparator1, 0, &IID_IEcoComparator1Int, (void**)&pCMe->m_pIComparator);
        if (result != 0 || pCMe->m_pIComparator == 0) {
            /* Ошибка */
            return result;
        }
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoComparator1, 0, &IID_IEcoComparator1Double, (void**)&pCMe->m_pIComparator);
        if (result != 0 || pCMe->m_pIComparator == 0) {
            /* Ошибка */
            return result;
        }
        break;
    default:
        result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoComparator1, 0, &IID_IEcoComparator1Pointer, (void**)&pCMe->m_pIComparator);
        if (result != 0 || pCMe->m_pIComparator == 0) {
            /* Ошибка */
            return result;
        }
        break;
    }
	return 0;
}


/*
 *
 * <сводка>
 *   Функция InitByTypeAndComparator
 * </сводка>
 *
 * <описание>
 *   Функция инициализирует вектор согласно используемому типу и интерфейсу сравнения
 * </описание>
 *
 */
int16_t CEcoVector1_InitByTypeAndComparator(/* in */ struct IEcoVector1* me,  /* in */ uchar_t type, /* in */ IEcoComparator1* pIComparator) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || type > 4 || pIComparator == 0 || pCMe->type != -1) {
        return -1;
    }

    /* Устанавливаем значения */
    pCMe->size = 0;
    pCMe->type = type;
    pCMe->m_pIComparator = pIComparator;
    pIComparator->pVTbl->AddRef(pIComparator);
    return 0;
}


/*
 *
 * <сводка>
 *   Функция Get_Type
 * </сводка>
 *
 * <описание>
 *   Функция возвращает тип используемых данных
 * </описание>
 *
 */
int16_t CEcoVector1_Get_Type(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    /* Возврат значения */
    return pCMe->type;
}


/*
 *
 * <сводка>
 *   Функция Get_Comparator
 * </сводка>
 *
 * <описание>
 *   Функция возвращает используемый интерфейс сравнения
 * </описание>
 *
 */
IEcoComparator1* CEcoVector1_Get_Comparator(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || pCMe->type == -1) {
        return 0;
    }

    /* Возврат значения */
    return pCMe->m_pIComparator;
}


/*
 *
 * <сводка>
 *   Функция Size
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t CEcoVector1_Size(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*) me;
	uint32_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Возврат значения */
    return pCMe->size;
}

/*
 *
 * <сводка>
 *   Функция IsEmpty
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
bool_t CEcoVector1_IsEmpty(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*) me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Возврат значения */
    return pCMe->size == 0;
}

/*
 *
 * <сводка>
 *   Функция At
 * </сводка>
 *
 * <описание>
 *   Функция возвращает элемент вектора с заданным индексом
 * </описание>
 *
 */
void* CEcoVector1_At(/* in */ struct IEcoVector1* me, /* in */ uint32_t index) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	void* result = 0;

    /* Проверка указателей и корректности индекса*/
    if (me == 0 || index >= pCMe->size) {
        return 0;
    }

	switch (pCMe->type)
    {
    case ECO_SET_1_STRING_TYPE:
		result = (void*)((char_t**)pCMe->data + index);
        break;
    case ECO_SET_1_INTEGER_TYPE:
        result = (void*)((int32_t*)pCMe->data + index);
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        result = (void*)((double_t*)pCMe->data + index);
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
    }

    return result;
}


/*
 *
 * <сводка>
 *   Функция Set
 * </сводка>
 *
 * <описание>
 *   Функция устанавливает заданное значение элементу с заданным индексом
 * </описание>
 *
 */
int16_t CEcoVector1_Set(/* in */ struct IEcoVector1* me, /* in */ uint32_t index, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	void* result = 0;

    /* Проверка указателей и корректности индекса*/
    if (me == 0 || index >= pCMe->size) {
        return -1;
    }

	switch (pCMe->type) {
		case ECO_SET_1_STRING_TYPE:
			((char_t**)pCMe->data)[index] = pCMe->m_pIString->pVTbl->Clone(pCMe->m_pIString, *((char_t**)value));;
			break;
		case ECO_SET_1_INTEGER_TYPE:
			((int32_t*)pCMe->data)[index] = *((int32_t*)value);
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			((double_t*)pCMe->data)[index] = *((double_t*)value);
			break;
		case ECO_SET_1_POINTER_TYPE:
			// TODO implement
			break;
		case ECO_SET_1_OBJECT_TYPE:
			// TODO implement
			break;
    }

    return 0;
}


/*
 *
 * <сводка>
 *   Функция IndexOf
 * </сводка>
 *
 * <описание>
 *   Возвращает индекс первого элемента который имеет заданное значение, если элемент не найден, возвращается -1
 * </описание>
 *
 */
int32_t CEcoVector1_IndexOf(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;
	int32_t foundIndex = -1;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	for (i = 0; i < pCMe->size; ++i) {
		if (pCMe->type == ECO_SET_1_STRING_TYPE) {
			if (pCMe->m_pIComparator->pVTbl->Compare(pCMe->m_pIComparator, *((char_t**)(pCMe->m_pVTblIEcoVector1->At((IEcoVector1*)pCMe, i))), *((char_t**)value)) == 0) {
				foundIndex = i;
				break;
			}
		} else {
			if (pCMe->m_pIComparator->pVTbl->Compare(pCMe->m_pIComparator, pCMe->m_pVTblIEcoVector1->At((IEcoVector1*)pCMe, i), value) == 0) {
				foundIndex = i;
				break;
			}
		}
	}
    return foundIndex;
}


void* CEcoVector1_AllocateData(/* in */ CEcoVector1* pCMe, int16_t type, void* data, int32_t size) {
    IEcoUnknown* pIData = 0;
    void* returnData = 0;
	void* currentElem = 0;
	int32_t i;

    /* Проверка указателей */
    if (pCMe == 0 || data == 0) {
        return 0;
    }

    /* Выделяем память */
    switch (type)
    {
    case ECO_SET_1_STRING_TYPE:
		returnData = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(char_t*) * size);
		for(i = 0; i < size; i++) {
			currentElem = pCMe->m_pIString->pVTbl->Clone(pCMe->m_pIString, ((char_t**)data)[i]);
			(char_t*)((char_t**)returnData)[i] = (char_t*)currentElem;
		}
        break;
    case ECO_SET_1_INTEGER_TYPE:
        returnData = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(int32_t) * size);
		for(i = 0; i < size; i++) {
			((int32_t*)returnData)[i] = ((int32_t*)data)[i];
		}
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        returnData = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(double_t) * size);
		for(i = 0; i < size; i++) {
			((double_t*)returnData)[i] = ((double_t*)data)[i];
		}
        *(double_t*)returnData = *(double_t*)data;
        break;
    case ECO_SET_1_POINTER_TYPE:
        returnData = data;
        break;
    case ECO_SET_1_OBJECT_TYPE:
        pIData = (IEcoUnknown*)data;
        returnData = data;
        pIData->pVTbl->AddRef(pIData);
        break;
    }

    /* Возвращение результата */
    return returnData;
}


void* CEcoVector1_ReallocateData(/* in */ CEcoVector1* pCMe, int16_t type, void* data, int32_t size) {
    IEcoUnknown* pIData = 0;
    void* returnData = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (pCMe == 0 || data == 0) {
        return 0;
    }

    /* Выделяем память */
    switch (type)
    {
    case ECO_SET_1_STRING_TYPE:
		// В случае когда новый размер меньше текущего, освобождаем память
		for (i = size; i < pCMe->size; i++) {
			if (((char_t**)data)[i] != 0) {
				pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, ((char_t**)data)[i]);
			}
		}
		returnData = pCMe->m_pIMem->pVTbl->Realloc(pCMe->m_pIMem, data, (uint32_t)(sizeof(char_t*) * size));
        break;
    case ECO_SET_1_INTEGER_TYPE:
        returnData = pCMe->m_pIMem->pVTbl->Realloc(pCMe->m_pIMem, data, (uint32_t)(sizeof(int32_t) * size));
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        returnData = pCMe->m_pIMem->pVTbl->Realloc(pCMe->m_pIMem, data, (uint32_t)(sizeof(double_t) * size));
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
    }

    /* Возвращение результата */
    return returnData;
}


/*
 *
 * <сводка>
 *   Функция FreeData
 * </сводка>
 *
 * <описание>
 *   Функция производит удаление памяти под данные согласно используемому типу
 * </описание>
 *
 */
int16_t CEcoVector1_FreeData(/* in */ CEcoVector1* pCMe, int16_t type, void* data) {
    IEcoUnknown* pIData = 0;
	uint32_t i = 0;

    /* Проверка указателей */
    if (pCMe == 0 || data == 0) {
        return -1;
    }

    /* Освобождаем память */
    if (data != 0) {
        switch (type) {
        case ECO_SET_1_OBJECT_TYPE:
            pIData = (IEcoUnknown*)data;
            pIData->pVTbl->Release(pIData);
            break;
        case ECO_SET_1_STRING_TYPE:
			for (i = 0; i < pCMe->size; i++) {
				pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, ((char_t**)data)[i]);
			}
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, data);
            break;
        case ECO_SET_1_INTEGER_TYPE:
        case ECO_SET_1_DOUBLE_TYPE:
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, data);
            break;
        }
    }

    /* Возвращение результата */
    return 0;
}


/*
 *
 * <сводка>
 *   Функция FromArray
 * </сводка>
 *
 * <описание>
 *   Функция заполняет вектор значениями из массива
 * </описание>
 *
 */
int16_t CEcoVector1_FromArray(/* in */ struct IEcoVector1* me, /* in */ void* sourceArray, int32_t size) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	void* res = 0;

    /* Проверка указателей */
    if (me == 0 || sourceArray == 0) {
        return -1;
    }
	
	res = pCMe->AllocateData(pCMe, pCMe->type, sourceArray, size);
	if (res == 0) {
		// Ошибка при выделении памяти
		return -1;
	}

	pCMe->size = size;
	pCMe->data = res;
    return 0;
}


/*
 *
 * <сводка>
 *   Функция PrintVector
 * </сводка>
 *
 * <описание>
 *   Функция выводит на stdout элементы вектора разделённые пробелом
 * </описание>
 *
 */
void CEcoVector1_PrintVector(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i;

    /* Проверка указателей */
    if (me == 0 ) {
        return;
    }

	for(i = 0; i < pCMe->size; ++i){
		switch (pCMe->type)
        {
        case ECO_SET_1_INTEGER_TYPE:
            printf("%i ", ((int32_t*)pCMe->data)[i]);
            break;
        case ECO_SET_1_DOUBLE_TYPE:
            printf("%.1f ", ((double_t*)pCMe->data)[i]);
            break;
        case ECO_SET_1_STRING_TYPE:
            printf("%s ", ((char_t**)pCMe->data)[i]);
            break;
        default:
            printf("?) ");
            break;
        }
	}
    return;
}


/*
 *
 * <сводка>
 *   Функция Push
 * </сводка>
 *
 * <описание>
 *   Добавление элемента в конец
 * </описание>
 *
 */
int16_t CEcoVector1_Push(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	return ((IEcoVector1*)pCMe)->pVTbl->InsertAt((IEcoVector1*)pCMe, pCMe->size, value);
}

/*
 *
 * <сводка>
 *   Функция Insert
 * </сводка>
 *
 * <описание>
 *   Добавление элемента в начало
 * </описание>
 *
 */
int16_t CEcoVector1_Insert(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return -1;
    }

	return ((IEcoVector1*)pCMe)->pVTbl->InsertAt((IEcoVector1*)pCMe, 0, value);
}

/*
 *
 * <сводка>
 *   Функция InsertAt
 * </сводка>
 *
 * <описание>
 *   Вставка элемента на позицию с заданным индексом со сдвигом элементов
 * </описание>
 *
 */
int16_t CEcoVector1_InsertAt(/* in */ struct IEcoVector1* me, /* in */ uint32_t index, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || index > pCMe->size) {
        return -1;
    }

	/* Перераспределение памяти и заполнение новых элементов */
	if (pCMe->data != 0) {
		pCMe->data = pCMe->ReallocateData(pCMe, pCMe->type, pCMe->data, pCMe->size + 1);
	} else {
		pCMe->data = pCMe->AllocateData(pCMe, pCMe->type, value, 1);
	}
	switch (pCMe->type)
    {
    case ECO_SET_1_STRING_TYPE:
		for (i = pCMe->size; i > index ; i--) {
			((char_t**)pCMe->data)[i] = ((char_t**)pCMe->data)[i-1];
		}
		((char_t**)pCMe->data)[index] = pCMe->m_pIString->pVTbl->Clone(pCMe->m_pIString, *((char_t**)value));
        break;
    case ECO_SET_1_INTEGER_TYPE:
        for (i = pCMe->size; i > index ; i--) {
			((int32_t*)pCMe->data)[i] = ((int32_t*)pCMe->data)[i-1];
		}
		((int32_t*)pCMe->data)[index] = *((int32_t*)value);
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        for (i = pCMe->size; i > index ; i--) {
			((double_t*)pCMe->data)[i] = ((double_t*)pCMe->data)[i-1];
		}
		((double_t*)pCMe->data)[index] = *((double_t*)value);
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
    }
	pCMe->size += 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Функция RemoveAt
 * </сводка>
 *
 * <описание>
 *   Функция удаляет элемент на позиции с заданным индексом со сдвигом элементов
 * </описание>
 *
 */
int16_t CEcoVector1_RemoveAt(/* in */ struct IEcoVector1* me, /* in */ uint32_t index) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей и аргументов */
	if (me == 0 || index >= pCMe->size || pCMe->size == 0) {
        return -1;
    }


	switch (pCMe->type)
    {
    case ECO_SET_1_STRING_TYPE:
		for (i = index; i < pCMe->size-1; i++) {
			((char_t**)pCMe->data)[i] = pCMe->m_pIString->pVTbl->Clone(pCMe->m_pIString, ((char_t**)pCMe->data)[i+1]);
		}
		pCMe->data = pCMe->ReallocateData(pCMe, pCMe->type, pCMe->data, pCMe->size - 1);
        break;
    case ECO_SET_1_INTEGER_TYPE:
        for (i = index; i < pCMe->size-1; i++) {
			((int32_t*)pCMe->data)[i] = ((int32_t*)pCMe->data)[i+1];
		}
		pCMe->data = pCMe->ReallocateData(pCMe, pCMe->type, pCMe->data, pCMe->size - 1);
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        for (i = index; i < pCMe->size-1; i++) {
			((double_t*)pCMe->data)[i] = ((double_t*)pCMe->data)[i+1];
		}
		pCMe->data = pCMe->ReallocateData(pCMe, pCMe->type, pCMe->data, pCMe->size - 1);
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
    }

	pCMe->size -= 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Функция Clear
 * </сводка>
 *
 * <описание>
 *   Очищение вектора с освобождением памяти
 * </описание>
 *
 */
int16_t CEcoVector1_Clear(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pCMe->type == -1) {
        return -1;
    }

	result = pCMe->FreeData(pCMe, pCMe->type, pCMe->data);
	pCMe->data = 0;
	pCMe->size = 0;
    return result;
}

/*
 *
 * <сводка>
 *   Функция Reverse
 * </сводка>
 *
 * <описание>
 *   Переворот вектора
 * </описание>
 *
 */
int16_t CEcoVector1_Reverse(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;
	void* tmp = 0;

    /* Проверка указателей */
	if (me == 0 || pCMe->data == 0) {
        return -1;
    }

	switch (pCMe->type)
    {
    case ECO_SET_1_STRING_TYPE:
		tmp = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(char_t*));
		for (i = 0; i < pCMe->size / 2; i++) {
			*(char_t**)tmp = ((char_t**)pCMe->data)[i];
			((char_t**)pCMe->data)[i] = ((char_t**)pCMe->data)[pCMe->size - i - 1];
			((char_t**)pCMe->data)[pCMe->size - i - 1] = *(char_t**)tmp;
		}
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tmp);
        break;
    case ECO_SET_1_INTEGER_TYPE:
		tmp = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(int32_t));
		for (i = 0; i < pCMe->size / 2; i++) {
			*(int32_t*)tmp = ((int32_t*)pCMe->data)[i];
			((int32_t*)pCMe->data)[i] = ((int32_t*)pCMe->data)[pCMe->size - i - 1];
			((int32_t*)pCMe->data)[pCMe->size - i - 1] = *(int32_t*)tmp;
		}
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tmp);
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        tmp = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(double_t));
		for (i = 0; i < pCMe->size / 2; i++) {
			*(double_t*)tmp = ((double_t*)pCMe->data)[i];
			((double_t*)pCMe->data)[i] = ((double_t*)pCMe->data)[pCMe->size - i - 1];
			((double_t*)pCMe->data)[pCMe->size - i - 1] = *(double_t*)tmp;
		}
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tmp);
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Reshape
 * </сводка>
 *
 * <описание>
 *   Изменение размерности вектора (если новая размерность меньше текущей, то элементы удаляются)
 * </описание>
 *
 */
int16_t CEcoVector1_Reshape(/* in */ struct IEcoVector1* me, /* in */ uint32_t dim) {
    CEcoVector1* pCMe = (CEcoVector1*)me;

    /* Проверка указателей */
	if (me == 0 || pCMe->size == dim) {
        return -1;
    }

	pCMe->data = pCMe->ReallocateData(pCMe, pCMe->type, pCMe->data, dim);
	if (pCMe->data == 0 && dim != 0) {
		// Ошибка
		return -1;
	}
	pCMe->size = dim;
    
	return 0;
}

/*
 *
 * <сводка>
 *   Функция deepCopy
 * </сводка>
 *
 * <описание>
 *   Функция создаёт глубокую копию вектора
 * </описание>
 *
 */
struct IEcoVector1* CEcoVector1_DeepCopy(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	IEcoVector1* newPIEcoVector1 = 0;
	int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

	/* Получение интерфейса */
	result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoVector1, 0, &IID_IEcoVector1, (void**) &newPIEcoVector1);
    if (result != 0 && newPIEcoVector1 == 0) {
        return 0;
    }
	
	switch (pCMe->type)
    {
    case ECO_SET_1_STRING_TYPE:
		result = newPIEcoVector1->pVTbl->InitByType(newPIEcoVector1, ECO_SET_1_STRING_TYPE);
		if (result != 0) {
			return 0;
		}
        result = newPIEcoVector1->pVTbl->FromArray(newPIEcoVector1, pCMe->data, pCMe->size);
		if (result != 0) {
			return 0;
		}
        break;
    case ECO_SET_1_INTEGER_TYPE:
		result = newPIEcoVector1->pVTbl->InitByType(newPIEcoVector1, ECO_SET_1_INTEGER_TYPE);
		if (result != 0) {
			return 0;
		}
        result = newPIEcoVector1->pVTbl->FromArray(newPIEcoVector1, pCMe->data, pCMe->size);
		if (result != 0) {
			return 0;
		}
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        result = newPIEcoVector1->pVTbl->InitByType(newPIEcoVector1, ECO_SET_1_DOUBLE_TYPE);
		if (result != 0) {
			return 0;
		}
        result = newPIEcoVector1->pVTbl->FromArray(newPIEcoVector1, pCMe->data, pCMe->size);
		if (result != 0) {
			return 0;
		}
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
    }
    return newPIEcoVector1;
}

/*
 *
 * <сводка>
 *   Функция map
 * </сводка>
 *
 * <описание>
 *   Функция применяет переданную в параметр функцию ко всем элементам вектора
 * </описание>
 *
 */
int16_t CEcoVector1_Map(/* in */ struct IEcoVector1*me, /* in */ void (*func)(void*)) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || func == 0) {
        return -1;
    }

	switch (pCMe->type)
    {
    case ECO_SET_1_STRING_TYPE:
		for(i = 0; i < pCMe->size; i++) {
			func((char_t**)(pCMe->data) + i); 
		}
        break;
    case ECO_SET_1_INTEGER_TYPE:
		for(i = 0; i < pCMe->size; i++) {
			func((int32_t*)(pCMe->data) + i); 
		}
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        for(i = 0; i < pCMe->size; i++) {
			func((double_t*)(pCMe->data) + i); 
		}
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
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
int16_t CEcoVector1_ReplaceValue(/* in */ struct IEcoVector1* me, /* in */ void* oldValue, void* newValue) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || oldValue == 0 || newValue == 0) {
        return -1;
    }

	switch (pCMe->type)
    {
    case ECO_SET_1_STRING_TYPE:
		for (i = 0; i < pCMe->size; i++) {
			if (pCMe->m_pIComparator->pVTbl->Compare(
					pCMe->m_pIComparator,
					*((char_t**)(pCMe->m_pVTblIEcoVector1->At((IEcoVector1*)pCMe, i))),
					*((char_t**)oldValue)) == 0
			) {
				((char_t**)(pCMe->data))[i] = pCMe->m_pIString->pVTbl->Clone(pCMe->m_pIString, *((char_t**)newValue));
			}
		}
        break;
    case ECO_SET_1_INTEGER_TYPE:
		for(i = 0; i < pCMe->size; i++) {
			if(((int32_t*)(pCMe->data))[i] == *((int32_t*)oldValue)) {
				((int32_t*)(pCMe->data))[i] = *((int32_t*)newValue);
			}
		}
        break;
    case ECO_SET_1_DOUBLE_TYPE:
        for(i = 0; i < pCMe->size; i++) {
			if(((double_t*)(pCMe->data))[i] == *((double_t*)oldValue)) {
				((double_t*)(pCMe->data))[i] = *((double_t*)newValue);
			}
		}
        break;
    case ECO_SET_1_POINTER_TYPE:
        // TODO implement
        break;
    case ECO_SET_1_OBJECT_TYPE:
        // TODO implement
        break;
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
 *   Функция добавляет заданное значение ко всем элементам вектора
 * </описание>
 *
 */
int16_t CEcoVector1_AddValue(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0 || !(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return -1;
    }

	switch (pCMe->type)
    {
		case ECO_SET_1_INTEGER_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((int32_t*)(pCMe->data))[i] += *((int32_t*)value);
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((double_t*)(pCMe->data))[i] += *((double_t*)value);
			}
			break;
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
 *   Функция вычитает заданное значение из всех элементов вектора
 * </описание>
 *
 */
int16_t CEcoVector1_SubValue(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0 || !(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return -1;
    }

	switch (pCMe->type)
    {
		case ECO_SET_1_INTEGER_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((int32_t*)(pCMe->data))[i] -= *((int32_t*)value);
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((double_t*)(pCMe->data))[i] -= *((double_t*)value);
			}
			break;
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
 *   Функция умножает на заданное значение все элементы вектора
 * </описание>
 *
 */
int16_t CEcoVector1_MulValue(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0 || !(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return -1;
    }

	switch (pCMe->type)
    {
		case ECO_SET_1_INTEGER_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((int32_t*)(pCMe->data))[i] *= *((int32_t*)value);
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((double_t*)(pCMe->data))[i] *= *((double_t*)value);
			}
			break;
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
 *   Функция делит каждый элемент на заданное значение. Если значение равно 0, то элементы вектора не изменяются
 * </описание>
 *
 */
int16_t CEcoVector1_DivValue(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0 || !(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return -1;
    }

	switch (pCMe->type)
    {
		case ECO_SET_1_INTEGER_TYPE:
			/* Check on zero division */
			if (*((int32_t*)value) == 0) {
				return -1;
			}
			for(i = 0; i < pCMe->size; i++) {
				((int32_t*)(pCMe->data))[i] /= *((int32_t*)value);
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			/* Check on zero division */
			if (*((double_t*)value) == 0.0) {
				return -1;
			}
			for(i = 0; i < pCMe->size; i++) {
				((double_t*)(pCMe->data))[i] /= *((double_t*)value);
			}
			break;
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
 *   Функция заменяет каждый элемент вектора на остаток от деления на заданное значение.
     Если значение равно 0, то элементы вектора не изменяются.
 * </описание>
 *
 */
int16_t CEcoVector1_ModValue(/* in */ struct IEcoVector1* me, /* in */ void* value) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;

    /* Проверка указателей и типа */
    if (me == 0 || pCMe->type != ECO_SET_1_INTEGER_TYPE) {
        return -1;
    }

	/* Check on zero division */
	if (*((int32_t*)value) == 0) {
		return -1;
	}

	for(i = 0; i < pCMe->size; i++) {
		((int32_t*)(pCMe->data))[i] %= *((int32_t*)value);
	}

    return 0;
}

/*
 *
 * <сводка>
 *   Функция addVector
 * </сводка>
 *
 * <описание>
 *   Функция складывает поэлементно два вектора. Вектора должны быть одинаковой размерности.
 * </описание>
 *
 */
int16_t CEcoVector1_AddVector(/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	CEcoVector1* sourceVector = (CEcoVector1*)vector;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || vector == 0 || sourceVector->size != pCMe->size || sourceVector->type != pCMe->type ||
			!(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return -1;
    }

	switch (pCMe->type) {
		case ECO_SET_1_INTEGER_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((int32_t*)(pCMe->data))[i] += ((int32_t*)(sourceVector->data))[i];
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((double_t*)(pCMe->data))[i] += ((double_t*)(sourceVector->data))[i];
			}
			break;
	}
    return 0;
}

/*
 *
 * <сводка>
 *   Функция subVector
 * </сводка>
 *
 * <описание>
 *   Функция вычитает поэлементно два вектора. Вектора должны быть одинаковой размерности.
 * </описание>
 *
 */
int16_t CEcoVector1_SubVector(/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	CEcoVector1* sourceVector = (CEcoVector1*)vector;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || vector == 0 || sourceVector->size != pCMe->size || sourceVector->type != pCMe->type ||
			!(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return -1;
    }

	switch (pCMe->type) {
		case ECO_SET_1_INTEGER_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((int32_t*)(pCMe->data))[i] -= ((int32_t*)(sourceVector->data))[i];
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((double_t*)(pCMe->data))[i] -= ((double_t*)(sourceVector->data))[i];
			}
			break;
    }

	return 0;
}

/*
 *
 * <сводка>
 *   Функция MulVector
 * </сводка>
 *
 * <описание>
 *   Функция перемножает поэлементно два вектора. Вектора должны быть одинаковой размерности.
 * </описание>
 *
 */
int16_t CEcoVector1_MulVector(/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	CEcoVector1* sourceVector = (CEcoVector1*)vector;
	uint32_t i = 0;

    /* Проверка указателей */
	if (me == 0 || vector == 0 || sourceVector->size != pCMe->size || sourceVector->type != pCMe->type ||
			!(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return -1;
    }

	switch (pCMe->type) {
		case ECO_SET_1_INTEGER_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((int32_t*)(pCMe->data))[i] *= ((int32_t*)(sourceVector->data))[i];
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			for(i = 0; i < pCMe->size; i++) {
				((double_t*)(pCMe->data))[i] *= ((double_t*)(sourceVector->data))[i];
			}
			break;
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
 *   Функция соединяет 2 вектора, если параметр isAppend равен 0, то новый вектор добавляется к концу текущего, если не равен - к началу.
 * </описание>
 *
 */
int16_t CEcoVector1_Join(/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector, /* in */ int8_t isAppend) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	CEcoVector1* sourceVector = (CEcoVector1*)vector;
	uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || vector == 0) {
        return -1;
    }

	/* Перераспределение памяти и заполнение новых элементов */
	pCMe->data = pCMe->ReallocateData(pCMe, pCMe->type, pCMe->data, pCMe->size + sourceVector->size);
	switch (pCMe->type) {
		case ECO_SET_1_STRING_TYPE:
			if (isAppend != 0) {
				// Append elements from source vector to the end of current one
				for (i = 0; i < sourceVector->size; i++) {
					((char_t**)pCMe->data)[i + pCMe->size] = pCMe->m_pIString->pVTbl->Clone(pCMe->m_pIString, ((char_t**)sourceVector->data)[i]);
				}
			} else {
				// Insert elements from source vector to the beginning of current one
				for (i = pCMe->size; i > 0; i--) {
					((char_t**)pCMe->data)[sourceVector->size + i - 1] = ((char_t**)pCMe->data)[i-1];
				}
				for (i = 0; i < sourceVector->size; i++) {
					((char_t**)pCMe->data)[i] = pCMe->m_pIString->pVTbl->Clone(pCMe->m_pIString, ((char_t**)sourceVector->data)[i]);
				}
			}
			break;
		case ECO_SET_1_INTEGER_TYPE:
			if (isAppend != 0) {
				// Append elements from source vector to the end of current one
				for (i = 0; i < sourceVector->size; i++) {
					((int32_t*)pCMe->data)[i + pCMe->size] = ((int32_t*)sourceVector->data)[i];
				}
			} else {
				// Insert elements from source vector to the beginning of current one
				for (i = pCMe->size; i > 0; i--) {
					((int32_t*)pCMe->data)[i - 1 + sourceVector->size] = ((int32_t*)pCMe->data)[i-1];
				}
				for (i = 0; i < sourceVector->size; i++) {
					((int32_t*)pCMe->data)[i] = ((int32_t*)sourceVector->data)[i];
				}
			}
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			if (isAppend != 0) {
				// Append elements from source vector to the end of current one
				for (i = 0; i < sourceVector->size; i++) {
					((double_t*)pCMe->data)[i + pCMe->size] = ((double_t*)sourceVector->data)[i];
				}
			} else {
				// Insert elements from source vector to the beginning of current one
				for (i = pCMe->size; i > 0; i--) {
					((double_t*)pCMe->data)[i - 1 + sourceVector->size] = ((double_t*)pCMe->data)[i-1];
				}
				for (i = 0; i < sourceVector->size; i++) {
					((double_t*)pCMe->data)[i] = ((double_t*)sourceVector->data)[i];
				}
			}
			break;
		case ECO_SET_1_POINTER_TYPE:
			// TODO implement
			break;
		case ECO_SET_1_OBJECT_TYPE:
			// TODO implement
			break;
    }
	pCMe->size += sourceVector->size;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Mean
 * </сводка>
 *
 * <описание>
 *   Функция возвращает среднее арифметическое значение по всем элементам вектора.
     Доступно только для типов int и double.
 * </описание>
 *
 */
double_t CEcoVector1_Mean(/* in */ struct IEcoVector1* me) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
	uint32_t i = 0;
	double_t mean = 0;
	double_t acc = 0;

    /* Проверка указателей и типов*/
    if (me == 0 || !(pCMe->type == ECO_SET_1_INTEGER_TYPE || pCMe->type == ECO_SET_1_DOUBLE_TYPE)) {
        return 0;
    }

	switch (pCMe->type) {
		case ECO_SET_1_INTEGER_TYPE:
			for (i = 0; i < pCMe->size; i++) {
				acc += ((int32_t*)pCMe->data)[i];
			}
			mean = acc / pCMe->size;
			break;
		case ECO_SET_1_DOUBLE_TYPE:
			for (i = 0; i < pCMe->size; i++) {
				acc += ((double_t*)pCMe->data)[i];
			}
			mean = acc / pCMe->size;
			break;
	}

    return mean;
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
int16_t initCEcoVector1(/*in*/ struct IEcoVector1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoVector1* pCMe = (CEcoVector1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

	/* Получение интерфейс для работы со строкой */
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**)&pCMe->m_pIString);
    if (result != 0 || pCMe->m_pIString == 0) {
        return result;
    }

    return result;
}

/* Create Virtual Table */
IEcoVector1VTbl g_xAB5664AF25FA4748A660573D673E68F1VTbl = {
    CEcoVector1_QueryInterface,
    CEcoVector1_AddRef,
    CEcoVector1_Release,
	CEcoVector1_InitByType,
	CEcoVector1_InitByTypeAndComparator,
	CEcoVector1_Get_Type,
	CEcoVector1_Get_Comparator,
    CEcoVector1_Size,
    CEcoVector1_IsEmpty,
    CEcoVector1_At,
	CEcoVector1_Set,
    CEcoVector1_IndexOf,
	CEcoVector1_FromArray,
	CEcoVector1_PrintVector,
    CEcoVector1_Insert,
	CEcoVector1_Push,
    CEcoVector1_InsertAt,
    CEcoVector1_RemoveAt,
    CEcoVector1_Clear,
    CEcoVector1_Reverse,
    CEcoVector1_Reshape,
    CEcoVector1_DeepCopy,
    CEcoVector1_Map,
    CEcoVector1_ReplaceValue,
    CEcoVector1_AddValue,
    CEcoVector1_SubValue,
    CEcoVector1_MulValue,
    CEcoVector1_DivValue,
    CEcoVector1_ModValue,
    CEcoVector1_AddVector,
    CEcoVector1_SubVector,
    CEcoVector1_MulVector,
    CEcoVector1_Join,
    CEcoVector1_Mean
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
int16_t createCEcoVector1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoVector1** ppIEcoVector1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoVector1* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoVector1 == 0 || pIUnkSystem == 0) {
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
    pCMe = (CEcoVector1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoVector1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoVector1 */
    pCMe->m_pVTblIEcoVector1 = &g_xAB5664AF25FA4748A660573D673E68F1VTbl;

	/* Создание таблицы вспомогательных функций интерфейса IEcoVector1 */
    pCMe->AllocateData = CEcoVector1_AllocateData;
	pCMe->ReallocateData = CEcoVector1_ReallocateData;
    pCMe->FreeData = CEcoVector1_FreeData;

    /* Инициализация данных */
	pCMe->m_pIString = 0;
    pCMe->m_Name = 0;
	pCMe->type = -1;
	pCMe->size = 0;
	pCMe->m_pIComparator = 0;
	pCMe->m_pIBus = pIBus;

    /* Возврат указателя на интерфейс */
    *ppIEcoVector1 = (IEcoVector1*)pCMe;

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
void deleteCEcoVector1(/* in */ IEcoVector1* pIEcoVector1) {
    CEcoVector1* pCMe = (CEcoVector1*)pIEcoVector1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoVector1 != 0 ) {
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
