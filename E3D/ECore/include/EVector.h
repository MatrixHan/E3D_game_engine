
#pragma once

#include "ECommon.h"
#include "EMath.h"
#include "EUtil.h"

namespace E3D
{
	// 2DÏòÁ¿--VECTOR2D_TYP
	struct EVector2D
	{
		static EVector2D ZERO;
		static EVector2D UNIT_X;
		static EVector2D UNIT_Y;

		EFloat	x;
		EFloat	y;

		EVector2D() : x(0), y(0){}
		EVector2D(EFloat xf, EFloat yf) : x(xf), y(yf){}
		EVector2D(const EVector2D& v) : x(v.x), y(v.y){}

		// ½«ÏòÁ¿¹æ·¶»¯
		inline EFloat normalize()
		{
			EFloat len = length();
			if (len > EPSILON_E6)
			{
				EFloat invLength = 1.0f / len;
				x *= invLength;
				y *= invLength;
			}

			return len;
		}

		inline EFloat dotProduct(const EVector2D&right) const
		{
			return x * right.x + y * right.y;
		}

		// ·µ»ØÁ½¸öÏòÁ¿Ö®¼äµÄ¼Ð½Ç, ·µ»Ø·½Ê½Îª»¡¶È
		inline EFloat angleBetween(const EVector2D&right) const
		{
			EFloat lenProduct = length() * right.length();

			// ³ýÁã¼ì²é
			if (lenProduct < EPSILON_E6)
				lenProduct = EPSILON_E6;

			EFloat f = dotProduct(right) / lenProduct;
			f = Clamp(f, -1.0f, 1.0f);

			return acos(f);
		}

		inline bool isZero() const 
		{
			return length() < EPSILON_E6;
		}

		// ·µ»ØÏòÁ¿³¤¶È
		inline EFloat length() const
		{
			return sqrt(x * x + y * y);
		}

		// ·µ»Ø³¤¶ÈµÄÆ½·½
		inline EFloat squaredLength() const
		{
			return x * x + y * y;
		}

		inline EVector2D operator*(float right) const
		{
			return EVector2D(x * right, y * right);
		}

		// ÏòÁ¿µã»ý
		inline EVector2D operator*(const EVector2D& right) const
		{
			return EVector2D(x * right.x, y * right.y);
		}

		inline EVector2D operator+(const EVector2D& right) const
		{
			return EVector2D(x + right.x, y +right.y);
		}

		inline EVector2D operator-(const EVector2D& right) const
		{
			return EVector2D(x - right.x, y -right.y);
		}

		inline EVector2D operator-()
		{
			x = -x;
			y = -y;
			return *this;
		}

		inline EVector2D operator+()
		{
			x = +x;
			y = +y;
			return *this;
		}

		inline bool operator==(const EVector2D& right) const
		{
			return EqualFloat(x, right.x) && EqualFloat(y, right.y);
		}

		inline EVector2D operator=(const EVector2D&right)
		{
			x = right.x;
			y = right.y;
			return *this;
		}
	};

	// 3DÏòÁ¿--VECTOR3D_TYP
	struct EVector3D
	{
		static EVector3D ZERO;
		static EVector3D UNIT_X;
		static EVector3D UNIT_Y;
		static EVector3D UNIT_Z;

		EFloat	x;
		EFloat	y;
		EFloat	z;

		EVector3D():x(0), y(0), z(0){}
		EVector3D(EFloat xf, EFloat yf, EFloat zf) : x(xf), y(yf), z(zf){}
		EVector3D(const EVector3D& v) : x(v.x), y(v.y), z(v.z){}

		inline EFloat dotProduct(const EVector3D&right) const
		{
			return x * right.x + y * right.y + z * right.z;
		}

		// ÏòÁ¿²æ»ý
		inline EVector3D crossProduct(const EVector3D&right) const
		{
			return EVector3D(y * right.z - z * right.y,
							 z * right.x - x * right.z,
							 x * right.y - y * right.x);
		}

		// ½«ÏòÁ¿¹æ·¶»¯
		inline EFloat normalize()
		{
			EFloat len = length();
			if (len > EPSILON_E6)
			{
				EFloat invLength = 1.0f / len;
				x *= invLength;
				y *= invLength;
				z *= invLength;
			}

			return len;
		}

		inline bool isZero() const 
		{
			return length() < EPSILON_E6;
		}

		// ·µ»ØÁ½¸öÏòÁ¿Ö®¼äµÄ¼Ð½Ç, ·µ»Ø·½Ê½Îª»¡¶È
		inline EFloat angleBetween(const EVector3D&right) const
		{
			EFloat lenProduct = length() * right.length();

			// ³ýÁã¼ì²é
			if (lenProduct < EPSILON_E6)
				lenProduct = EPSILON_E6;

			EFloat f = dotProduct(right) / lenProduct;
			return acos(f);
		}

		inline EFloat length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		inline EFloat squaredLength() const
		{
			return x * x + y * y + z * z;
		}

		inline EVector3D operator*(float right) const
		{
			return EVector3D(x * right, y * right, z * right);
		}

		inline EVector3D operator*(const EVector3D& right) const
		{
			return EVector3D(x * right.x, y * right.y, z * right.z);
		}

		inline EVector3D operator+(const EVector3D& right) const
		{
			return EVector3D(x + right.x, y +right.y, z + right.z);
		}

		inline EVector3D operator-(const EVector3D& right) const
		{
			return EVector3D(x - right.x, y -right.y, z - right.z);
		}

		inline EVector3D operator-()
		{
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		inline EVector3D operator+()
		{
			x = +x;
			y = +y;
			z = +z;
			return *this;
		}

		inline bool operator==(const EVector3D& right) const
		{
			return EqualFloat(x, right.x) && EqualFloat(y, right.y) && EqualFloat(z, right.z);
		}

		inline EVector3D operator=(const EVector3D&right)
		{
			x = right.x;
			y = right.y;
			z = right.z;

			return *this;
		}
	};

	// 4DÏòÁ¿--VECTOR4D_TYP
	struct EVector4D
	{
		static EVector4D ZERO;
		static EVector4D UNIT_X;
		static EVector4D UNIT_Y;
		static EVector4D UNIT_Z;

		EFloat	x;
		EFloat	y;
		EFloat	z;
		EFloat	w;

		EVector4D():x(0), y(0), z(0), w(1){}
		EVector4D(EFloat xf, EFloat yf, EFloat zf, EFloat wf = 1) : x(xf), y(yf), z(zf), w(wf){}
		EVector4D(const EVector4D& v) : x(v.x), y(v.y), z(v.z), w(v.w){}

		inline EFloat length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		inline EFloat squaredLength() const
		{
			return x * x + y * y + z * z;
		}

		// ½«ÏòÁ¿¹æ·¶»¯
		inline EFloat normalize()
		{
			EFloat len = length();
			if (len > EPSILON_E6)
			{
				EFloat invLength = 1.0f / len;
				x *= invLength;
				y *= invLength;
				z *= invLength;
				w = 1;
			}

			return len;
		}

		inline bool isZero() const 
		{
			return length() < EPSILON_E6;
		}

		// ·µ»ØÁ½¸öÏòÁ¿Ö®¼äµÄ¼Ð½Ç, ·µ»Ø·½Ê½Îª»¡¶È
		inline EFloat angleBetween(const EVector4D&right) const
		{
			EFloat lenProduct = length() * right.length();

			// ³ýÁã¼ì²é
			if (lenProduct < EPSILON_E6)
				lenProduct = EPSILON_E6;

			EFloat f = dotProduct(right) / lenProduct;
			f = Clamp(f, -1.0f, 1.0f);

			return acos(f);
		}

		inline EFloat dotProduct(const EVector4D&right) const
		{
			return x * right.x + y * right.y + z * right.z;
		}

		// ÏòÁ¿²æ»ý
		inline EVector4D crossProduct(const EVector4D&right) const
		{
			return EVector4D(y * right.z - z * right.y,
							 z * right.x - x * right.z,
							 x * right.y - y * right.x, 1);
		}

		inline EVector4D operator*(float right) const
		{
			return EVector4D(x * right, y * right, z * right, 1);
		}

		// ÏòÁ¿µã»ý
		inline EVector4D operator*(const EVector4D& right) const
		{
			return EVector4D(x * right.x, y * right.y, z * right.z, 1);
		}

		inline EVector4D operator+(const EVector4D& right) const
		{
			return EVector4D(x + right.x, y +right.y, z + right.z, 1);
		}

		inline EVector4D operator-() const
		{
			return EVector4D(-x, -y, -z, w);
		}

		inline EVector4D operator-(const EVector4D& right) const
		{
			return EVector4D(x - right.x, y -right.y, z - right.z, 1);
		}

		inline bool operator==(const EVector4D& right) const
		{
			return EqualFloat(x, right.x) && EqualFloat(y, right.y) && 
					EqualFloat(z, right.z) && EqualFloat(w, right.w);
		}

		inline EVector4D& operator=(const EVector4D&right)
		{
			x = right.x;
			y = right.y;
			z = right.z;
			w = right.w;

			return *this;
		}
	};
}
