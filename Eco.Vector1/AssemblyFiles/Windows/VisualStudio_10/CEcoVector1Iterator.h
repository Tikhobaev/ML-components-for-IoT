/*
 * <��������� ��������>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </��������� ��������>
 *
 * <������>
 *   CEcoVector1Iterator
 * </������>
 *
 * <��������>
 *   ������ ��������� ��������� ���������� ���������� CEcoVector1Iterator
 * </��������>
 *
 * <�����>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </�����>
 *
 */

#ifndef __C_ECOVECTOR1ITERATOR_H__
#define __C_ECOVECTOR1ITERATOR_H__

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoVector1.h"
#include "IdEcoMemoryManager1.h"


typedef struct CEcoVector1Iterator {

    /* ������� ������� ���������� IEcoVector1Iterator */
    IEcoVector1IteratorVTbl* m_VtblIEcoVector1Iterator;

    /* ������� ������ */
    uint32_t m_cRef;

    /* ��������� ��� ������ � ������� */
    IEcoMemoryAllocator1* m_pIMem;

    /* ��������� ��������� */
    IEcoSystem1* m_pISys;

    /* ������ ���������� */
    IEcoVector1* m_pIOwner;

} CEcoVector1Iterator, *CEcoVector1IteratorPtr;

/* ������������� ���������� */
int16_t initCEcoVector1Iterator(/*in*/ struct ICEcoVector1Iterator* me, /* in */ IEcoUnknown *pIUnkSystem);
/* �������� ���������� */
int16_t createCEcoVector1Iterator(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* in */ IEcoVector1* pIOwner, /* out */ IEcoVector1Iterator** ppIEcoVector1Iterator);
/* �������� */
void deleteCEcoVector1Iterator(/* in */ IEcoVector1Iterator* pIEcoVector1Iterator);

#endif /* __C_ECOVECTOR1ITERATOR_H__ */