//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//Pch.h
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
#ifndef __Pch_h__
#define __Pch_h__
//--------------------------------------------------------------------------------

//Standart C++ Libraries
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <vector>
#include <exception>
//

//Standard C Library includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <assert.h>
//

//Direct3D Includes
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <wrl.h>


#define COM_Release( x ) {if(x){(x)->Release();(x)=NULL;}}
#define COM_Delete( x ) {if(x){delete (x);(x)=NULL;}}


//--------------------------------------------------------------------------------
#endif //__Pch_h__



