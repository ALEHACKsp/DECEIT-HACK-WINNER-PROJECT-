#pragma once
#include <windows.h>
#include <d3d9.h>
#include <math.h>

#ifdef _DEBUG
#define ILINE _inline
#else
#define ILINE __forceinline
#endif

typedef signed char      int8;
typedef signed short     int16;
typedef signed int		 int32;
typedef signed __int64	 int64;
typedef unsigned char	 uint8;
typedef unsigned short	 uint16;
typedef unsigned int	 uint32;
typedef unsigned __int64 uint64;
typedef char             s_char;
typedef const char*      c_char;
typedef const wchar_t*   c_char_w;

//#define z_ptr            nullptr
//#define ret              return 
//#define r_false          ret false
//#define r_true           ret true
//#define t64              this
//#define t_call           __thiscall
//#define f_call           __fastcall
#define dev_8(c)         c/8

typedef float f32;
typedef double f64;
#define zero_buffer ""
f32 f32_zero = 0.000f;
f32 m_pi_32 = 3.14159f;
f64 m_pi_64 = 3.14159265358979323846264;
ILINE f32 __fsel(const f32 _a, const f32 _b, const f32 _c) { return (_a < 0.0f) ? _c : _b; }
ILINE f64 __fsel(const f64 _a, const f64 _b, const f64 _c) { return (_a < 0.0f) ? _c : _b; }
ILINE f32 __fself(const f32 _a, const f32 _b, const f32 _c) { return (_a < 0.0f) ? _c : _b; }
ILINE f32 __fsels(const f32 _a, const f32 _b, const f32 _c) { return (_a < 0.0f) ? _c : _b; }
ILINE f32 __fres(const f32 _a) { return 1.f / _a; }

enum type_zero { _zero };
enum type_min { v_min };
enum type_max { v_max };
enum type_identity { _identity };

typedef void* win_hwnd;
typedef void* win_hinstance;
typedef void* win_hdc;
typedef void* win_hglrc;

float m_sqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)& i;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	return 1 / y;
}

double m_sin(double x) 
{
	double sign = 1;
	if (x < 0) {
		sign = -1.0;
		x = -x;
	}
	if (x > 360) x -= int(x / 360) * 360;
	x *= 3.14159265358979323846264 / 180.0;
	double res = 0;
	double term = x;
	int k = 1;
	while (res + term != res) 
	{
		res += term;
		k += 2;
		term *= -x * x / k / (k - 1);
	}

	return sign * res;
}

double m_cos(double x)
{
	if (x < 0) x = -x;
	if (x > 360) x -= int(x / 360) * 360;
	x *= 3.14159265358979323846264 / 180.0;
	double res = 0;
	double term = 1;
	int k = 0;
	while (res + term != res)
	{
		res += term;
		k += 2;
		term *= -x * x / k / (k - 1);
	}
	return res;
}

struct vec_to_screen
{
public:
	f32 to_x;
	f32 to_y;
	f32 to_z;
	f32* out_x;
	f32* out_y;
	f32* out_z;
};

struct ray_hit_cached
{
	int Unknown001[0x100];
};

struct UCol
{
	union
	{
		uint32 dcolor;
		uint8  bcolor[4];
		struct { uint8 b, g, r, a; };
		struct { uint8 z, y, x, w; };
	};
};

inline void mathVec3Transform(f32 out[4], const f32 m[16], const f32 in[3])
{
#define M(row,col)  m[col*4+row]
	out[0] = M(0, 0) * in[0] + M(0, 1) * in[1] + M(0, 2) * in[2] + M(0, 3) * 1.0f;
	out[1] = M(1, 0) * in[0] + M(1, 1) * in[1] + M(1, 2) * in[2] + M(1, 3) * 1.0f;
	out[2] = M(2, 0) * in[0] + M(2, 1) * in[1] + M(2, 2) * in[2] + M(2, 3) * 1.0f;
	out[3] = M(3, 0) * in[0] + M(3, 1) * in[1] + M(3, 2) * in[2] + M(3, 3) * 1.0f;
#undef M
}

template <typename F> struct Vec3_tpl
{
	F x, y, z;
	ILINE Vec3_tpl(type_zero) : x(0), y(0), z(0) {}
	ILINE Vec3_tpl(type_min);
	ILINE Vec3_tpl(type_max);
	explicit ILINE Vec3_tpl(F f) : x(f), y(f), z(f) { }
	ILINE Vec3_tpl() {
		Vec3_tpl(0, 0, 0);
	}
	ILINE Vec3_tpl(F xt, F yt, F zt) {
		x = xt;
		y = yt;
		z = zt;
	}
	ILINE F length() const { return (F)m_sqrt(x*x + y * y + z * z); }
	template<typename T> ILINE F sum(T a) {
		F s = 0;
		for (int i = 0; i < a.size; ++i) s += a[i];
		return s;
	}
	template<typename T> ILINE F dot(T a, T b) { return sum(a * b); }
	ILINE F  distance(Vec3_tpl VecB) { return (F)m_sqrt(((x - VecB.x) * (x - VecB.x)) + ((y - VecB.y) * (y - VecB.y)) + ((z - VecB.z) * (z - VecB.z))); }
	ILINE F  get_length() const { return (F)m_sqrt(x * x + y * y + z * z); }
	ILINE F& operator[](int index) { return ((F*)this)[index]; }
	ILINE F  operator[](int index) const { return ((F*)this)[index]; }
	void operator += (F f) { x += f; y += f; z += f; }
	void operator -= (F f) { x -= f; y -= f; z -= f; }
	ILINE Vec3_tpl<F> operator*(F k) const {
		const Vec3_tpl<F> v = *this;
		return Vec3_tpl<F>(v.x * k, v.y * k, v.z * k);
	}
	ILINE Vec3_tpl &operator /  (F f) { return Vec3_tpl(x / f, y / f, z / f); }
	ILINE Vec3_tpl &operator = (const Vec3_tpl &source) { x = source.x; y = source.y; z = source.z; return *this; }
	ILINE Vec3_tpl &operator = (const F value) { x = value; y = value; z = value;   return *this; }
	ILINE Vec3_tpl &operator *= (F f) { x *= f; y *= f; z *= f; return *this; }
	ILINE Vec3_tpl &operator /= (F f) { x /= f; y /= f; z /= f; return *this; }
	ILINE friend Vec3_tpl operator + (const Vec3_tpl &vec1, const Vec3_tpl &vec2) { return Vec3_tpl(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z); }
	ILINE friend Vec3_tpl operator + (const Vec3_tpl &vec1, const F*  vec2) { return vec1 + Vec3_tpl(vec2); }
	ILINE friend Vec3_tpl operator + (const F*  vec1, const Vec3_tpl &vec2) { return Vec3_tpl(vec1) + vec2; }
	ILINE friend Vec3_tpl operator - (const Vec3_tpl &vec1, const Vec3_tpl &vec2) { return Vec3_tpl(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z); }
	ILINE friend Vec3_tpl operator - (const Vec3_tpl &vec1, const F*  vec2) { return vec1 - Vec3_tpl(vec2); }
	ILINE friend Vec3_tpl operator - (const F*  vec1, const Vec3_tpl &vec2) { return Vec3_tpl(vec1) - vec2; }
	ILINE Vec3_tpl<F>& Set(const F xval, const F yval, const F zval)
	{
		x = xval; y = yval; z = zval;
		return *this;
	}
	ILINE Vec3_tpl& normalize()
	{
		F len2 = x * x + y * y + z * z;
		if (len2 > (F)1e-20f) {
			F rlen = m_sqrt(len2);
			x *= rlen;
			y *= rlen;
			z *= rlen;
		}
		else Set(0, 0, 1);

		return *this;
	}
	ILINE Vec3_tpl<F> GetNormalized() const
	{
		FLOAT fInvLen = (FLOAT)isqrt_safe_tpl(x*x + y * y + z * z);
		Vec3_tpl<F> out = *this;
		out.x *= fInvLen;
		out.y *= fInvLen;
		out.z *= fInvLen;
		return out;
	}
};

template<class F> struct Vec2_tpl
{
	typedef F value_type;
	F x, y;
	ILINE Vec2_tpl() {};
	ILINE Vec2_tpl(type_zero) : x(0), y(0) {}
	ILINE Vec2_tpl(F vx, F vy) { x = F(vx); y = F(vy); }
	ILINE Vec2_tpl& set(F nx, F ny) { x = F(nx); y = F(ny); return *this; }
	template<class F1> ILINE Vec2_tpl(const Vec2_tpl<F1> &src) { x = F(src.x); y = F(src.y); }
	template<class F1> ILINE explicit Vec2_tpl(const Vec3_tpl<F1> &src) { x = F(src.x); y = F(src.y); }
	template<class F1> ILINE explicit Vec2_tpl(const F1 *psrc) { x = F(psrc[0]); y = F(psrc[1]); }
	explicit ILINE Vec2_tpl(const Vec3_tpl<F>& v) : x((F)v.x), y((F)v.y) { assert(this->IsValid()); }
};
template <typename F> struct Vec4_tpl
{
	typedef F value_type;
	F x, y, z, w;
};
typedef Vec4_tpl<f32> Vec4;
template <typename F> struct Quat_tpl
{
	Vec3_tpl<F> v;
	F w;
	ILINE  Quat_tpl() {}
	ILINE  Quat_tpl(F angle, const Vec3_tpl<F> &axis) : w(angle), v(axis) {};
	ILINE  Quat_tpl(type_identity) : w(1), v(0, 0, 0) {}
	ILINE  bool operator!=(const Quat_tpl<F> &q) const { return !(*this == q); }
	ILINE  Quat_tpl<F>	operator - () const { return Quat_tpl<F>(-w, -v); };

	ILINE  void set_rotation_v_dir(const Vec3_tpl<F>& vdir)
	{
		w = (0.70710676908493042f);
		v.x = (vdir.z * 0.70710676908493042f);
		v.y = (0.0f);
		v.z = (0.0f);
		F l = (F)m_sqrt(vdir.x * vdir.x + vdir.y * vdir.y);

		if (l > (0.00001)) 
		{
			Vec3_tpl<F> hv;
			hv.x = vdir.x / l;
			hv.y = vdir.y / l + 1.0f;
			hv.z = l + 1.0f;

			F r = (F)m_sqrt(hv.x * hv.x + hv.y * hv.y);
			F s = (F)m_sqrt(hv.z * hv.z + vdir.z * vdir.z);
			F hacos0 = 0.0;
			F hasin0 = -1.0;

			if (r > (0.00001)) 
			{
				hacos0 = hv.y / r;
				hasin0 = -hv.x / r;
			}
			F hacos1 = hv.z / s;
			F hasin1 = vdir.z / s;
			w = (hacos0 * hacos1);
			v.x = (hacos0 * hasin1);
			v.y = (hasin0 * hasin1);
			v.z = (hasin0 * hacos1);
		}
	}

	static Quat_tpl<F> create_rotation_v_dir(const Vec3_tpl<F>& vdir)
	{
		Quat_tpl<F> q;
		q.set_rotation_v_dir(vdir);
		return q;
	}

	Vec3_tpl<F> to_forward_vector()
	{
		return Vec3_tpl<F>(2 * (v.x * v.y - v.z * w), 2 * (v.y * v.y + w * w) - 1, 2 * (v.z * v.y + v.x * w));
	}
};
template <typename F> struct QuatT_tpl
{
	Quat_tpl<F>   q;
	Vec3_tpl<F> t;
	ILINE  QuatT_tpl() {};
	ILINE  QuatT_tpl(const Vec3_tpl<F>& _t, const Quat_tpl<F>& _q) { q = _q; t = _t; }
	ILINE  QuatT_tpl(type_identity) { q.w = 1; q.v.x = 0; q.v.y = 0; q.v.z = 0; t.x = 0; t.y = 0; t.z = 0; }
};
template <typename F> struct Matrix33_tpl
{
	F m00, m01, m02;
	F m10, m11, m12;
	F m20, m21, m22;
	ILINE  Matrix33_tpl() {};
	template<typename F1> ILINE  Matrix33_tpl(const Matrix33_tpl<F1>& m)
	{
		m00 = F(m.m00);	m01 = F(m.m01);	m02 = F(m.m02);
		m10 = F(m.m10);	m11 = F(m.m11);	m12 = F(m.m12);
		m20 = F(m.m20);	m21 = F(m.m21);	m22 = F(m.m22);
	}
	ILINE  Matrix33_tpl& operator = (const Matrix33_tpl<F> &m)
	{
		m00 = m.m00;	m01 = m.m01;	m02 = m.m02;
		m10 = m.m10;	m11 = m.m11;	m12 = m.m12;
		m20 = m.m20;	m21 = m.m21;	m22 = m.m22;
		return *this;
	}
};
template <typename F> struct Matrix34_tpl
{
	F m00, m01, m02, m03;
	F m10, m11, m12, m13;
	F m20, m21, m22, m23;
	ILINE Matrix34_tpl() {};
	template<class F1> explicit Matrix34_tpl(const QuatT_tpl<F1>& q)
	{
		Vec3_tpl<F1> v2 = q.q.v + q.q.v;
		F1 xx = 1 - v2.x*q.q.v.x;		F1 yy = v2.y*q.q.v.y;		F1 xw = v2.x*q.q.w;
		F1 xy = v2.y*q.q.v.x;			F1 yz = v2.z*q.q.v.y;		F1 yw = v2.y*q.q.w;
		F1 xz = v2.z*q.q.v.x;			F1 zz = v2.z*q.q.v.z;		F1 zw = v2.z*q.q.w;
		m00 = F(1 - yy - zz);					m01 = F(xy - zw);					m02 = F(xz + yw);			m03 = F(q.t.x);
		m10 = F(xy + zw);						m11 = F(xx - zz);					m12 = F(yz - xw);			m13 = F(q.t.y);
		m20 = F(xz - yw);						m21 = F(yz + xw);					m22 = F(xx - yy);			m23 = F(q.t.z);
	}
	ILINE Vec3_tpl<F> get_translation() const { return Vec3_tpl<F>(m03, m13, m23); }
	ILINE void set_translation(const Vec3_tpl<F>& t) { m03 = t.x;	m13 = t.y; m23 = t.z; }
};
template <class F> Matrix34_tpl<F> operator * (const Matrix34_tpl<F>& l, const Matrix34_tpl<F>& r)
{
	Matrix34_tpl<F> m;
	m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;
	m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;
	m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
	m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;
	m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;
	m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
	m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
	m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
	m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
	m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03;
	m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13;
	m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23;
	return m;
}

typedef Vec2_tpl<f32>     Vec2;
typedef Vec3_tpl<f32>     Vec3;
typedef Quat_tpl<f32>     Quat;
typedef QuatT_tpl<f32>	  QuatT;
typedef Matrix34_tpl<f32> Matrix34;
typedef Matrix33_tpl<f32> Matrix33;
template <class T> struct Color_tpl;
typedef Color_tpl<uint8> ColorB;
typedef Color_tpl<float> ColorF;

template <class T> struct Color_tpl
{
	T	r, g, b, a;
	inline Color_tpl() {};
	Color_tpl(T _x, T _y, T _z, T _w);
	Color_tpl(T _x, T _y, T _z);
	Color_tpl(const unsigned int abgr);
	Color_tpl(const f32 c);
	Color_tpl(const ColorF& c);
	Color_tpl(const Vec3& c, f32 fAlpha);
};

template<>
inline Color_tpl<f32>::Color_tpl(f32 _x, f32 _y, f32 _z, f32 _w)
{
	r = _x; g = _y; b = _z; a = _w;
}

template<>
inline Color_tpl<f32>::Color_tpl(f32 _x, f32 _y, f32 _z)
{
	r = _x; g = _y; b = _z; a = 1.f;
}

template<>
inline Color_tpl<uint8>::Color_tpl(uint8 _x, uint8 _y, uint8 _z, uint8 _w)
{
	r = _x; g = _y; b = _z; a = _w;
}

template<>
inline Color_tpl<uint8>::Color_tpl(uint8 _x, uint8 _y, uint8 _z)
{
	r = _x; g = _y; b = _z; a = 255;
}
template<>
inline Color_tpl<f32>::Color_tpl(const unsigned int abgr)
{
	r = (abgr & 0xff) / 255.0f;
	g = ((abgr >> 8) & 0xff) / 255.0f;
	b = ((abgr >> 16) & 0xff) / 255.0f;
	a = ((abgr >> 24) & 0xff) / 255.0f;
}
template<>
inline Color_tpl<uint8>::Color_tpl(const unsigned int c) { *(unsigned int*)(&r) = c; }
template<>
inline Color_tpl<f32>::Color_tpl(const float c)
{
	r = c;	g = c;	b = c;	a = c;
}
template<>
inline Color_tpl<uint8>::Color_tpl(const float c)
{
	r = (uint8)(c * 255);	g = (uint8)(c * 255);	b = (uint8)(c * 255);	a = (uint8)(c * 255);
}
template<>
inline Color_tpl<f32>::Color_tpl(const ColorF& c)
{
	r = c.r;	g = c.g;	b = c.b;	a = c.a;
}
template<>
inline Color_tpl<uint8>::Color_tpl(const ColorF& c) {
	r = (uint8)(c.r * 255);	g = (uint8)(c.g * 255);	b = (uint8)(c.b * 255);	a = (uint8)(c.a * 255);
}
template<>
inline Color_tpl<f32>::Color_tpl(const Vec3& c, float fAlpha)
{
	r = c.x;	g = c.y;	b = c.z;	a = fAlpha;
}
template<>
inline Color_tpl<uint8>::Color_tpl(const Vec3& c, float fAlpha)
{
	r = (uint8)(c.x * 255);	g = (uint8)(c.y * 255);	b = (uint8)(c.z * 255);	a = (uint8)(fAlpha * 255);
}

class cry_color
{
public:
	int32 a, r, g, b;
	f32 max_color = 255.0f;

	cry_color()
	{
		cry_color(0, 0, 0, 0);
	}
	cry_color(int32 a, int32 r, int32 g, int32 b)
	{
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	cry_color(int32 r, int32 g, int32 b)
	{
		this->a = 255;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	cry_color(uint32 color)
	{
		this->b = (color & 0xff);
		this->g = ((color >> 8) & 0xff);
		this->r = ((color >> 16) & 0xff);
		this->a = ((color >> 24) & 0xff);
	}
	inline f32* base_color()
	{
		f32 f_color[3];
		f_color[0] = this->r / max_color;
		f_color[1] = this->g / max_color;
		f_color[2] = this->b / max_color;
		return &f_color[0];
	}

	inline f32 r_base() const { return this->r / max_color; }
	inline f32 g_base() const { return this->g / max_color; }
	inline f32 b_base() const { return this->b / max_color; }
	inline f32 a_base() const { return this->a / max_color; }

	inline operator unsigned long() const
	{
		return (a << 24) | (r << 16) | (g << 8) | b;
	}
};

struct color_f
{
	f32 r;
	f32 g;
	f32 b;
	f32 a;
};

struct AABB
{
	Vec3 min;
	Vec3 max;

	ILINE Vec3 get_center() const
	{
		return (min + max) * 0.5f;
	}

	ILINE bool is_reset() const
	{
		return min.x > max.x;
	}

	ILINE f32 is_reset_sel(f32 if_reset, f32 if_not_reset) const
	{
		return (f32)__fsel(max.x - min.x, if_not_reset, if_reset);
	}

	ILINE Vec3 get_size() const
	{
		return (max - min) * is_reset_sel(0.0f, 1.0f);
	}

	ILINE void reset()
	{
		min = Vec3(1e15f);
		max = Vec3(-1e15f);
	}
};

#define R_PRIMV_TRIANGLES		   0
#define R_PRIMV_TRIANGLE_STRIP	   1
#define R_PRIMV_LINES			   7
#define R_PRIMV_LINESTRIP		   8
#define GS_BLSRC_MASK              0xF
#define GS_BLSRC_ZERO              0x1
#define GS_BLSRC_ONE               0x2
#define GS_BLSRC_DSTCOL            0x3
#define GS_BLSRC_ONEMINUSDSTCOL    0x4
#define GS_BLSRC_SRCALPHA          0x5
#define GS_BLSRC_ONEMINUSSRCALPHA  0x6
#define GS_BLSRC_DSTALPHA          0x7
#define GS_BLSRC_ONEMINUSDSTALPHA  0x8
#define GS_BLSRC_ALPHASATURATE     0x9
#define GS_BLDST_MASK              0xF0
#define GS_BLDST_ZERO              0x10
#define GS_BLDST_ONE               0x20
#define GS_BLDST_SRCCOL            0x30
#define GS_BLDST_ONEMINUSSRCCOL    0x40
#define GS_BLDST_SRCALPHA          0x50
#define GS_BLDST_ONEMINUSSRCALPHA  0x60
#define GS_BLDST_DSTALPHA          0x70
#define GS_BLDST_ONEMINUSDSTALPHA  0x80
#define GS_WIREFRAME               0x00010000
#define GS_POINTRENDERING          0x00020000
#define GS_NODEPTHTEST             0x00040000
#define R_CULL_DISABLE             0
#define R_CULL_NONE                0
#define R_CULl_fRONT               1
#define R_CULL_BACK                2
#define UIDRAW_TEXTSIZEFACTOR      (12.0f)
#define BIT(x)                     (1<<(x))

enum EDrawTextFont
{
	font_default,
	font_overlay,
	font_warface
};

enum EDrawTextFlags
{
	eDrawText_Center = BIT(1),
	eDrawText_Right = BIT(2),
	eDrawText_2D = BIT(4),
	eDrawText_FixedSize = BIT(3),
	eDrawText_800x600 = BIT(5),
	eDrawText_Monospace = BIT(6),
	eDrawText_Framed = BIT(7),
};

enum EColorOp
{
	eCO_NOSET = 0,
	eCO_DISABLE = 1,
	eCO_REPLACE = 2,
	eCO_DECAL = 3,
	eCO_ARG2 = 4,
	eCO_MODULATE = 5,
	eCO_MODULATE2X = 6,
	eCO_MODULATE4X = 7,
	eCO_BLENDDIFFUSEALPHA = 8,
	eCO_BLENDTEXTUREALPHA = 9,
	eCO_DETAIL = 10,
	eCO_ADD = 11,
	eCO_ADDSIGNED = 12,
	eCO_ADDSIGNED2X = 13,
	eCO_MULTIPLYADD = 14,
	eCO_BUMPENVMAP = 15,
	eCO_BLEND = 16,
	eCO_MODULATEALPHA_ADDCOLOR = 17,
	eCO_MODULATECOLOR_ADDALPHA = 18,
	eCO_MODULATEINVALPHA_ADDCOLOR = 19,
	eCO_MODULATEINVCOLOR_ADDALPHA = 20,
	eCO_DOTPRODUCT3 = 21,
	eCO_LERP = 22,
	eCO_SUBTRACT = 23,
};

enum EColorArg
{
	eCA_Specular,
	eCA_Texture,
	eCA_Diffuse,
	eCA_Previous,
	eCA_Constant,
};

enum e_ui_draw_horizontal
{
	ui_draw_horizontal_left,
	ui_draw_horizontal_center,
	ui_draw_horizontal_right
};

enum e_ui_draw_vertical
{
	ui_draw_vertical_top,
	ui_draw_vertical_center,
	ui_draw_vertical_bottom
};

enum text_flags : uint8
{
	t_left = 0 << 0,
	t_right = 1 << 1,
	t_centered_x = 1 << 2,
	t_centered_y = 1 << 3,
	t_centered = 1 << 2 | 1 << 3,
};

#define	text_center (DT_CENTER | DT_VCENTER | DT_NOCLIP)
#define	text_left   (DT_LEFT   | DT_VCENTER | DT_NOCLIP)
#define text_right  (DT_RIGHT  | DT_VCENTER | DT_NOCLIP)

#define DEF_TEXARG0 (eCA_Texture|(eCA_Diffuse<<3))
#define DEF_TEXARG1 (eCA_Texture|(eCA_Previous<<3))
#define RGBA8(r,g,b,a)  ((uint32)(((uint8)(r)|((uint16)((uint8)(g))<<8))|(((uint32)(uint8)(b))<<16)) | (((uint32)(uint8)(a))<<24))

struct SVF_P3F_C4B_T2F
{
	Vec3 xyz;
	UCol color;
	Vec2 st;
};

struct s_draw_text_info
{
	int32   flags;
	f32 color[4];
	f32 xscale;
	f32 yscale;

	s_draw_text_info()
	{
		flags = 0;
		color[0] = color[1] = color[2] = color[3] = 1;
		xscale = 1.0f;
		yscale = 1.0f;
	}
};

struct s_text_draw_context
{
	uint32 m_fx_idx;
	Vec2 m_size;
	f32 m_width_scale;
	f32 m_clip_x;
	f32 m_clip_y;
	f32 m_clip_width;
	f32 m_clip_height;
	bool m_proportional;
	bool m_size_in_800x600;
	bool m_clipping_enabled;
	bool m_framed;

	ColorB m_color_override;
	int32 m_draw_text_flags;

	s_text_draw_context() : m_fx_idx(0), m_size{ 16.0f, 16.0f }, m_width_scale(1.0f), m_clip_x(0), m_clip_y(0), m_clip_width(0), m_clip_height(0), m_proportional(true), m_size_in_800x600(true), m_clipping_enabled(false), m_framed(false), m_color_override(0, 0, 0, 0) {}
	void reset() { *this = s_text_draw_context(); }
	void set_effect(uint32 fx_idx) { m_fx_idx = fx_idx; }
	void set_size(const Vec2& size) { m_size = size; }
	void set_char_width_scale(f32 width_scale) { m_width_scale = width_scale; }
	void set_clipping_rect(f32 x, f32 y, f32 width, f32 height) { m_clip_x = x; m_clip_y = y; m_clip_width = width; m_clip_height = height; }
	void set_proportional(bool proportional) { m_proportional = proportional; }
	void set_size_in_800x600(bool size_in_800x600) { m_size_in_800x600 = size_in_800x600; }
	void enable_clipping(bool enable) { m_clipping_enabled = enable; }
	void enable_frame(bool enable) { m_framed = enable; }
	void set_color(const ColorF& col) { m_color_override = col; }
	float get_char_width() const { return m_size.x; }
	float get_char_height() const { return m_size.y; }
	float get_char_width_scale() const { return m_width_scale; }
};

