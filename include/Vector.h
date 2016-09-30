///
/// A 2d (x,y) Vector
///
#pragma once

namespace df
{

class Vector
{

private:
    float x; ///< Horizontal component.
    float y; ///< Vertical component.

public:
    /// Create Vector with (x,y).
    Vector(float init_x, float init_y);

    /// Default is (0,0).
    Vector();

    float getX() const;                   ///< Get horizontal component.
    void setX(float new_x);               ///< Set horizontal component.
    float getY() const;                   ///< Get vertical component.
    void setY(float new_y);               ///< Set vertical component.
    void setXY(float new_x, float new_y); ///< Set horizizontal & vertical.
    
    void normalize();		///< Normalize Vector.
    void scale(float s);		///< Scale Vector.
    float getMagnitude() const;	///< Return magnitude.
    bool operator==(const Vector &other) const;  ///< Compare Vector.
    bool operator!=(const Vector &other) const;  ///< Compare Vector.
    Vector &operator+=(const Vector &other);     ///< Add other Vector to this one.
	
    Vector operator+(const Vector& other) const; ///< Add Vector.
    Vector operator-(const Vector& other) const; ///< Subtract Vector.
    bool operator!() const;                          ///< Test if (0,0).
};

} // end of namespace df
