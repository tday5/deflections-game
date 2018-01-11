#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <utility>
#include <vector>

namespace deflection {

/**
 * Represents an object with an index for its image, a position in x and y
 * coordinates, a width, a length, and an angle.
 * 
 * @author Trevor Day
 */
class ImageObject {
public:

    /**
     * Constructs a new ImageObject from the given arguments.
     * @param imageIndex is an unsigned int representing the index of the image
     * loaded in SDL that should be used when rendering this ImageObject.
     * @param x is a double representing an x coordinate.
     * @param y is a double representing a y coordinate.
     * @param width is a double representing width.
     * @param length is a double representing length.
     * @param angle is a double representing angle in degrees.
     */
    ImageObject(unsigned int imageIndex, double x, double y, double width,
            double length, double angle) noexcept;

    /**
     * The top left x coordinate of this ImageObject.
     * @return The top left x coordinate of this ImageObject.
     */
    int getTopLeftXCoordinate() const noexcept;

    /**
     * The top left y coordinate of this ImageObject.
     * @return The top left y coordinate of this ImageObject.
     */
    int getTopLeftYCoordinate() const noexcept;

    /**
     * Returns the width of this ImageObject.
     * @return an int representing width of this ImageObject.
     */
    int getWidth() const noexcept;

    /**
     * Returns the length of this ImageObject.
     * @return an int representing the length of this ImageObject.
     */
    int getLength() const noexcept;

    /**
     * Get the image index of this ImageObject.
     * @return the index of the image to use for this ImageObject.
     */
    int getImageIndex() const noexcept;

    /**
     * The angle of this ImageObject.
     * @return a double representing the angle of this ImageObject in degrees.
     */
    double getAngle() const noexcept;

    /**
     * Returns a vector of pairs of doubles, with the first representing the x coordinate
     * and the second representing the y coordinate, representing the vertices of this
     * ImageObject.
     * @return the vertices of this ImageObject.
     */
    std::vector<std::pair<double, double> > getVertices() const noexcept;

    /**
     * Determines whether this ImageObject collides with the given ImageObject,
     * using the separating axis theorem.
     * @param other is the ImageObject to check for collision.
     * @return true if the other ImageObject is colliding with this one, false otherwise.
     */
    bool hits(const ImageObject& other) const noexcept;

    /**
     * Returns a pair of doubles, with the first representing the x vector, and
     * the second representing the y vector, which represents the vector that
     * this ImageObject should travel after hitting the given ImageObject other.
     * The given ImageObject is treated as static, and this ImageObject is assumed
     * to be traveling along the given vector vx and vy.
     * @param other is the ImageObject to bounce this ImageObject off of.
     * @param vx is the x vector that this ImageObject is assumed to be traveling
     * at.
     * @param vy is the y vector that this ImageObject is assumed to be traveling
     * at.
     * @return a pair of doubles.
     */
    std::pair<double, double> bounce(const ImageObject& other, double vx, double vy) const noexcept;

    /**
     * A static method on ImageObjects which computes the dot product of the given
     * points. The first in the pairs represents the x value, and the second
     * represents the y value.
     * @param one is the first point.
     * @param two is the second point.
     * @return a double representing the result of the dot product of the two
     * given points.
     */
    static double dotProduct(std::pair<double, double> one, std::pair<double, double> two) noexcept;

    /**
     * A static method which returns a pair of doubles which represents the min and max after projecting
     * the given vector of points across the given axis. The first represents
     * the min, and the second represents the max.
     * @param points is the vector of pairs of doubles which should be projected
     * across the axis. The first in the pairs represents the x value, and the
     * second represents the y value.
     * @param axis is the pair of doubles representing the axis that the points
     * should be projected across.
     * @return a pair of doubles.
     */
    static std::pair<double, double> project(
            std::vector<std::pair<double, double> > points, std::pair<double, double> axis) noexcept;

    /**
     * A static method which returns the axes of the given vector of points. Axes are retrieved by
     * taking the normals of each side, and sides are defined by two adjacent points
     * in the given vector.
     * @param points1 is the vector of pairs of doubles representing points to
     * get the axes of.
     * @return a vector of pairs of doubles representing the axes of the given
     * vector of points.
     */
    static std::vector<std::pair<double, double> > getAxes(
            std::vector<std::pair<double, double> > points1) noexcept;

    /**
     * A static method which returns the smallest distance between the given
     * point and the line defined by the two given line points.
     * @param point is a pair of doubles representing x and y values.
     * @param linePoint1 is a pair of doubles representing the first point of the line.
     * @param linePoint2 is a pair of doubles representing the second point of the line.
     * @return a double representing the smallest distance.
     */
    static double lineDistance(std::pair<double, double> point,
            std::pair<double, double> linePoint1, std::pair<double, double> linePoint2) noexcept;

protected:

    /** The width of this ImageObject. */
    int width_ = 1.0;

    /** The length of this ImageObject. */
    int length_ = 1.0;

    /** Index of the image to use for this ImageObject. */
    unsigned int imageIndex_ = 0;

    /** The current x-coordinate of the center of this ImageObject. */
    double cx_ = 0.0;

    /** The current y-coordinate of the center of this ImageObject. */
    double cy_ = 0.0;

    /** The angle, in degrees, of this ImageObject. */
    double angle_ = 0.0;
};
}


#endif /* IMAGEOBJECT_H */
