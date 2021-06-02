/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoVector1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoVector1
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

#ifndef __ID_ECO_VECTOR_1_H__
#define __ID_ECO_VECTOR_1_H__

#include "IEcoBase1.h"
#include "IEcoVector1.h"

/* EcoVector1 CID = {2A3866FF-01C7-4D03-819C-FD138812B4A1} */
#ifndef __CID_EcoVector1
static const UGUID CID_EcoVector1 =  {0x01, 0x10, 0x2A, 0x38, 0x66, 0xFF, 0x01, 0xC7, 0x4D, 0x03, 0x81, 0x9C, 0xFD, 0x13, 0x88, 0x12, 0xB4, 0xA1};
#endif /* __CID_EcoVector1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_2A3866FF01C74D03819CFD138812B4A1;
#endif

#endif /* __ID_ECO_VECTOR_1_H__ */
