/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLinearRegression1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLinearRegression1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOLINEARREGRESSION1_H__
#define __I_ECOLINEARREGRESSION1_H__

#include "IEcoBase1.h"
#include "IdEcoVector1.h"
#include "IdEcoMatrix1.h"

/* IEcoLinearRegression1 IID = {368A2DEF-D0F8-4978-8819-F10AA45CC937} */
#ifndef __IID_IEcoLinearRegression1
static const UGUID IID_IEcoLinearRegression1 = {0x01, 0x10, 0x36, 0x8A, 0x2D, 0xEF, 0xD0, 0xF8, 0x49, 0x78, 0x88, 0x19, 0xF1, 0x0A, 0xA4, 0x5C, 0xC9, 0x37};
#endif /* __IID_IEcoLinearRegression1 */

typedef struct IEcoLinearRegression1VTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoLinearRegression1* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoLinearRegression1* me);
    uint32_t (*Release)(/* in */ struct IEcoLinearRegression1* me);

    /* IEcoLinearRegression1 */
	double_t (*MSE)(/* in */ struct IEcoLinearRegression1* me, IEcoVector1* predictions, IEcoVector1* y);
    int16_t (*Fit)(/* in */ struct IEcoLinearRegression1* me, IEcoMatrix1* X_origin, IEcoVector1* y,
				   uint32_t patience, uint32_t max_epochs, double_t eps, double_t lr
	);
	IEcoVector1* (*Predict)(/* in */ struct IEcoLinearRegression1* me, IEcoMatrix1* X_origin, IEcoVector1* y);
	

} IEcoLinearRegression1VTbl, *IEcoLinearRegression1VTblPtr;

interface IEcoLinearRegression1 {
    struct IEcoLinearRegression1VTbl *pVTbl;
} IEcoLinearRegression1;

#endif /* __I_ECOLINEARREGRESSION1_H__ */
