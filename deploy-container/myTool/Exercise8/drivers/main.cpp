#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Intersection.hpp"
#include "Union.hpp"
#include "Difference.hpp"
#include "quadtree.hpp"

#include <iostream>

int main( )
{
    // these two do the same thing (but the second one is slightly faster):
    // implicit::ImplicitGeometryPtr circle1( new implicit::Circle( 0.0, 0.0, 1.06 ) );
    // auto circle1 = std::make_shared<implicit::Circle>( 0.0, 0.0, 1.06 );

    auto circle1 = std::make_shared<implicit::Circle>( 0.0, 0.0, 1.06 );
    auto rectangle1 = std::make_shared<implicit::Rectangle>( -1.0, -1.0, 1.0, 1.0 );
    auto intersection = std::make_shared<implicit::Intersection>( circle1, rectangle1 );
    auto rectangle2 = std::make_shared<implicit::Rectangle>( -0.1, -1.5, 0.1, 1.5 );
    auto union1 = std::make_shared<implicit::Union>( intersection, rectangle2 );
    auto circle2 = std::make_shared<implicit::Circle>( 0.0, 0.0, 0.65 );
    auto geometry = std::make_shared<implicit::Difference>( union1, circle2 );
        
    implicit::Cell2D boundingBox { implicit::Bounds { -1.58, 1.58 },
                                   implicit::Bounds { -1.58, 1.58 } };

    implicit::generateQuadTree( *geometry, boundingBox, 7, "quadtree.vtk" );
}
