#include "quadtree.hpp"
#include "quadtree_helper.hpp"

#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Intersection.hpp"
#include "Union.hpp"
#include "Difference.hpp"

#include "catch.hpp"

namespace implicit
{

TEST_CASE( "subdivideCell_test" )
{
	Bounds xBounds { 2.5, 3.5 };
	Bounds yBounds { -1.0, 2.0 };

	Cell2D testCell { xBounds, yBounds };

	double xmid = 3.0;
	double ymid = 0.5;

	auto subCells = detail::subdivideCell( testCell );

	const auto& cell0 = subCells[0];

	CHECK( cell0[0][0] == Approx( xBounds[0] ) );
	CHECK( cell0[0][1] == Approx( xmid ) );

	CHECK( cell0[1][0] == Approx( yBounds[0] ) );
	CHECK( cell0[1][1] == Approx( ymid ) );

	const auto& cell1 = subCells[1];

	CHECK( cell1[0][0] == Approx( xBounds[0] ) );
	CHECK( cell1[0][1] == Approx( xmid ) );

	CHECK( cell1[1][0] == Approx( ymid ) );
	CHECK( cell1[1][1] == Approx( yBounds[1] ) );

	const auto& cell2 = subCells[2];

	CHECK( cell2[0][0] == Approx( xmid ) );
	CHECK( cell2[0][1] == Approx( xBounds[1] ) );

	CHECK( cell2[1][0] == Approx( yBounds[0] ) );
	CHECK( cell2[1][1] == Approx( ymid ) );

	const auto& cell3 = subCells[3];

	CHECK( cell3[0][0] == Approx( xmid ) );
	CHECK( cell3[0][1] == Approx( xBounds[1] ) );

	CHECK( cell3[1][0] == Approx( ymid ) );
	CHECK( cell3[1][1] == Approx( yBounds[1] ) );
}

TEST_CASE( "isCutByBoundary_test" )
{
	Circle circle( 3.0, 2.0, 4.0 );

	Cell2D cutCell { Bounds { -1.0, 1.0 }, Bounds { 3.0, 5.0 } };
	Cell2D insideCell { Bounds { 0.0, 2.0 }, Bounds { 1.0, 3.0 } };
	Cell2D outsideCell { Bounds { 6.2, 8.0 }, Bounds { -4.0, -1.2 } };

	CHECK( detail::isCutByBoundary( cutCell, circle, 3 ) == true );
	CHECK( detail::isCutByBoundary( insideCell, circle, 3 ) == false );
	CHECK( detail::isCutByBoundary( outsideCell, circle, 3 ) == false );
}

TEST_CASE( "quadtree_test" )
{
	auto circle1 = std::make_shared<implicit::Circle>( 0.0, 0.0, 1.06 );
	auto rectangle1 = std::make_shared<implicit::Rectangle>( -1.0, -1.0, 1.0, 1.0 );
	auto intersection = std::make_shared<implicit::Intersection>( circle1, rectangle1 );
	auto rectangle2 = std::make_shared<implicit::Rectangle>( -0.1, -1.5, 0.1, 1.5 );
	auto union1 = std::make_shared<implicit::Union>( intersection, rectangle2 );
	auto circle2 = std::make_shared<implicit::Circle>( 0.0, 0.0, 0.65 );
	auto geometry = std::make_shared<implicit::Difference>( union1, circle2 );

	implicit::Cell2D boundingBox { implicit::Bounds { -1.58, 1.58 },
								   implicit::Bounds { -1.58, 1.58 } };

	detail::QuadTreeNode rootNode( boundingBox, 0 );

	rootNode.partition( *geometry, 6 );

	auto leaves = rootNode.getLeafCells( );

	CHECK( leaves.first.size( ) == 856 );
	CHECK( leaves.second.size( ) == 856 );
}

} // namespace implicit
