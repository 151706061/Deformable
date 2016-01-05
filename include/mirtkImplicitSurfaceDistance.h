/*
 * Medical Image Registration ToolKit (MIRTK)
 *
 * Copyright 2013-2015 Imperial College London
 * Copyright 2013-2015 Andreas Schuh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MIRTK_ImplicitSurfaceDistance_H
#define MIRTK_ImplicitSurfaceDistance_H

#include <mirtkImplicitSurfaceForce.h>


namespace mirtk {


/**
 * Force attracting the surface towards a given implicit surface / object boundary
 *
 * This force term is similar to an BalloonForce with the implicit surface
 * model given as input image. Unlike the balloon force, however, this force
 * does not vanish for a node which is close to the implicit surface. A separate
 * image edge force which takes over once a vertex is nearby an image edge is
 * therefore not required. Moreover, the force vectors can be scaled by the
 * estimated distance of a point to the given implicit surface. Points which are
 * further away, thus move faster. When a point lies on the implicit surface,
 * its force vanishes. As soon as it is displaced again, e.g., by a smoothness
 * therm, it starts pulling the point back to the implicit surface again.
 *
 * The input _Image of the force term is the discrete distance function of the
 * implicit surface, e.g., a signed Euclidean distance transform of a binary
 * object mask.
 */
class ImplicitSurfaceDistance : public ImplicitSurfaceForce
{
  mirtkEnergyTermMacro(ImplicitSurfaceDistance, EM_ImplicitSurfaceDistance);

  // ---------------------------------------------------------------------------
  // Construction/Destruction
public:

  /// Constructor
  ImplicitSurfaceDistance(const char * = "", double = 1.0);

  /// Copy constructor
  ImplicitSurfaceDistance(const ImplicitSurfaceDistance &);

  /// Assignment operator
  ImplicitSurfaceDistance &operator =(const ImplicitSurfaceDistance &);

  /// Destructor
  virtual ~ImplicitSurfaceDistance();

  /// Initialize force term once input and parameters have been set
  virtual void Initialize();

  // ---------------------------------------------------------------------------
  // Evaluation

  /// Update moving input points and internal state of force term
  virtual void Update(bool = true);

protected:

  /// Evaluate external force term
  virtual double Evaluate();

  /// Evaluate external force
  virtual void EvaluateGradient(double *, double, double);

};


} // namespace mirtk

#endif // MIRTK_ImplicitSurfaceDistance_H