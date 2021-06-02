/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoMatrix1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoMatrix1
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

#ifndef __ID_ECO_MATRIX_1_H__
#define __ID_ECO_MATRIX_1_H__

#include "IEcoBase1.h"
#include "IEcoMatrix1.h"

/* EcoMatrix1 CID = {9A659401-C933-4EF6-970F-7F5FE68577AA} */
#ifndef __CID_EcoMatrix1
static const UGUID CID_EcoMatrix1 = {0x01, 0x10, 0x9A, 0x65, 0x94, 0x01, 0xC9, 0x33, 0x4E, 0xF6, 0x97, 0x0F, 0x7F, 0x5F, 0xE6, 0x85, 0x77, 0xAA};
#endif /* __CID_EcoMatrix1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_9A659401C9334EF6970F7F5FE68577AA;
#endif

#endif /* __ID_ECO_MATRIX_1_H__ */
