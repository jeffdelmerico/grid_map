/*
 * Polygon.hpp
 *
 *  Created on: Nov 7, 2014
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

#include <grid_map_core/TypeDefs.hpp>

// STD
#include <vector>

// Eigen
#include <Eigen/Core>

namespace grid_map {

class Polygon
{
 public:

  /*!
   * Default constructor.
   */
  Polygon();

  /*!
   * Constructor with vertices.
   * @param vertices the points of the polygon.
   */
  Polygon(std::vector<Position> vertices);

  /*!
   * Destructor.
   */
  virtual ~Polygon();

  /*!
   * Check if point is inside polygon.
   * @param point the point to be checked.
   * @return true if inside, false otherwise.
   */
  bool isInside(const Position& point);

  /*!
   * Add a vertex to the polygon
   * @param vertex the point to be added.
   */
  void addVertex(const Position& vertex);

  /*!
   * Get the vertex with index.
   * @param index the index of the requested vertex.
   * @return the requested vertex.
   */
  const Position& getVertex(const size_t index) const;

  /*!
   * Removes all vertices from the polygon.
   */
  void removeVertices();

  /*!
   * Get vertex operator overload.
   * @param index the index of the requested vertex.
   * @return the requested vertex.
   */
  const Position& operator [](const size_t index) const;

  /*!
   * Returns the vertices of the polygon.
   * @return the vertices of the polygon.
   */
  const std::vector<Position>& getVertices() const;

  /*!
   * Returns the number of vertices.
   * @return the number of vertices.
   */
  const size_t nVertices() const;

  /*!
   * Set the timestamp of the polygon.
   * @param timestamp the timestamp to set (in  nanoseconds).
   */
  void setTimestamp(const uint64_t timestamp);

  /*!
   * Get the timestamp of the polygon.
   * @return timestamp in nanoseconds.
   */
  uint64_t getTimestamp() const;

  /*!
   * Resets the timestamp of the polygon (to zero).
   */
  void resetTimestamp();

  /*!
   * Set the frame id of the polygon.
   * @param frameId the frame id to set.
   */
  void setFrameId(const std::string& frameId);

  /*!
   * Get the frameId of the polygon.
   * @return frameId.
   */
  const std::string& getFrameId() const;

  /*!
   * Get the area of the polygon. The polygon has to be
   * "simple", i.e. not crossing itself.
   * @return area of the polygon.
   */
  const double getArea() const;

  /*!
   * Computes the convex hull of two polygons and returns it as polygon.
   * @param[in] polygon1 the first input polygon.
   * @param[in] polygon2 the second input polygon.
   * @return convex hull as Polygon.
   */
  Polygon convexHull(Polygon& polygon1, Polygon& polygon2);

  /*!
   * Approximates the convex hull of two circles and returns it as polygon.
   * @param[in] center1 the center position of the first circle.
   * @param[in] center2 the center position of the second circle.
   * @param[in] radius radius of the circles.
   * @param[in] nVertices number of vertices of the approximation polygon. Default = 20.
   * @return convex hull as Polygon.
   */
  Polygon convexHullCircles(const Position center1, const Position center2, const double radius, const int nVertices = 20);

  /*!
   * Approximates a circle with a convex hull polygon.
   * @param[in] center the center position of the circle.
   * @param[in] radius radius of the circle.
   * @param[in] nVertices number of vertices of the approximation polygon. Default = 20.
   * @return convex hull as Polygon.
   */
  Polygon convexHullCircle(const Position center, const double radius, const int nVertices = 20);

  /*!
   * Convert polygon to inequality constraints which most tightly contain the points; i.e.,
   * create constraints to bound the convex hull of polygon. The inequality constraints are
   * represented as A and b, a set of constraints such that A*x <= b defining the region of
   * space enclosing the convex hull.
   * Based on the VERT2CON MATLAB method by Michael Kleder:
   * http://www.mathworks.com/matlabcentral/fileexchange/7895-vert2con-vertices-to-constraints
   * @param A the A matrix in of the inequality constraint.
   * @param b the b matrix in of the inequality constraint.
   * @return true if conversion successful, false otherwise.
   */
  bool convertToInequalityConstraints(Eigen::MatrixXd& A, Eigen::VectorXd& b);

  /*!
   * Offsets the polygon inward (buffering) by a margin.
   * Use a negative margin to offset the polygon outward.
   * @param margin the margin to offset the polygon by (in [m]).
   * @return true if succesful, false otherwise.
   */
  bool offsetInward(const double margin);

 protected:

  /*!
   * Returns true if the vector1 and vector2 are sorted lexicographically.
   * @param[in] vector1 the first input vector.
   * @param[in] vector2 the second input vector.
   */
  static bool sortVertices(const Eigen::Vector2d& vector1,
                           const Eigen::Vector2d& vector2);

  /*!
   * Returns the 2D cross product of vector1 and vector2.
   * @param[in] vector1 the first input vector.
   * @param[in] vector2 the second input vector.
   */
  double computeCrossProduct2D(const Eigen::Vector2d& vector1,
                               const Eigen::Vector2d& vector2);

  //! Frame id of the polygon.
  std::string frameId_;

  //! Timestamp of the polygon (nanoseconds).
  uint64_t timestamp_;

  //! Vertices of the polygon.
  std::vector<Position> vertices_;
};

} /* namespace grid_map */
