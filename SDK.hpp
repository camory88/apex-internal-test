#pragma once

#include <Windows.h>
#include <string_view>
#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include "setting.h"





#define dwbase (DWORD64)GetModuleHandleA(0)
#define SCREEN_W 1920
#define SCREEN_H 1080

// to-do: stop hardcoding screen vars

#define OFFSET_EntityLIST			0x1a1e3b8//good
#define OFFSET_LOCAL_ENT			0x1dcf5e8  //good
#define OFFSET_NAME_LIST            0xba2e9b0 //good

#define OFFSET_TEAM					0x448 //good
#define OFFSET_HEALTH				0x438 //good
#define OFFSET_SHIELD				0x170 //good
#define OFFSET_NAME					0x589 //good?

#define OFFSET_SIGN_NAME			0x580 //good?
#define OFFSET_ABS_VELOCITY         0x140 //good?
#define OFFSET_VISIBLE_TIME         0x1ad4 //CPlayer!lastVisibleTime?
#define OFFSET_ZOOMING      		0x1c51 //m_bZooming

#define OFFSET_THIRDPERSON_SV       0x36a8 //m_thirdPersonShoulderView
#define OFFSET_THIRDPERSON          0x01a02db0 + 0x6c //thirdperson_override + 0x6c

#define OFFSET_ITEM_ID				0x0448 //m_iTeamNum

#define OFFSET_LIFE_STATE			0x0798  //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE		0x2720 //m_bleedoutState, >0 = knocked

#define OFFSET_SKIN 				0x0ea8 

#define OFFSET_STUDIOHDR 0x1150
#define OFFSET_BONECLASS 0x0ef0 + 0x48
#define OFFSET_MODEL				0x1138////m_nForceBone + 0x48


#define OFFSET_ORIGIN				0x14c //m_vecAbsOrigin
#define OFFSET_BONES				0xF38 //m_bConstrainBetweenEndpoints
#define OFFSET_AIMPUNCH				0x2498 //m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS			0x1f40 //CPlayer!camera_origin
#define OFFSET_VIEWANGLES			0x2594 - 0x14 //m_ammoPoolCapacity - 0x14
#define OFFSET_BREATH_ANGLES		OFFSET_VIEWANGLES - 0x10
#define OFFSET_OBSERVER_MODE		0x34bc //m_iObserverMode
#define OFFSET_OBSERVING_TARGET		0x34c8 //m_hObserverTarget

#define OFFSET_MATRIX				0x11a210 
#define OFFSET_RENDER				0x75441d0 

#define OFFSET_WEAPON				0x1a6c //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED         0x1f28 //CWeaponX!m_flProjectileSpeed
#define OFFSET_BULLET_SCALE         0x1f30 //CWeaponX!m_flProjectileScale
#define OFFSET_ZOOM_FOV             0x1718 + 0x00b8 //m_playerData + m_curZoomFOV
#define OFFSET_AMMO                 0x16a4 //m_ammoInClip

#define OFFSET_ITEM_GLOW            0x02c0 //m_highlightFunctionBits

#define OFFSET_GLOW_T1              0x262 //16256 = enabled, 0 = disabled 
#define OFFSET_GLOW_T2              0x2dc //1193322764 = enabled, 0 = disabled 
#define OFFSET_GLOW_ENABLE          0x3c8 //7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS   0x3d0 //2 = enabled, 5 = disabled

#define GLOW_FADE 0x388
#define GLOW_DISTANCE 0x3B4
#define GLOW_CONTEXT 0x3C8
#define GLOW_LIFE_TIME 0x3A4
#define GLOW_VISIBLE_TYPE 0x3D0
#define GLOW_TYPE 0x2C4
#define GLOW_COLOR 0x1D0
#define GLOW_COLOR2 0x1D4 // GLOW_COLOR + 0x4
#define GLOW_COLOR3 0x1D8 // GLOW_COLOR + 0x8
#define MAX_SHIELD 0x174 //shieldhealthmax
#define ARMOR_TYPE 0x4604 //CPlayer!armorType
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

float oVisTime[100];

struct ClientClass {
	uint64_t pCreateFn;
	uint64_t pCreateEventFn;
	uint64_t pNetworkName;
	uint64_t pRecvTable;
	uint64_t pNext;
	uint32_t ClassID;
	uint32_t ClassSize;
};

typedef struct bone_t
{
	uint8_t pad1[0xCC];
	float x;
	uint8_t pad2[0xC];
	float y;
	uint8_t pad3[0xC];
	float z;
}bone_t;

#define DECL_ALIGN(x) __attribute__((aligned(x)))


#define ALIGN16 DECL_ALIGN(16)
#define VALVE_RAND_MAX 0x7fff
#define VectorExpand(v) (v).x, (v).y, (v).z

#define Assert( _exp ) ((void)0)

#define FastSqrt(x)			(sqrt)(x)

#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#define M_PHI		1.61803398874989484820 // golden ratio

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

class Vector
{
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	inline Vector& operator+=(const Vector& v);
	inline Vector& operator-=(const Vector& v);
	inline Vector& operator*=(const Vector& v);
	inline Vector& operator*=(float s);
	inline Vector& operator/=(const Vector& v);
	inline Vector& operator/=(float s);
	inline Vector& operator+=(float fl);
	inline Vector& operator-=(float fl);
	inline float	Length() const;
	inline float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance&&
			z > -tolerance && z < tolerance);
	}
	Vector	Normalize();
	void	NormalizeInPlace();
	inline float	DistTo(const Vector& vOther) const;
	inline float	DistToSqr(const Vector& vOther) const;
	float	Dot(const Vector& vOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	Vector& operator=(const Vector& vOther);
	Vector	operator-(void) const;
	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

//===============================================
inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
}
//===============================================
inline Vector::Vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
}
//===============================================
inline Vector::Vector(void) { Zero(); }
//===============================================
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline Vector& Vector::operator=(const Vector& vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& Vector::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float Vector::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool Vector::operator==(const Vector& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool Vector::operator!=(const Vector& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
inline void VectorCopy(const Vector& src, Vector& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
inline  Vector& Vector::operator+=(const Vector& v)
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
inline  Vector& Vector::operator-=(const Vector& v)
{
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
inline  Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;

	return *this;
}
//===============================================
inline  Vector& Vector::operator*=(const Vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}
//===============================================
inline Vector& Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;

	return *this;
}
//===============================================
inline Vector& Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;

	return *this;
}
//===============================================
inline  Vector& Vector::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;

	return *this;
}
//===============================================
inline  Vector& Vector::operator/=(const Vector& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}
//===============================================
inline float Vector::Length(void) const
{


	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	root = sqrt(sqsr);

	return root;
}
//===============================================
inline float Vector::Length2D(void) const
{
	float root = 0.0f;

	float sqst = x * x + y * y;

	root = sqrt(sqst);

	return root;
}
//===============================================
inline float Vector::Length2DSqr(void) const
{
	return (x * x + y * y);
}
//===============================================
inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
//===============================================
float Vector::DistTo(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}
float Vector::DistToSqr(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}
//===============================================
inline Vector Vector::Normalize()
{
	Vector vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
	{
		vector.x = vector.y = 0.0f; vector.z = 1.0f;
	}

	return vector;
}
//===============================================
inline void Vector::NormalizeInPlace()
{
	Vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;
}
//===============================================
inline float VectorNormalize(Vector& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		// FIXME:
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
inline float VectorNormalize(float* v)
{
	return VectorNormalize(*(reinterpret_cast<Vector*>(v)));
}
//===============================================
inline Vector Vector::operator+(const Vector& v) const
{
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline Vector Vector::operator-(const Vector& v) const
{
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline Vector Vector::operator*(float fl) const
{
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline Vector Vector::operator*(const Vector& v) const
{
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline Vector Vector::operator/(float fl) const
{
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline Vector Vector::operator/(const Vector& v) const
{
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return(a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float VectorLength(const Vector& v)
{

	return (float)FastSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//VECTOR SUBTRAC
inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{


	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//VECTORADD
inline void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{


	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* Vector::Base()
{
	return (float*)this;
}

inline float const* Vector::Base() const
{
	return (float const*)this;
}

inline void VectorMAInline(const float* start, float scale, const float* direction, float* dest)
{
	dest[0] = start[0] + direction[0] * scale;
	dest[1] = start[1] + direction[1] * scale;
	dest[2] = start[2] + direction[2] * scale;
}

inline void VectorMAInline(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	dest.x = start.x + direction.x * scale;
	dest.y = start.y + direction.y * scale;
	dest.z = start.z + direction.z * scale;
}

inline void VectorMA(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	VectorMAInline(start, scale, direction, dest);
}

inline void VectorMA(const float* start, float scale, const float* direction, float* dest)
{
	VectorMAInline(start, scale, direction, dest);
}


inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline bool IsFinite(float f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

//=========================================================
// 2D Vector2D
//=========================================================

class Vector2D
{
public:
	// Members
	float x, y;

	// Construction/destruction
	Vector2D(void);
	Vector2D(float X, float Y);
	Vector2D(const float* pFloat);

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// Initialization methods
	void Random(float minVal, float maxVal);

	// equality
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	// arithmetic operations
	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator*=(float s);
	Vector2D& operator/=(const Vector2D& v);
	Vector2D& operator/=(float s);

	// negate the Vector2D components
	void	Negate();

	// Get the Vector2D's magnitude.
	float	Length() const;

	// Get the Vector2D's magnitude squared.
	float	LengthSqr(void) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance);
	}

	float	Normalize();

	// Normalize in place and return the old length.
	float	NormalizeInPlace();

	// Compare length.
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// Get the distance from this Vector2D to the other one.
	float	DistTo(const Vector2D& vOther) const;

	// Get the distance from this Vector2D to the other one squared.
	float	DistToSqr(const Vector2D& vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector2D equation (because it's done per-component
	// rather than per-Vector2D).
	void	MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

	// Dot product.
	float	Dot(const Vector2D& vOther) const;

	// assignment
	Vector2D& operator=(const Vector2D& vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	Vector2D(const Vector2D& vOther);

	// arithmetic operations
	Vector2D	operator-(void) const;

	Vector2D	operator+(const Vector2D& v) const;
	Vector2D	operator-(const Vector2D& v) const;
	Vector2D	operator*(const Vector2D& v) const;
	Vector2D	operator/(const Vector2D& v) const;
	Vector2D	operator*(float fl) const;
	Vector2D	operator/(float fl) const;

	// Cross product between two vectors.
	Vector2D	Cross(const Vector2D& vOther) const;

	// Returns a Vector2D with the min or max in X, Y, and Z.
	Vector2D	Min(const Vector2D& vOther) const;
	Vector2D	Max(const Vector2D& vOther) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	Vector2D(const Vector2D& vOther);
#endif
};

//-----------------------------------------------------------------------------

const Vector2D vec2_origin(0, 0);
//const Vector2D vec2_invalid(3.40282347E+38F, 3.40282347E+38F);

//-----------------------------------------------------------------------------
// Vector2D related operations
//-----------------------------------------------------------------------------

// Vector2D clear
void Vector2DClear(Vector2D& a);

// Copy
void Vector2DCopy(const Vector2D& src, Vector2D& dst);

// Vector2D arithmetic
void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, float b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, float b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result);

// Store the min or max of each of x, y, and z into the result.
void Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result);

#define Vector2DExpand( v ) (v).x, (v).y

// Normalization
float Vector2DNormalize(Vector2D& v);

// Length
float Vector2DLength(const Vector2D& v);

// Dot Product
float DotProduct2D(const Vector2D& a, const Vector2D& b);

// Linearly interpolate between two vectors
void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest);


//-----------------------------------------------------------------------------
//
// Inlined Vector2D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(void)
{
#ifdef _DEBUG
	// Initialize to NAN to catch errors
	//x = y = float_NAN;
#endif
}

inline Vector2D::Vector2D(float X, float Y)
{
	x = X; y = Y;
	Assert(IsValid());
}

inline Vector2D::Vector2D(const float* pFloat)
{
	Assert(pFloat);
	x = pFloat[0]; y = pFloat[1];
	Assert(IsValid());
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void Vector2D::Init(float ix, float iy)
{
	x = ix; y = iy;
	Assert(IsValid());
}

inline void Vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}

inline void Vector2DClear(Vector2D& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector2D& Vector2D::operator=(const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline float& Vector2D::operator[](int i)
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

inline float Vector2D::operator[](int i) const
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* Vector2D::Base()
{
	return (float*)this;
}

inline float const* Vector2D::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

inline bool Vector2D::IsValid() const
{
	return IsFinite(x) && IsFinite(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector2D::operator==(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x == x) && (src.y == y);
}

inline bool Vector2D::operator!=(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void Vector2DCopy(const Vector2D& src, Vector2D& dst)
{
	Assert(src.IsValid());
	dst.x = src.x;
	dst.y = src.y;
}

inline void	Vector2D::CopyToArray(float* rgfl) const
{
	Assert(IsValid());
	Assert(rgfl);
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void Vector2D::Negate()
{
	Assert(IsValid());
	x = -x; y = -y;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x += v.x; y += v.y;
	return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x -= v.x; y -= v.y;
	return *this;
}

inline Vector2D& Vector2D::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator*=(const Vector2D& v)
{
	x *= v.x;
	y *= v.y;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/=(const Vector2D& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
	Assert(IsValid());
	return *this;
}

inline void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void Vector2DMultiply(const Vector2D& a, float b, Vector2D& c)
{
	Assert(a.IsValid() && IsFinite(b));
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


inline void Vector2DDivide(const Vector2D& a, float b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert(b != 0.0f);
	float oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert((b.x != 0.0f) && (b.y != 0.0f));
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result)
{
	Assert(start.IsValid() && IsFinite(s) && dir.IsValid());
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
inline void	Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline float DotProduct2D(const Vector2D& a, const Vector2D& b)
{
	Assert(a.IsValid() && b.IsValid());
	return(a.x * b.x + a.y * b.y);
}

// for backwards compatability
inline float Vector2D::Dot(const Vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float Vector2DLength(const Vector2D& v)
{
	Assert(v.IsValid());
	return (float)FastSqrt(v.x * v.x + v.y * v.y);
}

inline float Vector2D::LengthSqr(void) const
{
	Assert(IsValid());
	return (x * x + y * y);
}

inline float Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

inline bool Vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val * val;
}

inline bool Vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val * val;
}

inline float Vector2D::Length(void) const
{
	return Vector2DLength(*this);
}


inline void Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


inline void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------
inline float Vector2DNormalize(Vector2D& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
	}
	return l;
}


//-----------------------------------------------------------------------------
// Get the distance from this Vector2D to the other one
//-----------------------------------------------------------------------------
inline float Vector2D::DistTo(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.Length();
}

inline float Vector2D::DistToSqr(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.LengthSqr();
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D* pResult)
{
	Vector2D vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist)
	{
		*pResult = vecTarget;
	}
	else
	{
		vecDelta /= FastSqrt(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}



//-----------------------------------------------------------------------------
//
// Slow methods
//
//-----------------------------------------------------------------------------

#ifndef VECTOR_NO_SLOW_OPERATIONS
#endif
//-----------------------------------------------------------------------------
// Returns a Vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

inline Vector2D Vector2D::Min(const Vector2D& vOther) const
{
	return Vector2D(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y);
}

inline Vector2D Vector2D::Max(const Vector2D& vOther) const
{
	return Vector2D(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline Vector2D Vector2D::operator-(void) const
{
	return Vector2D(-x, -y);
}

inline Vector2D Vector2D::operator+(const Vector2D& v) const
{
	Vector2D res;
	Vector2DAdd(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator-(const Vector2D& v) const
{
	Vector2D res;
	Vector2DSubtract(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator*(float fl) const
{
	Vector2D res;
	Vector2DMultiply(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator*(const Vector2D& v) const
{
	Vector2D res;
	Vector2DMultiply(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator/(float fl) const
{
	Vector2D res;
	Vector2DDivide(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator/(const Vector2D& v) const
{
	Vector2D res;
	Vector2DDivide(*this, v, res);
	return res;
}

inline Vector2D operator*(float fl, const Vector2D& v)
{
	return v * fl;
}


struct SVector
{
	float x;
	float y;
	float z;
	SVector(float x1, float y1, float z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
};

Vector calc_angle(Vector src, Vector dst)
{
	Vector angle = Vector();
	SVector delta = SVector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	angle.x = atan(delta.z / hyp) * (180.0f / M_PI);
	angle.y = atan(delta.y / delta.x) * (180.0f / M_PI);
	angle.z = 0;
	if (delta.x >= 0.0) angle.y += 180.0f;

	return angle;
}

struct glowMode
{
	BYTE GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

struct glowFade
{
	int a, b;
	float c, d, e, f;
};

void get_class_name(uint64_t Entity_ptr, char* out_str)
{
	uint64_t client_networkable_vtable = *(uint64_t*)(Entity_ptr + 8 * 3);

	uint64_t get_client_class = *(uint64_t*)(client_networkable_vtable + 8 * 3);

	uint32_t disp = *(uint32_t*)(get_client_class + 3);
	const uint64_t client_class_ptr = get_client_class + disp + 7;

	ClientClass client_class = *(ClientClass*)(client_class_ptr);

	memcpy(&client_class.pNetworkName, out_str, 32);
}

Vector oldPunch;
Vector old_aimpunch;
#include "Qangles.h"
class Entity
{
public:
	

	bool is_dummie();
	bool is_item();
	bool is_player();
	bool is_visible(int i);
	bool isAlive();
	bool isKnocked();
	inline float last_vis_time();
	int ammo();
	int armor_type();
	int health();
	int id_num();
	int down();
	int max_shield();
	int shield();
	int team_num();
	std::string get_signifier();
	uint64_t get_wepon();
	uint64_t GetWeapon();
	Vector aim_punch();
	Vector base_position();
	Vector bone_position(int id);
	Vector cam_pos();
	Vector sway_angles();
	Vector view_angles();
	Vector getstudiohdr(int id);
	Vector getAbsVelocity();
	QAngle Q_sway_angles();
	QAngle Q_view_angles();
	void Q_set_view_angles(QAngle angles);
	void set_view_angles(Vector angles);
	void start_glowing(int i);
	void stop_glowing();
	std::string name();
};

std::string Entity::name()
{
	//return *(char*)(engine::get_player_name(this));
	uintptr_t nameIndex = *(uintptr_t*)(this + 0x694);
	uintptr_t nameOffset = *(uintptr_t*)(dwbase+ OFFSET_NAME_LIST + ((nameIndex - 1) << 4));
	char buf[64] = { 0 };
	*(UINT_PTR*)buf[64] = nameOffset;
	return buf;
}

int Entity::health()
{
	return *(int*)(this + OFFSET_HEALTH);
}

int Entity::shield()
{
	return *(int*)(this + OFFSET_SHIELD);
}

int Entity::armor_type()
{
	return *(int*)(this + ARMOR_TYPE);
}

inline float Entity::last_vis_time()
{
	return *(float*)(this + OFFSET_VISIBLE_TIME);
}

bool Entity::is_player()
{
	return *(uint64_t*)(this + OFFSET_NAME) == 125780153691248;
}

uint64_t Entity::get_wepon()
{
	return *(uint64_t*)(this + OFFSET_WEAPON);
}

uint64_t Entity::GetWeapon()
{
	/*uint64_t worldEnt = *(uint64_t*)(dwbase + OFFSET_EntityLIST);
	 if (!worldEnt)
	{
		ImGui::End();
		return;
	}*/
	uint64_t WeaponHandle = *(uint64_t*)(this + OFFSET_WEAPON);
	WeaponHandle &= 0xffff;
	uint64_t activeWeap = *(uint64_t*)((dwbase + OFFSET_EntityLIST) + (WeaponHandle << 5));
	if (activeWeap != 0)
	{
		return activeWeap;
	}
	else return 0;
}

Vector Entity::view_angles()
{
	return *(Vector*)(this + OFFSET_VIEWANGLES);
}

Vector Entity::aim_punch()
{
	return *(Vector*)(this + OFFSET_AIMPUNCH);
}

void Entity::set_view_angles(Vector angles)
{
	*(Vector*)(this + OFFSET_VIEWANGLES) = angles;
}
void Entity::Q_set_view_angles(QAngle angles)
{
	*(QAngle*)(this + OFFSET_VIEWANGLES) = angles;
}

Vector Entity::sway_angles()
{
	return *(Vector*)(this + OFFSET_BREATH_ANGLES);
}

QAngle Entity::Q_sway_angles()
{
	return *(QAngle*)(this + OFFSET_BREATH_ANGLES);
}

QAngle Entity::Q_view_angles()
{
	return *(QAngle*)(this + OFFSET_VIEWANGLES);
}

Vector Entity::cam_pos()
{
	return *(Vector*)(this + OFFSET_CAMERAPOS);
}

Vector Entity::base_position()
{
	return *(Vector*)(this + OFFSET_ORIGIN);
}

int Entity::ammo()
{
	return *(int*)(this + OFFSET_AMMO);
}

int Entity::down()
{
	return *(int*)(this + OFFSET_BLEED_OUT_STATE);
}

int Entity::max_shield()
{
	return *(int*)(this + MAX_SHIELD);
}

int Entity::team_num()
{
	return *(int*)(this + OFFSET_TEAM);
}

int Entity::id_num()
{
	return *(int*)(this + OFFSET_ITEM_ID);
}

bool Entity::isAlive()
{
	return *(int*)(this + OFFSET_LIFE_STATE) == 0;
}

bool Entity::isKnocked()
{
	return *(int*)(this + OFFSET_BLEED_OUT_STATE) > 0;
}

Vector Entity::getAbsVelocity()
{
	return *(Vector*)(this + OFFSET_ABS_VELOCITY);
}

Vector Entity::bone_position(int id)
{
	Vector position = *(Vector*)(this + OFFSET_ORIGIN);
	uintptr_t boneArray = *(uintptr_t*)(this + OFFSET_BONES);
	Vector bone = Vector();
	uint32_t boneloc = (id * 0x30);
	bone_t bo = { };
	bo = *(bone_t*)(boneArray + boneloc);
	bone.x = bo.x + position.x;
	bone.y = bo.y + position.y;
	bone.z = bo.z + position.z;
	return bone;
}

std::string Entity::get_signifier()
{
	uintptr_t sigAddr = *(uintptr_t*)(this + 0x580); // 580h = ida. name = m_iSignifierName

	char buf[128] = { 0 };
	memcpy(&buf, (const void*)sigAddr, 64);

	return buf;
}

void Entity::start_glowing(int i)
{
	//  109, 103, 100, 255 - solid
	//  0, 118, 100, 100 - out line
	glowMode glowStyle = { 109, 103, 100, 100 }; //Default Glow is Outline

	float time = 5000.f;

	//Vector color = { 0, 0, 0 };
	//if (is_visible(i))

	//else
		//setting::glow_col;
	Vector glow_col = { 1.f,.5f,.5f };
	*(glowMode*)(this + GLOW_TYPE) = glowStyle;
	*(Vector*)(this + GLOW_COLOR) = glow_col;
	*(float*)(this + GLOW_DISTANCE) = 40000.f;
	*(float*)(this + GLOW_LIFE_TIME) = time;
	time -= 1.f;
	*(int*)(this + GLOW_CONTEXT) = 1;
	*(int*)(this + GLOW_VISIBLE_TYPE) = 1;
	*(glowFade*)(this + GLOW_FADE) = { 872415232, 872415232, time, time, time, time };
}

void Entity::stop_glowing()
{
	*(int*)(this + OFFSET_GLOW_T1) = 0;
	*(int*)(this + OFFSET_GLOW_T2) = 0;
	*(int*)(this + OFFSET_GLOW_ENABLE) = 2;
	*(int*)(this + OFFSET_GLOW_THROUGH_WALLS) = 5;
	*(float*)(this + GLOW_DISTANCE) = 0;
}

bool Entity::is_visible(int i) {
	const auto VisCheck = last_vis_time();

	const auto IsVis = VisCheck > oVisTime[i] || VisCheck < 0.f && oVisTime[i] > 0.f;

	oVisTime[i] = VisCheck;

	return IsVis;
}

bool Entity::is_dummie()
{
	char class_name[33] = { };
	get_class_name((uint64_t)this, class_name);

	return strncmp(class_name, "CAI_BaseNPC", 11) == 0;
}

bool Entity::is_item()
{
	char class_name[33] = { };
	get_class_name((uint64_t)this, class_name);

	return strncmp(class_name, "CPropSurvival", 13) == 0;
}

Entity* get_entiy(uintptr_t idx){
	return *(Entity**)(dwbase + OFFSET_EntityLIST + (idx << 5));
}

Entity* get_localEntity(){
	return *(Entity**)(dwbase + OFFSET_LOCAL_ENT);
}

class Matrix3x4
{
public:
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
		};

		float m[3][4];
		float mm[12];
	};

	inline Vector& GetAxis(int i)
	{
		return *(Vector*)&m[i][0];
	}
};

class HitBoxManager
{
private:

public:

	Vector2D ScreenHeadBone{};
	Vector2D ScreenNeckBone{};
	Vector2D ScreenChestBone{};
	Vector2D ScreenWaistBone{};
	Vector2D ScreenBotmBone{};

	Vector2D ScreenLeftshoulderBone{};
	Vector2D ScreenLeftelbowBone{};
	Vector2D ScreenLeftHandBone{};
	Vector2D ScreenRightshoulderBone{};
	Vector2D ScreenRightelbowBone{};
	Vector2D ScreenRightHandBone{};

	Vector2D ScreenLeftThighsBone{};
	Vector2D ScreenLeftkneesBone{};
	Vector2D ScreenLeftlegBone{};
	Vector2D ScreenRightThighsBone{};
	Vector2D ScreenRightkneesBone{};
	Vector2D ScreenRightlegBone{};
};

int BoneByHitBox(int HitBox, Entity* local_ent)
{
	//get model ptr
	uint64_t Model = *(uint64_t*)(local_ent + OFFSET_STUDIOHDR);
	if (!Model) return -1;

	//get studio hdr
	uint64_t StudioHdr = *(uint64_t*)(Model + 0x8);
	if (!StudioHdr) return -1;

	//get hitbox array
	int HitBoxsArray = *(int*)(StudioHdr + 0xB4);
	uint64_t HitBoxsArray2 = HitBoxsArray + StudioHdr;
	if (!HitBoxsArray) return -1;

	//get bone index
	int Bone = *(int*)(HitBoxsArray2 + *(int*)(HitBoxsArray2 + 8) + (HitBox * 0x2C));

	return ((Bone < 0) || (Bone > 255)) ? -1 : Bone;
}

struct c_matrix
{
	float matrix[16];
};


float DrawOutlinedText(ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* text, ...)
{
	va_list(args);
	va_start(args, text);

	CHAR wbuffer[256] = { };
	vsprintf_s(wbuffer, text, args);

	va_end(args);

	ImGuiWindow* window = ImGui::GetCurrentWindow();

	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, wbuffer);

		if (center)
		{
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);

			window->DrawList->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), wbuffer);
		}
		else
		{
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);

			window->DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), wbuffer);
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}
	return y;
}

inline c_matrix get_matrix()
{
	uint64_t viewRenderer = *(uint64_t*)(dwbase + OFFSET_RENDER);
	uint64_t viewMatrix = *(uint64_t*)(viewRenderer + OFFSET_MATRIX);

	return *(c_matrix*)(viewMatrix);
}

bool getKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}


bool world_to_screen(Vector in, Vector2D& out)
{

	float* m_vMatrix = get_matrix().matrix;
	float w = m_vMatrix[12] * in.x + m_vMatrix[13] * in.y + m_vMatrix[14] * in.z + m_vMatrix[15];

	if (w < 0.01f)
		return false;

	out.x = m_vMatrix[0] * in.x + m_vMatrix[1] * in.y + m_vMatrix[2] * in.z + m_vMatrix[3];
	out.y = m_vMatrix[4] * in.x + m_vMatrix[5] * in.y + m_vMatrix[6] * in.z + m_vMatrix[7];

	float invw = 1.0f / w;
	out.x *= invw;
	out.y *= invw;

	float xx = GetSystemMetrics(SM_CXSCREEN) / 2;
	float xy = GetSystemMetrics(SM_CYSCREEN) / 2;

	xx += 0.5 * out.x * GetSystemMetrics(SM_CXSCREEN) + 0.5;
	xy -= 0.5 * out.y * GetSystemMetrics(SM_CYSCREEN) + 0.5;

	out.x = xx;
	out.y = xy;

	if (out.x > GetSystemMetrics(SM_CXSCREEN) || out.x < 0 || out.y > GetSystemMetrics(SM_CYSCREEN) || out.y < 0)
		return false;

	return true;
}

Vector calculate_best_bone(Entity* from, Entity* to)
{
	auto calculated_angles = calc_angle(from->cam_pos(), to->bone_position(5));

	Vector view_angles = from->view_angles();
	Vector punchAngle = from->aim_punch();
	Vector sway_angles = from->sway_angles();

	calculated_angles.Normalize();

	calculated_angles -= sway_angles * (100 / 100.f);
	calculated_angles -= (punchAngle * 0.05f) * (100 / 100.f);
	calculated_angles += view_angles * (100 / 100.f);
	oldPunch = punchAngle; // do this so the rcs doesnt

	Vector delta = calculated_angles - view_angles;

	delta.Normalize();

	Vector smoothed_angles = view_angles + delta / setting::aimbot::aimbot_smoothing;

	return smoothed_angles;
}

Vector calculate_best_bone_legit(Entity* from, Entity* to)
{
	auto calculated_angles = calc_angle(from->cam_pos(), to->bone_position(5));

	Vector view_angles = from->view_angles();
	Vector sway_angles = from->sway_angles();

	calculated_angles.Normalize();

	Vector delta = calculated_angles - view_angles;

	delta.Normalize();

	Vector smoothed_angles = view_angles + delta / 10;

	return smoothed_angles;
}

namespace Utils
{
	inline float sqrtf_(float x)
	{
		union { float f; uint32_t i; } z = { x };
		z.i = 0x5f3759df - (z.i >> 1);
		z.f *= (1.5f - (x * 0.5f * z.f * z.f));
		z.i = 0x7EEEEEEE - z.i;
		return z.f;
	}


	double powf_(double x, int y)
	{
		double temp;
		if (y == 0)
			return 1;
		temp = powf_(x, y / 2);
		if ((y % 2) == 0) {
			return temp * temp;
		}
		else {
			if (y > 0)
				return x * temp * temp;
			else
				return (temp * temp) / x;
		}
	}
	double GetCrossDistance(double x1, double y1, double x2, double y2)
	{
		return sqrtf_(powf_((float)(x1 - x2), (float)2) + powf_((float)(y1 - y2), (float)2));
	}
}

bool check_in_fov(Vector2D screen_body, float FOVmax)
{
	float Dist = Utils::GetCrossDistance(screen_body.x, screen_body.y, (SCREEN_W / 2), (SCREEN_H / 2));

	if (Dist < FOVmax)
	{
		float Radius = setting::aimbot::aimbot_fov;

		if (screen_body.x <= ((SCREEN_W / 2) + Radius) &&
			screen_body.x >= ((SCREEN_W / 2) - Radius) &&
			screen_body.y <= ((SCREEN_H / 2) + Radius) &&
			screen_body.y >= ((SCREEN_H / 2) - Radius))
		{
			FOVmax = Dist;
			return true;
		}
		return false;
	}
}


typedef char* (__fastcall* getplayername_fn)(Entity* ent);
getplayername_fn o_getplayername = 0;

typedef bool(__fastcall* islobby_fn)();
islobby_fn o_islobby = 0;


float ToMeters(float x)
{
	return x / 39.62f;
}

namespace engine
{
	bool is_lobby()
	{
		if (o_islobby == 0)
			o_islobby = (islobby_fn)util::ida_signature(dwbase, E("48 83 EC 28 48 8B 0D ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 01 48 3B C2 75 14 83 3D ? ? ? ? ?"));

		return o_islobby();
	}

	char* get_player_name(Entity* ent)
	{
		if (o_getplayername == 0)
			o_getplayername = (getplayername_fn)util::ida_signature(dwbase, E("40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 63 43 38"));

		return o_getplayername(ent);
	}
}

Vector HitBoxPos(int HitBox, Entity* local_ent, Vector EntityPosition)
{
	//get bones base data
	uint64_t Bones = *(uint64_t*)(local_ent + OFFSET_BONECLASS);
	if (!Bones) return Vector();


	int Bone = BoneByHitBox(HitBox, local_ent);

	if (Bone == -1) return Vector();

	Matrix3x4 BoneMatrix = *(Matrix3x4*)(Bones + (Bone * sizeof(Matrix3x4)));
	Vector BoneOff = { BoneMatrix._14, BoneMatrix._24, BoneMatrix._34 };

	Vector Pos = EntityPosition + BoneOff;
	return Pos;
}

Vector Entity::getstudiohdr(int id)
{
	uint64_t bones = *(uint64_t*)(dwbase + this + OFFSET_BONECLASS);
	if (!bones) return Vector();
	int Bone = BoneByHitBox(id, this);
	if (Bone == -1) return Vector();
	Matrix3x4 BoneMatrix = *(Matrix3x4*)(bones + (Bone * sizeof(Matrix3x4)));
	Vector BoneOff = { BoneMatrix._14, BoneMatrix._24, BoneMatrix._34 };
	Vector Pos = base_position() + BoneOff;
	return Pos;
}

void PredictPos(Entity* target, Vector* bonePos, Entity* local)
{
	uint64_t WeaponHandle = *(uint64_t*)(local + OFFSET_WEAPON);
	WeaponHandle &= 0xffff;
	uint64_t activeWeap = *(uint64_t*)((dwbase + OFFSET_EntityLIST) + (WeaponHandle << 5));

	if (activeWeap != 0)
	{
		float bulletSpeed = *(float*)(activeWeap + OFFSET_BULLET_SPEED);
		float bulletGravity = *(float*)(activeWeap + OFFSET_BULLET_SCALE);

		if (bulletSpeed > 1.f)
		{
			Vector muzzle = local->cam_pos();
			float time = bonePos->DistTo(muzzle) / bulletSpeed;
			bonePos->z += (700.f * bulletGravity * 0.5f) * (time * time);
			Vector velDelta = (*(Vector*)(target + OFFSET_ORIGIN - 0xC) * time);
			bonePos->x += velDelta.x;
			bonePos->y += velDelta.y;
			bonePos->z += velDelta.z;
		}
	}
}
class WeaponXEntity
{
public:
	void update(Entity* LocalPlayer);
	float get_projectile_speed();
	float get_projectile_gravity();
	float get_zoom_fov();

private:
	float projectile_scale;
	float projectile_speed;
	float zoom_fov;
};

void WeaponXEntity::update(Entity* LocalPlayer)
{
	extern uint64_t g_Base;
	uint64_t entitylist = *(uint64_t*)(dwbase + OFFSET_EntityLIST);
	uint64_t wephandle = *(uint64_t*)(LocalPlayer + OFFSET_WEAPON);
	wephandle &= 0xffff;

	uint64_t wep_entity = 0;
	*(uint64_t*)(entitylist + (wephandle << 5), wep_entity);

	projectile_speed = (wep_entity + OFFSET_BULLET_SPEED, projectile_speed);
	
	projectile_scale = (wep_entity + OFFSET_BULLET_SCALE, projectile_scale);
	
	zoom_fov = (wep_entity + OFFSET_ZOOM_FOV, zoom_fov);
}

float WeaponXEntity::get_projectile_speed()
{
	return projectile_speed;
}

float WeaponXEntity::get_projectile_gravity()
{
	return 750.0f * projectile_scale;
}

float WeaponXEntity::get_zoom_fov()
{
	return zoom_fov;
}

Vector prediction(Vector LPlayerpos, Vector Targetpos, Entity* from, Entity* target)
{
	WeaponXEntity curweap = WeaponXEntity();
	curweap.update(from);
	float BulletSpeed = curweap.get_projectile_speed();
	//printf("%f\n", BulletSpeed);
	float BulletGrav = curweap.get_projectile_gravity();
	//printf("%f\n", BulletGrav);
	float distance = LPlayerpos.DistTo(Targetpos);
	float time = distance / BulletSpeed;
	Vector BulletGravChange = { 0, BulletGrav * time, 0 };
	Vector TargetVel = target->getAbsVelocity();
	Vector MovementChange = TargetVel * time;
	Vector FinalPos = Targetpos + MovementChange + BulletGravChange;
	return FinalPos;
}
struct PredictCtx
{
	Vector StartPos;
	Vector TargetPos;
	Vector TargetVel;
	float BulletSpeed;
	float BulletGravity;

	Vector2D AimAngles;
};

Vector ExtrapolatePos(const PredictCtx& Ctx, float Time)
{
	return Ctx.TargetPos + (Ctx.TargetVel * Time);
}

bool OptimalPitch(const PredictCtx& Ctx, const Vector2D& Dir2D, float* OutPitch)
{
	float Vel = Ctx.BulletSpeed, Grav = Ctx.BulletGravity, DirX = Dir2D.x, DirY = Dir2D.y;
	float Root = Vel * Vel * Vel * Vel - Grav * (Grav * DirX * DirX + 2.f * DirY * Vel * Vel);
	if (Root >= 0.f) { *OutPitch = atanf((Vel * Vel - sqrt(Root)) / (Grav * DirX)); return true; }
	return false;
}

bool SolveTrajectory(PredictCtx& Ctx, const Vector& ExtrPos, float* TravelTime)
{
	Vector Dir = ExtrPos - Ctx.StartPos;
	Vector2D Dir2D = { sqrtf(Dir.x * Dir.x + Dir.y * Dir.y), Dir.z };

	float CurPitch;
	if (!OptimalPitch(Ctx, Dir2D, &CurPitch))
	{
		return false;
	}

	*TravelTime = Dir2D.x / (cosf(CurPitch) * Ctx.BulletSpeed);
	Ctx.AimAngles.y = atan2f(Dir.y, Dir.x);
	Ctx.AimAngles.x = CurPitch;
	return true;
}
bool BulletPredict(PredictCtx& Ctx)
{
	float MAX_TIME = 1.f, TIME_STEP = (1.f / 256.f);
	for (float CurrentTime = 0.f; CurrentTime <= MAX_TIME; CurrentTime += TIME_STEP)
	{
		float TravelTime;
		Vector ExtrPos = ExtrapolatePos(Ctx, CurrentTime);
		if (!SolveTrajectory(Ctx, ExtrPos, &TravelTime))
		{
			return false;
		}

		if (TravelTime < CurrentTime)
		{
			Ctx.AimAngles = { -RAD2DEG(Ctx.AimAngles.x), RAD2DEG(Ctx.AimAngles.y) };
			return true;
		}
	}
	return false;
}


QAngle CalculateBestBoneAim(Entity* from, uintptr_t t, float max_fov)
{
	Entity* target = get_entiy(t);


	if (!target->isAlive() || target->isKnocked())
	{
		return QAngle(0, 0, 0);
	}

	Vector LocalCamera = from->cam_pos();
	//Vector TargetBonePosition = target.getBonePosition(bone);
	//get TartgetBonePosition by using hitboxpos
	Vector TargetBonePosition = target->bone_position(setting::aimbot::aimBone);
	QAngle CalculatedAngles = QAngle(0, 0, 0);

	WeaponXEntity curweap = WeaponXEntity();
	curweap.update(from);
	float BulletSpeed = curweap.get_projectile_speed();
	float BulletGrav = curweap.get_projectile_gravity();
	float zoom_fov = curweap.get_zoom_fov();

	if (zoom_fov != 0.0f && zoom_fov != 1.0f)
	{
		max_fov *= zoom_fov / 90.0f;
	}

	// more accurate prediction
	if (BulletSpeed > 1.f)
	{
		PredictCtx Ctx;
		Ctx.StartPos = LocalCamera;
		Ctx.TargetPos = TargetBonePosition;
		Ctx.BulletSpeed = BulletSpeed - (BulletSpeed * 0.08);
		Ctx.BulletGravity = BulletGrav + (BulletGrav * 0.05);
		Ctx.TargetVel = target->getAbsVelocity();

		if (BulletPredict(Ctx))
			CalculatedAngles = QAngle{ Ctx.AimAngles.x, Ctx.AimAngles.y, 0.f };
	}

	if (CalculatedAngles == QAngle(0, 0, 0))
		CalculatedAngles = CalcAngle(LocalCamera, TargetBonePosition);

	QAngle ViewAngles = from->Q_view_angles();
	QAngle SwayAngles = from->Q_sway_angles();


	// remove sway and recoil
	//if (aim_no_recoil)
		CalculatedAngles -= SwayAngles - ViewAngles;
	monkey(CalculatedAngles);
	QAngle Delta = CalculatedAngles - ViewAngles;
	double fov = GetFov(SwayAngles, CalculatedAngles);
	if (fov > max_fov)
	{
		return QAngle(0, 0, 0);
	}

	monkey(Delta);

	QAngle SmoothedAngles = ViewAngles + Delta / setting::aimbot::aimbot_smoothing;

	return SmoothedAngles;
}

