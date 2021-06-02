/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoMatrix1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoMatrix1
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

#ifndef __I_ECO_MATRIX_1_H__
#define __I_ECO_MATRIX_1_H__

#include "IEcoBase1.h"
#include "IEcoVector1.h"
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


/* IEcoMatrix1 IID = {23F199B6-1FA0-41DC-8217-69E891FC30F6} */
#ifndef __IID_IEcoMatrix1
static const UGUID IID_IEcoMatrix1 = {0x01, 0x10, 0x23, 0xF1, 0x99, 0xB6, 0x1F, 0xA0, 0x41, 0xDC, 0x82, 0x17, 0x69, 0xE8, 0x91, 0xFC, 0x30, 0xF6};
#endif /* __IID_IEcoMatrix1 */

typedef struct IEcoMatrix1VTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoMatrix1* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoMatrix1* me);
    uint32_t (*Release)(/* in */ struct IEcoMatrix1* me);

    /* IEcoMatrix1 */
	int16_t (*InitBySize)(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t sizeX, /* in */ uint32_t sizeY);
	int16_t (*CreateVectorAtIndex)(
		/* in */ struct IEcoMatrix1* me, /* in */ void* sourceArray,
		/* in */ uint32_t size, /* in */ uint32_t index, /* in */ uchar_t type
	);
	int16_t (*SetVectorAtIndex)(
		/* in */ struct IEcoMatrix1* me, /* in */ IEcoVector1* sourceVector, uint32_t index
	);
	int16_t (*InsertVectorAtIndex)(
		/* in */ struct IEcoMatrix1* me, /* in */ IEcoVector1* sourceVector, uint32_t index
	);
	
	void (*PrintMatrix)(/* in */ struct IEcoMatrix1* me);

	int16_t (*Size)(
		/* in */ struct IEcoMatrix1* me,
		/* out */ uint32_t* sizeX,
		/* out */ uint32_t* sizeY
	);
    int16_t (*IsEmpty)(/* in */ struct IEcoMatrix1* me);

    void* (*At)(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t ix,  /* in */ uint32_t iy);
	int16_t (*Set)(
		/* in */ struct IEcoMatrix1* me, /* in */ uint32_t ix,  /* in */ uint32_t iy, void* value
	);
	int16_t (*IndexOf)(
		/* in */ struct IEcoMatrix1* me, /* in */ void* value,
		/* out */ uint32_t* ix, /* out */ uint32_t* iy
	);

    int16_t (*Clear)(/* in */ struct IEcoMatrix1* me);
    int16_t (*Transpose)(/* in */ struct IEcoMatrix1* me);
    int16_t (*Reshape)(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t dimX, /* in */ uint32_t dimY);
    struct IEcoMatrix1* (*DeepCopy)(/* in */ struct IEcoMatrix1* me);

    int16_t (*Map)(/* in */ struct IEcoMatrix1*me, /* in */ void (*func)(void*));
    int16_t (*ReplaceValue)(/* in */ struct IEcoMatrix1* me, /* in */ void* oldValue, void* newValue);

    int16_t (*AddValue)(/* in */ struct IEcoMatrix1* me, /* in */ void* value);
    int16_t (*SubValue)(/* in */ struct IEcoMatrix1* me, /* in */ void* value);
    int16_t (*MulValue)(/* in */ struct IEcoMatrix1* me, /* in */ void* value);
    int16_t (*DivValue)(/* in */ struct IEcoMatrix1* me, /* in */ void* value);
    int16_t (*ModValue)(/* in */ struct IEcoMatrix1* me, /* in */ void* value);

    int16_t (*AddMatrix)(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix);
    int16_t (*SubMatrix)(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix);
	int16_t (*MulMatrix)(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix);
    int16_t (*MulMatrixElementwise)(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix);

    int16_t (*Join)(/* in */ struct IEcoMatrix1* me, /* in */ struct IEcoMatrix1* matrix,
        /* in */ int8_t isAppend, /* in */ int8_t isAlongAxisX
	);
    double_t (*Mean)(/* in */ struct IEcoMatrix1* me);
    
	struct IEcoVector1* (*GetCol)(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t colIndex);
	struct IEcoVector1* (*RemoveCol)(/* in */ struct IEcoMatrix1* me, /* in */ uint32_t colIndex);

} IEcoMatrix1VTbl, *IEcoMatrix1VTblPtr;

interface IEcoMatrix1 {
    struct IEcoMatrix1VTbl *pVTbl;
} IEcoMatrix1;


#endif /* __I_ECO_MATRIX_1_H__ */
