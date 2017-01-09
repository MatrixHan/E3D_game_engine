#pragma once

#include "ECommon.h"
#include "EOgreMeshInfo.h"
#include "ECore.h"
#include <fstream>

namespace E3D
{
	EString ReadString(std::ifstream &in, EInt size = -1);

	EUShort ReadChunk(std::ifstream &in);

	EBool ReadBool(std::ifstream &in);

	EUInt ReadInt(std::ifstream &in);

	EUShort ReadShort(std::ifstream &in);

	template<typename T>
	std::vector<T> ReadArray(std::ifstream &in, EInt size)
	{
		std::vector<T> v(size, 0);
		in.read((char*)(&v[0]), sizeof(T)*size);
		return v;
	}

	EObject4D* LoadOgreMesh(const EString &meshName, const EVector4D &worldPos = EVector4D::ZERO,
		const EVector4D &scale = EVector4D(1, 1, 1));

}