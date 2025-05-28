
inline Vec3 operator+(const Vec3 left, const Vec3 right)
{
    return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}

inline Vec3 operator+=(Vec3 &left, const Vec3 right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
}

inline Vec3 operator-(const Vec3 &left, const Vec3 &right)
{
    return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}

inline Vec3 operator*(const double &left, const Vec3 &right)
{
    return Vec3(left * right.x, left * right.y, left * right.z);
}

inline Vec3 operator*(const Vec3 &left, const double &right)
{
    return Vec3(left.x * right, left.y * right, left.z * right);
}

inline double operator*(const Vec3 &left, const Vec3 &right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

inline Vec3 operator/(const Vec3 &left, const double right)
{
    return Vec3(left.x / right, left.y / right, left.z / right);
}

inline bool operator==(const Vec3 &left, const Vec3 &right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

inline Vec3 Vec3::Cross(const Vec3 &a, const Vec3 &b)
{
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

inline double Vec3::Magnitude() const
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

inline void Vec3::Print() const 
{
    std::cout << "[ " << x << " " << y << " " << z << " ]" << std::endl;
}

inline Vector3 Vec3::ToVector3() const
{
    return (Vector3){ (float)x, (float)y, (float)z };
}

inline Vec3 Vec3::Normalize(const Vec3 &src)
{
    return src / src.Magnitude();
}

