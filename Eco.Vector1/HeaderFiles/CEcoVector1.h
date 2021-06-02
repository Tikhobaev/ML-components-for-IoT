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
 *   Данный заголовок описывает реализацию компонента CEcoVector1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_VECTOR_1_H__
#define __C_ECO_VECTOR_1_H__

#include "IEcoVector1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoComparator1.h"
#include "IEcoInterfaceBus1.h"


typedef struct CEcoVector1 {

    /* Таблица функций интерфейса IEcoVector1 */
    IEcoVector1VTbl* m_pVTblIEcoVector1;


	/* Вспомогательные функции */
    void* (*AllocateData)(/* in */ struct CEcoVector1* pCMe, int16_t type, void* data, int32_t size);
	void* (*ReallocateData)(/* in */ struct CEcoVector1* pCMe, int16_t type, void* data, int32_t size);
    int16_t (*FreeData)(/* in */ struct CEcoVector1* pCMe, int16_t type, void* data);

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

	/* Интерфейс для работы со строкой */
    IEcoString1* m_pIString;

	/* Интерфейсная шина */
    IEcoInterfaceBus1* m_pIBus;


    /* Данные экземпляра */
    char_t* m_Name;
	IEcoComparator1* m_pIComparator;
	int16_t type;
	uint32_t size;
	void* data;

} CEcoVector1, *CEcoVector1Ptr;

/* Инициализация экземпляра */
int16_t initCEcoVector1(/*in*/ struct IEcoVector1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t createCEcoVector1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoVector1** ppIEcoVector1);
/* Удаление */
void deleteCEcoVector1(/* in */ IEcoVector1* pIEcoVector1);

#endif /* __C_ECO_VECTOR_1_H__ */
