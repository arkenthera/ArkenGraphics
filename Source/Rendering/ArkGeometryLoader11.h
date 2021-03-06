//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//ArkGeometryLoader11.h
//--------------------------------------------------------------------------------
#ifndef __ArkGeometryLoader11_h__
#define __ArkGeometryLoader11_h__
//--------------------------------------------------------------------------------
#include "ArkGeometry11.h"
#include "ArkNodedGeometryExecutor11.h"
#include "ArkGeometryNode11.h"
//#include "SkinnedActor.h"
#include <string>
#include "Actor.h"
#include <fbxsdk.h>
//--------------------------------------------------------------------------------
namespace Arkeng
{
	class ArkGeometryLoader11
	{
	public:
		//static GeometryDX11* loadPlyFile( std::wstring filename );
		//static GeometryDX11* loadMS3DFile( std::wstring filename );		
		static GeometryPtr loadMS3DFile2( std::wstring filename );		
		//static GeometryPtr loadMS3DFileWithAnimationAndWeights( std::wstring filename, SkinnedActor* pActor = 0 );
		//static GeometryPtr loadMS3DFileWithAnimation( std::wstring filename, SkinnedActor* pActor = 0 );	
		
		
		//static void removeWhiteSpace( std::wstring& s );
		//static std::wstring getElementName( int usage, int index );

		static GeometryPtr loadStanfordPlyFile( std::wstring filename, bool withAdjacency = false );


		GeometryPtr LoadFbxFile( std::wstring filename );
		std::vector<Actor*> LoadFbxRecursively( std::wstring filename );
	public:
		ArkGeometryLoader11();
	private:
		struct PlyElementPropertyDeclaration
		{
			std::string name;
			bool isList;
			std::string type;
			std::string listLengthType;
		};

		struct PlyElementDesc
		{
			std::string name;
			int elementCount;
			std::vector< PlyElementPropertyDeclaration > dataFormat;
			std::vector< void** > data;
		};

		template<typename T>
		struct PlyDataArray
		{
			unsigned int length;
			T* data;
		};

		static int FindAdjacentIndex( int edgeStart, int edgeEnd, int triV, int* pRaw, int rawLen);
		static PlyElementDesc ParsePLYElementHeader(std::string headerLine, std::ifstream& input);
		static PlyElementPropertyDeclaration ParsePLYElementProperty(std::string desc);
		static PlyElementPropertyDeclaration ParsePLYElementPropertyList(std::string desc);
		static std::vector<void**> ReadPLYElementData(std::ifstream& input, const PlyElementDesc& desc);
		static void** ParsePLYElementData(std::string text, const std::vector<PlyElementPropertyDeclaration>& desc);
		template<typename T> static T* ExtractDataPtr(std::string input);
		template<typename T> static T ExtractDataVal(std::string input);
		template<typename T> static PlyDataArray<T>* ExtractDataPtrArray(int length, std::vector<std::string>::iterator iterator);
		static int FindPlyElementIndex(std::vector<PlyElementDesc> elems, std::string name);
		static int FindPlyElementPropertyIndex(std::vector<PlyElementPropertyDeclaration> elems, std::string name);
	};
};
#endif // GeometryLoaderDX11_h


