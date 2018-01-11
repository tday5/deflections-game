#include <cmath>
#include "ImageObject.h"

// A definition of pi
#define PI 3.14159265

using namespace std;
using namespace deflection;

ImageObject::ImageObject(unsigned int imageIndex, double x, double y,
        double width, double length, double angle) noexcept
: imageIndex_(imageIndex), cx_(x), cy_(y), width_(width), length_(length), angle_(angle) {
}

int ImageObject::getTopLeftXCoordinate() const noexcept {
    return int(cx_ - (width_ / 2.0) + 0.5);
}

int ImageObject::getTopLeftYCoordinate() const noexcept {
    return int(cy_ - (length_ / 2.0) + 0.5);
}

int ImageObject::getWidth() const noexcept {
    return int(width_);
}

int ImageObject::getLength() const noexcept {
    return int(length_);
}

int ImageObject::getImageIndex() const noexcept {
    return imageIndex_;
}

double ImageObject::getAngle() const noexcept {
    return angle_;
}

vector<pair<double, double> > ImageObject::getVertices() const noexcept {

    // Get half the width, half the length
    double halfWidth = width_ / 2.0;
    double halfLength = length_ / 2.0;
    double angle = angle_ * PI / 180.0;

    // Get the top left rotated corner
    double X1 = (((0 - halfWidth) * cos(angle)) - ((0 - halfLength) * sin(angle))) + cx_;
    double Y1 = (((0 - halfWidth) * sin(angle)) + ((0 - halfLength) * cos(angle))) + cy_;

    // Get the top right rotated corner
    double X2 = ((halfWidth * cos(angle)) - ((0 - halfLength) * sin(angle))) + cx_;
    double Y2 = ((halfWidth * sin(angle)) + ((0 - halfLength) * cos(angle))) + cy_;

    // Get the bottom right rotated corner
    double X3 = ((halfWidth * cos(angle)) - (halfLength * sin(angle))) + cx_;
    double Y3 = ((halfWidth * sin(angle)) + (halfLength * cos(angle))) + cy_;

    // Get the bottom left rotated corner
    double X4 = (((0 - halfWidth) * cos(angle)) - (halfLength * sin(angle))) + cx_;
    double Y4 = (((0 - halfWidth) * sin(angle)) + (halfLength * cos(angle))) + cy_;

    // Create a vector to add the points to
    vector<pair<double, double> > points1;
    points1.push_back(make_pair(X1, Y1));
    points1.push_back(make_pair(X2, Y2));
    points1.push_back(make_pair(X3, Y3));
    points1.push_back(make_pair(X4, Y4));

    // Return the points
    return points1;
}

double ImageObject::dotProduct(pair<double, double> one, pair<double, double> two) noexcept {
    // Multiply X1 by X2 and add it to Y1 multiplied by Y2
    return (get<0>(one) * get<0>(two)) + (get<1>(one) * get<1>(two));
}

pair<double, double> ImageObject::project(vector<pair<double, double> > points,
        pair<double, double> axis) noexcept {

    // Set the min and max to the first
    double minProj = dotProduct(points.at(0), axis);
    double maxProj = dotProduct(points.at(0), axis);

    // Iterate through points, project them, and check if the min is less, or
    // the max is more, and if so set them to that
    for (unsigned int i = 1; i < points.size(); i += 1) {
        double currProj = dotProduct(points.at(i), axis);
        if (currProj < minProj) {
            minProj = currProj;
        }

        if (currProj > maxProj) {
            maxProj = currProj;
        }
    }
    // Return the pairing of the min and the max
    return make_pair(minProj, maxProj);
}

vector<pair<double, double> > ImageObject::getAxes(vector<pair<double, double> > points1) noexcept {
    // Make a vector to hold axes
    vector<pair<double, double> > axes1;
    //Iterate through all the points, creating the axes from the normals of the points
    for (unsigned int i = 0; i < points1.size(); i += 1) {
        if (i + 1 == points1.size()) {
            // Equation for normals: get the perpendicular vector of the line
            axes1.push_back(make_pair((0 - (get<1>(points1.at(i)) - get<1>(points1.at(0)))),
                    get<0>(points1.at(i)) - get<0>(points1.at(0))));
        } else {
            axes1.push_back(make_pair((0 - (get<1>(points1.at(i)) - get<1>(points1.at(i + 1)))),
                    get<0>(points1.at(i)) - get<0>(points1.at(i + 1))));
        }
    }
    return axes1;
}

bool ImageObject::hits(const ImageObject& other) const noexcept {

    // Checks for collision using separating axis theorem,
    // which takes all axes of both polygons, projects them across the axes,
    // and if they ever do not overlap, they are not colliding

    // Get the points for this object
    vector<pair<double, double> > points1 = getVertices();

    // Get the axes for this object
    vector<pair<double, double> > axes1 = getAxes(points1);

    // Get the points for the other object
    vector<pair<double, double> > points2 = other.getVertices();

    // Get the axes for the other object
    vector<pair<double, double> > axes2 = getAxes(points2);

    // Project all points of both polygons across all axes of the first polygon
    // and check to make sure they always overlap
    for (unsigned int i = 0; i < axes1.size(); i += 1) {
        pair<double, double> P1 = project(points1, axes1.at(i));
        pair<double, double> P2 = project(points2, axes1.at(i));

        // If they ever do not overlap return false
        if (get<1>(P1) < get<0>(P2) || get<1>(P2) < get<0>(P1)) {
            return false;
        }
    }

    // Project all points of both polygons across all axes of the second polygon
    // and check to make sure they always overlap
    for (unsigned int i = 0; i < axes2.size(); i += 1) {
        pair<double, double> P1 = project(points1, axes2.at(i));
        pair<double, double> P2 = project(points2, axes2.at(i));

        // If they ever do not overlap return false
        if (get<1>(P1) < get<0>(P2) || get<1>(P2) < get<0>(P1)) {
            return false;
        }
    }

    // They must always overlap, so they collide
    return true;
}

double ImageObject::lineDistance(pair<double, double> point,
        pair<double, double> linePoint1, pair<double, double> linePoint2) noexcept {
    double X0 = get<0>(point);
    double Y0 = get<1>(point);

    double X1 = get<0>(linePoint1);
    double Y1 = get<1>(linePoint1);

    double X2 = get<0>(linePoint2);
    double Y2 = get<1>(linePoint2);

    // Equation for determining shortest distance from a point to a line
    // defined by two points
    return abs((Y2 - Y1) * X0 - (X2 - X1) * Y0 + (X2 * Y1) - (Y2 * X1)) /
            sqrt(pow(Y2 - Y1, 2) + pow(X2 - X1, 2));
}

pair<double, double> ImageObject::bounce(const ImageObject& other,
        double vx, double vy) const noexcept {
    // Get the vertices of the other object
    vector<pair<double, double> > points = other.getVertices();

    // Get the vector of this object
    pair<double, double> v = make_pair(vx, vy);

    // Get the center point of this object
    pair<double, double> center = make_pair(cx_, cy_);

    // Make variables to hold the two closest points, and set them to the first
    // to start
    pair<double, double> closest1 = points.at(0);
    pair<double, double> closest2 = points.at(1);

    // Iterate through all the points of this object, checking to see which line
    // of the other object is closest to the center point of this object
    for (unsigned int i = 1; i < points.size(); i += 1) {
        if (i + 1 == points.size()) {
            if (lineDistance(center, points.at(i), points.at(0)) <
                    lineDistance(center, closest1, closest2)) {
                // If the distance is shorter, set the points defining that line
                // to the closest two points
                closest1 = points.at(i);
                closest2 = points.at(0);
            }
        } else {
            if (lineDistance(center, points.at(i), points.at(i + 1)) <
                    lineDistance(center, closest1, closest2)) {
                // If the distance is shorter, set the points defining that line
                // to the closest two points
                closest1 = points.at(i);
                closest2 = points.at(i + 1);
            }
        }
    }

    // Get the normal of the line formed by the closest points
    pair<double, double> n = make_pair((0 - (get<1>(closest1) - get<1>(closest2))),
            get<0>(closest1) - get<0>(closest2));

    // Equation for calculating new object velocity after collision
    // with a line
    pair<double, double> u = make_pair((dotProduct(v, n) / dotProduct(n, n)) * get<0>(n),
            (dotProduct(v, n) / dotProduct(n, n)) * get<1>(n));

    pair<double, double> w = make_pair(get<0>(v) - get<0>(u), get<1>(v) - get<1>(u));

    return make_pair(get<0>(w) - get<0>(u), get<1>(w) - get<1>(u));
}
