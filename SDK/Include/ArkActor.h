//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//ArkActor.h
//--------------------------------------------------------------------------------
#ifndef __ArkActor_h__
#define __ArkActor_h___
//--------------------------------------------------------------------------------
#include "ArkBox.h"
//--------------------------------------------------------------------------------
namespace Arkeng
{
	class ArkActor
	{
	public:
		ArkActor();
		~ArkActor();

		ArkBox* BoundingBox;
	};
}
//--------------------------------------------------------------------------------
#endif
