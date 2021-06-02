/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoVector1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoVector1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2021 Ilya Tikhobaev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_VECTOR_1_H__
#define __I_ECO_VECTOR_1_H__

#include "IEcoBase1.h"
#include "IEcoComparator1.h"


/*
     Тип Данных: char_t*;
     Интерфейс сравнения по-умолчанию: IEcoComparator1String,
     Производит копирование строки при вставке и очистку при удалении
 */
#define ECO_SET_1_STRING_TYPE 0

 /*
     Тип Данных: int32_t;
     Интерфейс сравнения по-умолчанию: IEcoComparator1Int,
     Производит выделение памяти под число и копирование при вставке, а также очистку памяти при удалении
 */
#define ECO_SET_1_INTEGER_TYPE 1

 /*
     Тип Данных: double_t;
     Интерфейс сравнения по-умолчанию: IEcoComparator1Double;
     Производит выделение памяти под число и копирование при вставке, а также очистку памяти при удалении
 */
#define ECO_SET_1_DOUBLE_TYPE 2  

 /*
     Тип Данных: void*;
     Интерфейс сравнения по-умолчанию: IEcoComparator1Pointer;
     При вставке не производится никакого копирования, при удалении также не производится очистка памяти (вставка и удаление "AsIs")
 */
#define ECO_SET_1_POINTER_TYPE 3

 /*
     Тип Данных: интерфейсный тип (IEcoUnknown*);
     Интерфейс сравнения по-умолчанию: IEcoComparator1Pointer;
     При вставке увеличивает число ссылок на объект (функция AddRef), при удалении уменьшает число ссылок (фукция Release)
 */
#define ECO_SET_1_OBJECT_TYPE 4


/* IEcoVector1 IID = {AB5664AF-25FA-4748-A660-573D673E68F1} */
#ifndef __IID_IEcoVector1
static const UGUID IID_IEcoVector1 = {0x01, 0x10, 0xAB, 0x56, 0x64, 0xAF, 0x25, 0xFA, 0x47, 0x48, 0xA6, 0x60, 0x57, 0x3D, 0x67, 0x3E, 0x68, 0xF1};
#endif /* __IID_IEcoVector1 */

typedef struct IEcoVector1VTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoVector1* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoVector1* me);
    uint32_t (*Release)(/* in */ struct IEcoVector1* me);

    /* IEcoVector */
	int16_t (*InitByType)(/* in */ struct IEcoVector1* me, /* in */ uchar_t type);
    int16_t (*InitByTypeAndComparator)(
		/* in */ struct IEcoVector1* me, /* in */ uchar_t type, /* in */ IEcoComparator1* pIComparator
	);
    int16_t (*Get_Type)(/* in */ struct IEcoVector1* me);
    IEcoComparator1* (*Get_Comparator)(/* in */ struct IEcoVector1* me);

    uint32_t (*Size)(/* in */ struct IEcoVector1* me);
    bool_t (*IsEmpty)(/* in */ struct IEcoVector1* me);

    void* (*At)(/* in */ struct IEcoVector1* me, /* in */ uint32_t index);
	int16_t (*Set)(/* in */ struct IEcoVector1* me, /* in */ uint32_t index, /* in */ void* value);
    int32_t (*IndexOf)(/* in */ struct IEcoVector1* me, /* in */ void* value);

	int16_t (*FromArray)(/* in */ struct IEcoVector1* me, /* in */ void* sourceArray, int32_t size);
	void (*PrintVector)(/* in */ struct IEcoVector1* me); // For debug purposes

    int16_t (*Insert)(/* in */ struct IEcoVector1* me, /* in */ void* value);
	int16_t (*Push)(/* in */ struct IEcoVector1* me, /* in */ void* value);
    int16_t (*InsertAt)(/* in */ struct IEcoVector1* me, /* in */ uint32_t index, /* in */ void* value);

    int16_t (*RemoveAt)(/* in */ struct IEcoVector1* me, /* in */ uint32_t index);

    int16_t (*Clear)(/* in */ struct IEcoVector1* me);
    int16_t (*Reverse)(/* in */ struct IEcoVector1* me);
    int16_t (*Reshape)(/* in */ struct IEcoVector1* me, /* in */ uint32_t dim);
    struct IEcoVector1* (*DeepCopy)(/* in */ struct IEcoVector1* me);

    int16_t (*Map)(/* in */ struct IEcoVector1*me, /* in */ void (*func)(void*));
    int16_t (*ReplaceValue)(/* in */ struct IEcoVector1* me, /* in */ void* oldValue, void* newValue);

    int16_t (*AddValue)(/* in */ struct IEcoVector1* me, /* in */ void* value);
    int16_t (*SubValue)(/* in */ struct IEcoVector1* me, /* in */ void* value);
    int16_t (*MulValue)(/* in */ struct IEcoVector1* me, /* in */ void* value);
    int16_t (*DivValue)(/* in */ struct IEcoVector1* me, /* in */ void* value);
    int16_t (*ModValue)(/* in */ struct IEcoVector1* me, /* in */ void* value);

    int16_t (*AddVector)(/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector);
    int16_t (*SubVector)(/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector);
    int16_t (*MulVector)(/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector);
    int16_t (*Join)(
		/* in */ struct IEcoVector1* me, /* in */ struct IEcoVector1* vector, /* in */ int8_t isAppend
	);

    double_t (*Mean)(/* in */ struct IEcoVector1* me);

} IEcoVector1VTbl, *IEcoVector1VTblPtr;

interface IEcoVector1 {
    struct IEcoVector1VTbl *pVTbl;
} IEcoVector1;


/* IEcoVector1Iterator IID = {24503B2D-8B59-486B-9E75-624BE1A35B2D} */
#ifndef __IID_IEcoVector1Iterator
static const UGUID IID_IEcoVector1Iterator = {0x01, 0x10, 0x24, 0x50, 0x3B, 0x2D, 0x8B, 0x59, 0x48, 0x6B, 0x9E, 0x75, 0x62, 0x4B, 0xE1, 0xA3, 0x5B, 0x2D};
#endif /* __IID_IEcoVector1Iterator */

typedef struct IEcoVector1Iterator {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoVector1Iterator* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoVector1Iterator* me);
    uint32_t (*Release)(/* in */ struct IEcoVector1Iterator* me);

    /* IEcoVector1Iterator */
    IEcoVector1* (*Get_OwnerSet)(/* in */ struct IEcoVector1Iterator* me);
    void* (*Get_Value)(/* in */ struct IEcoVector1Iterator* me);
    bool_t (*HasNext)(/* in */ struct IEcoVector1Iterator* me);
    bool_t (*HasPrev)(/* in */ struct IEcoVector1Iterator* me);
    void* (*GoToNext)(/* in */ struct IEcoVector1Iterator* me);
    void* (*GoToPrev)(/* in */ struct IEcoVector1Iterator* me);

} IEcoVector1Iterator, *IEcoVector1IteratorPtr;


#endif /* __I_ECO_VECTOR_1_H__ */
