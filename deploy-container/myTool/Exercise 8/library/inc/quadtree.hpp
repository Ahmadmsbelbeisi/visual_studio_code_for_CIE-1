#pragma once

#include <array>
#include <string>

namespace implicit
{

using Bounds = std::array<double, 2>;
using Cell2D = std::array<Bounds, 2>;

class AbsImplicitGeometry;

void generateQuadTree( const AbsImplicitGeometry& geometry,
					   Cell2D boundingBox,
					   int maxDepth,
					   const std::string& filename );

} // namespace implicit