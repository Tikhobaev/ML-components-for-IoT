/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoLinearRegression1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoLinearRegression1
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

#ifndef __ID_ECOLINEARREGRESSION1_H__
#define __ID_ECOLINEARREGRESSION1_H__

#include "IEcoBase1.h"
#include "IEcoLinearRegression1.h"

/* EcoLinearRegression1 CID = {FB377ED7-D319-4F84-8BC2-AF19B762B739} */
#ifndef __CID_EcoLinearRegression1
static const UGUID CID_EcoLinearRegression1 = {0x01, 0x10, 0xFB, 0x37, 0x7E, 0xD7, 0xD3, 0x19, 0x4F, 0x84, 0x8B, 0xC2, 0xAF, 0x19, 0xB7, 0x62, 0xB7, 0x39};
#endif /* __CID_EcoLinearRegression1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_FB377ED7D3194F848BC2AF19B762B739;
#endif

#endif /* __ID_ECOLINEARREGRESSION1_H__ */
