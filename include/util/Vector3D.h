/**
 * @file        Vector3D.h
 * @author      Robert Koch
 * @version     1.0
 *
 * This file contains the class declaration for a 3-dimensional, mathematical vector.
 */
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

#include "../ErrorMessage.h"


namespace Piko {

    /**
     * Class declaring a 3-dimensional, mathematical vector. Several arithmetic operations can be
     * used on instances of this class.
     */
    template<typename T>
    class Vector3D final {
    
        public:

            /**
             * Standard constructor to create a vector with the coordinates (0,0,0).
             */
            Vector3D();

            /**
             * Constructor to create a vector with the specified coordinates.
             * 
             * @param x x-coordinate
             * @param y y-coordinate
             * @param z z-coordinate
             */
            Vector3D(const T& x, const T& y, const T& z);

            /**
             * Destructor.
             */ 
            ~Vector3D();

            /**
             * Function to get the x-coordinate.
             * 
             * @return x-coordinate.
             */ 
            const T& x() const;

            /**
             * Function to get the y-coordinate.
             * 
             * @return y-coordinate.
             */
            const T& y() const;

            /**
             * Function to get the z-coordinate.
             * 
             * @return z-coordinate.
             */
            const T& z() const;

            /**
             * Function add two vectors.
             * 
             * @param v Vector to add.
             * @return Sum of the vectors.
             */
            const Vector3D<T> operator+(const Vector3D<T>& v) const;

            /**
             * Function to subtract two vectors.
             * 
             * @param v Vector to subtract.
             * @return Difference of the vectors.
             */
            const Vector3D<T> operator-(const Vector3D<T>& v) const;

            /**
             * Function to scalar mutliply two vectors.
             * 
             * @param v Vector to scalar multiply with.
             * @return Scalar product of the vectors.
             */
            const T operator*(const Vector3D<T>& v) const;            

            /**
             * Function to mutliply the vector with a scalar.
             * 
             * @param v Scalar to multiply with.
             * @return Product of vector and scalar.
             */
            const Vector3D<T> operator*(const T& s) const;

            /**
             * Function to divide the vector through a scalar.
             * 
             * @param v Scalar to divide through.
             * @return Quotient of vector and scalar.
             */
            const Vector3D<T> operator/(const T& s) const;
            
            /**
             * Function to get the vector product of the two vectors.
             * 
             * @param v Vector to multiply with.
             * @return Vector product of the vectors.
             */
            const Vector3D<T> operator^(const Vector3D<T>& v) const;

            /**
             * Function to add a vector to the calling instance.
             * 
             * @param v Vector to add.
             * @return Sum of the vectors.
             */
            const Vector3D<T>& operator+=(const Vector3D<T>& v);

            /**
             * Function to subtract a vector to the calling instance.
             * 
             * @param v Vector to subtract.
             * @return Difference of the vectors.
             */
            const Vector3D<T>& operator-=(const Vector3D<T>& v);

            /**
             * Function to multiply the calling instance with a scalar.
             * 
             * @param s Scalar to multiplay with.
             * @return Product of the vector and scalar.
             */
            const Vector3D<T>& operator*=(const T& s);

            /**
             * Function to divide the calling instance through a scalar.
             * 
             * @param s Scalar to divide through.
             * @return Quotient of the vector and scalar.
             */
            const Vector3D<T>& operator/=(const T& s);

            /**
             * Function to multiply the calling vector with the specified one.
             * 
             * @param v Vector to multiply with.
             * @return Vector product of the vectors.
             */
            const Vector3D<T>& operator^=(const Vector3D<T>& v);

            /**
             * Function to change the position of the vector.
             * 
             * @param x New x-Coordinate.
             * @param y New y-Coordinate.
             * @param z New z-Coordinate.
             */
            void setPosition(const T& x, const T& y, const T& z);

            /**
             * Function to normalize the vector.
             */
            void normalize();

            /**
             * Function to get the normalization of the vector. This will not change the vector
             * itself.
             * 
             * @return Vector normalization.
             */
            const Vector3D<T> getNormalization() const;

            /**
             * Function to get the magnitude of the vector.
             * 
             * @return Magnitude.
             */
            const T getMagnitude() const;
            

            /**
             * Function to have nice output, if appended to a stream.
             */
            friend std::ostream& operator<<(std::ostream& stream, const Vector3D<T>& v) {
                return stream << "(" << v.m_x << "," << v.m_y << "," << v.m_z << ")";
            }
        

        private:

            T m_x;      /**< x-Coordinate. */
            T m_y;      /**< y-Coordinate. */
            T m_z;      /**< z-Coordinate. */
    
    
    }; /* Class Vector3D */



    /*==========================================
     * INLINE IMPLEMENTATION
     *=========================================*/

    template<typename T>
    inline Vector3D<T>::Vector3D() 
      :
      m_x(0),
      m_y(0),
      m_z(0) {
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline Vector3D<T>::Vector3D(const T& x, const T& y, const T& z)
      :
      m_x(x),
      m_y(y),
      m_z(z) {
      }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline Vector3D<T>::~Vector3D() {}

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    const T& Vector3D<T>::x() const {
        return m_x;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    const T& Vector3D<T>::y() const {
        return m_y;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    const T& Vector3D<T>::z() const {
        return m_z;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T> Vector3D<T>::operator+(const Vector3D<T>& v) const {
        return Vector3D<T>(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T> Vector3D<T>::operator-(const Vector3D<T>& v) const {
        return Vector3D<T>(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const T Vector3D<T>::operator*(const Vector3D<T>& v) const {
        return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T> Vector3D<T>::operator*(const T& s) const {
        return Vector3D<T>(m_x * s, m_y * s, m_z * s);
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T> Vector3D<T>::operator/(const T& s) const {
        return Vector3D<T>(m_x / s, m_y / s, m_z / s);
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T> Vector3D<T>::operator^(const Vector3D<T>& v) const {
        
        T tmpX = (m_y * v.m_z) - (m_z * v.m_y);
        T tmpY = (m_z * v.m_x) - (m_x * v.m_z);
        T tmpZ = (m_x * v.m_y) - (m_y * v.m_x);

        return Vector3D<T>(tmpX, tmpY, tmpZ);
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    
    template<typename T>
    inline const Vector3D<T>& Vector3D<T>::operator+=(const Vector3D<T>& v) {
        m_x += v.m_x;
        m_y += v.m_y;
        m_z += v.m_z;
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T>& Vector3D<T>::operator-=(const Vector3D<T>& v) {
        m_x -= v.m_x;
        m_y -= v.m_y;
        m_z -= v.m_z;
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T>& Vector3D<T>::operator*=(const T& s) {
        m_x *= s;
        m_y *= s;
        m_z *= s;
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T>& Vector3D<T>::operator/=(const T& s) {
        m_x /= s;
        m_y /= s;
        m_z /= s;
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const Vector3D<T>& Vector3D<T>::operator^=(const Vector3D<T>& v) {

        T tmpX, tmpY, tmpZ;

        tmpX = (m_y * v.m_z) - (m_z * v.m_y);
        tmpY = (m_z * v.m_x) - (m_x * v.m_z);
        tmpZ = (m_x * v.m_y) - (m_y * v.m_x);
        
        m_x = tmpX; 
        m_y = tmpY;
        m_z = tmpZ;

        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    template<typename T>
    inline void Vector3D<T>::setPosition(const T& x, const T& y, const T& z) {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    
    template<typename T>
    inline void Vector3D<T>::normalize() {

        T mag = getMagnitude();

        m_x /= mag;
        m_y /= mag;
        m_z /= mag;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    
    template<typename T>
    inline const Vector3D<T> Vector3D<T>::getNormalization() const {
        
        T mag = getMagnitude();

        T tmpX = m_x / mag;
        T tmpY = m_y / mag;
        T tmpZ = m_z / mag;

        return Vector3D<T>(tmpX, tmpY, tmpZ);
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------

    template<typename T>
    inline const T Vector3D<T>::getMagnitude() const {
        return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }


} /* Namespace Piko */

#endif // End of VECTOR3D_H
