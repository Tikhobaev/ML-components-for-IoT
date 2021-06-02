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
 *   Данный заголовок описывает реализацию компонента CEcoLinearRegression1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLINEARREGRESSION1_H__
#define __C_ECOLINEARREGRESSION1_H__

#include "IEcoLinearRegression1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLinearRegression1 {

    /* Таблица функций интерфейса IEcoLinearRegression1 */
    IEcoLinearRegression1VTbl* m_VTblIEcoLinearRegression1;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;
	double_t* weights;
	uint32_t size_x;
	uint32_t size_xi;
} CEcoLinearRegression1, *CEcoLinearRegression1Ptr;

/* Инициализация экземпляра */
int16_t initCEcoLinearRegression1(/*in*/ struct IEcoLinearRegression1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t createCEcoLinearRegression1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLinearRegression1** ppIEcoLinearRegression1);
/* Удаление */
void deleteCEcoLinearRegression1(/* in */ IEcoLinearRegression1* pIEcoLinearRegression1);

#endif /* __C_ECOLINEARREGRESSION1_H__ */
