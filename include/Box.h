///
/// A 2-d bounding box
///

#pragma once

#include "Vector.h"

namespace df {

class Box {

 private:
  Vector corner;           ///< Upper left corner of box.
  float horizontal;	   ///< Horizontal dimension.
  float vertical;	   ///< Vertical dimension.

 public:
  /// Create box with upper-left corner, horiz and vert sizes.
  Box(Vector init_corner, float init_horizontal, float init_vertical);

  /// Create box with (0,0) for corner, and 0 for horiz and vert.
  Box();

  /// Set upper left corner of box.
  void setCorner(Vector new_corner);

  /// Get upper left corner of box.
  Vector getCorner() const;

  /// Set horizontal size of box.
  void setHorizontal(float new_horizontal);

  /// Get horizontal size of box.
  float getHorizontal() const;

  /// Set vertical size of box.
  void setVertical(float new_vertical);

  /// Get vertical size of box.
  float getVertical() const;

  bool operator==(const Box &other) const; ///< Compare boxes.
  bool operator!=(const Box &other) const; ///< Compare boxes.
};

} // end of namespace df
