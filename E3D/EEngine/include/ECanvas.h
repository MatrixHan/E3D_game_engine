#pragma once

#include "EGraphics.h"

namespace E3D
{
	class ECanvas
	{
	public:
		virtual	~ECanvas() {}

		virtual void onPaint()=0;

		virtual void update()=0;

	private:

	};

}