/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoVector1Iterator
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoVector1Iterator
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOVECTOR1ITERATOR_H__
#define __C_ECOVECTOR1ITERATOR_H__

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoVector1.h"
#include "IdEcoMemoryManager1.h"


typedef struct CEcoVector1Iterator {

    /* Таблица функций интерфейса IEcoVector1Iterator */
    IEcoVector1IteratorVTbl* m_VtblIEcoVector1Iterator;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    IEcoVector1* m_pIOwner;

} CEcoVector1Iterator, *CEcoVector1IteratorPtr;

/* Инициализация экземпляра */
int16_t initCEcoVector1Iterator(/*in*/ struct ICEcoVector1Iterator* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t createCEcoVector1Iterator(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* in */ IEcoVector1* pIOwner, /* out */ IEcoVector1Iterator** ppIEcoVector1Iterator);
/* Удаление */
void deleteCEcoVector1Iterator(/* in */ IEcoVector1Iterator* pIEcoVector1Iterator);

#endif /* __C_ECOVECTOR1ITERATOR_H__ */