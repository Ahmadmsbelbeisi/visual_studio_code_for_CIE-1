#include "catch.hpp"
#include "Union.hpp"
#include "Difference.hpp"
#include "Intersection.hpp"
#include "Circle.hpp"

namespace implicit
{

TEST_CASE( "Union_test" )
{ 
    ImplicitGeometryPtr circle1( new Circle( 0.0, 0.0, 1.0 ) );
    ImplicitGeometryPtr circle2( new Circle( 1.0, 0.0, 1.0 ) );
    
    Union u( circle1, circle2 );
    
    CHECK( !u.inside( 0.5,  1.0 ) );
    CHECK( !u.inside( 0.5, -1.0 ) );
    
    CHECK( !u.inside( -1.5, 0.0 ) );
    CHECK(  u.inside( -0.2, 0.0 ) );
    CHECK(  u.inside(  0.2, 0.0 ) );
    CHECK(  u.inside(  0.8, 0.0 ) );
    CHECK(  u.inside(  1.2, 0.0 ) );
    CHECK( !u.inside(  2.5, 0.0 ) );
}

TEST_CASE( "Difference_test" )
{    
    ImplicitGeometryPtr circle1( new Circle( 0.0, 0.0, 1.0 ) );
    ImplicitGeometryPtr circle2( new Circle( 1.0, 0.0, 1.0 ) );
    
    Difference difference( circle1, circle2 );
    
    CHECK( !difference.inside( 0.5,  1.0 ) );
    CHECK( !difference.inside( 0.5, -1.0 ) );
    
    CHECK( !difference.inside( -1.5, 0.0 ) );
    CHECK(  difference.inside( -0.2, 0.0 ) );
    CHECK( !difference.inside(  0.2, 0.0 ) );
    CHECK( !difference.inside(  0.8, 0.0 ) );
    CHECK( !difference.inside(  1.2, 0.0 ) );
    CHECK( !difference.inside(  2.5, 0.0 ) );
}

TEST_CASE( "Intersection_test" )
{
    ImplicitGeometryPtr circle1( new Circle( 0.0, 0.0, 1.0 ) );
    ImplicitGeometryPtr circle2( new Circle( 1.0, 0.0, 1.0 ) );
    
    Intersection intersection( circle1, circle2 );
    
    CHECK( !intersection.inside( 0.5,  1.0 ) );
    CHECK( !intersection.inside( 0.5, -1.0 ) );
    
    CHECK( !intersection.inside( -1.5, 0.0 ) );
    CHECK( !intersection.inside( -0.2, 0.0 ) );
    CHECK(  intersection.inside(  0.2, 0.0 ) );
    CHECK(  intersection.inside(  0.8, 0.0 ) );
    CHECK( !intersection.inside(  1.2, 0.0 ) );
    CHECK( !intersection.inside(  2.5, 0.0 ) );
}

} // implicit
