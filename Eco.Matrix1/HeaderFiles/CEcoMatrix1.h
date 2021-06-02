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
 *   Данный заголовок описывает реализацию компонента CEcoMatrix1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOMATRIX1_H__
#define __C_ECOMATRIX1_H__

#include "IEcoMatrix1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoInterfaceBus1.h"


typedef struct CEcoMatrix1 {

    /* Таблица функций интерфейса IEcoMatrix1 */
    IEcoMatrix1VTbl* m_pVTblIEcoMatrix1;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

	/* Интерфейс для работы с вектором */
    IEcoVector1* m_pIVector;

	/* Интерфейсная шина */
    IEcoInterfaceBus1* m_pIBus;

    /* Данные экземпляра */
    char_t* m_Name;
	IEcoVector1** vectors;
	uint32_t sizeX;  // Количество векторов в матрице (количество строк)
	uint32_t sizeY;  // Размер вектора в матрице (количество столбцов)

} CEcoMatrix1, *CEcoMatrix1Ptr;

/* Инициализация экземпляра */
int16_t initCEcoMatrix1(/*in*/ struct IEcoMatrix1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t createCEcoMatrix1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoMatrix1** ppIEcoMatrix1);
/* Удаление */
void deleteCEcoMatrix1(/* in */ IEcoMatrix1* pIEcoMatrix1);

#endif /* __C_ECOMATRIX1_H__ */
