#include "quadtree.hpp"
#include "quadtree_helper.hpp"

#include "AbsImplicitGeometry.hpp"

#include <fstream>

namespace implicit
{
namespace detail
{

std::array<Cell2D, 4> subdivideCell( Cell2D cell )
{
	double xmin = cell[0][0];
	double xmax = cell[0][1];

	double ymin = cell[1][0];
	double ymax = cell[1][1];

	double xmid = 0.5 * ( xmin + xmax );
	double ymid = 0.5 * ( ymin + ymax );

	Bounds xBounds0 { xmin, xmid };
	Bounds xBounds1 { xmid, xmax };

	Bounds yBounds0 { ymin, ymid };
	Bounds yBounds1 { ymid, ymax };

	Cell2D cell0 { xBounds0, yBounds0 };
	Cell2D cell1 { xBounds0, yBounds1 };
	Cell2D cell2 { xBounds1, yBounds0 };
	Cell2D cell3 { xBounds1, yBounds1 };

	return { cell0, cell1, cell2, cell3 };
}

bool isCutByBoundary( Cell2D cell,
					  const AbsImplicitGeometry& geometry,
					  int numberOfSeedPoints )
{
	double xmin = cell[0][0];
	double xmax = cell[0][1];

	double ymin = cell[1][0];
	double ymax = cell[1][1];

	int count = 0;

	for( int i = 0; i < numberOfSeedPoints; ++i )
	{
		for( int j = 0; j < numberOfSeedPoints; ++j )
		{
			double x = i / ( numberOfSeedPoints - 1.0 ) * ( xmax - xmin ) + xmin;
			double y = j / ( numberOfSeedPoints - 1.0 ) * ( ymax - ymin ) + ymin;

			count += geometry.inside( x, y );
		}
	}

	return count != 0 && count != numberOfSeedPoints * numberOfSeedPoints;
}

void writeCellsToVtkFile( const CellsAndLevels& data, std::string filename )
{
	// For convenience. Use const& to prevent creating copies
	const auto& cells = data.first;
	const auto& levels = data.second;

	size_t numberOfCells = cells.size( );

	std::ofstream outfile;

	outfile.open( filename );

	outfile << "# vtk DataFile Version 4.2" << std::endl;
	outfile << "Test Data                 " << std::endl;
	outfile << "ASCII                     " << std::endl;
	outfile << "DATASET UNSTRUCTURED_GRID " << std::endl;

	outfile << "POINTS " << 4 * numberOfCells << " " << "double " << std::endl;

	for( unsigned int i = 0; i < numberOfCells; ++i )
	{
		outfile << cells[i][0][0] << "\t" << cells[i][1][0] << "\t" << "0" << std::endl;
		outfile << cells[i][0][1] << "\t" << cells[i][1][0] << "\t" << "0" << std::endl;
		outfile << cells[i][0][1] << "\t" << cells[i][1][1] << "\t" << "0" << std::endl;
		outfile << cells[i][0][0] << "\t" << cells[i][1][1] << "\t" << "0" << std::endl;
	}

	outfile << "CELLS " << numberOfCells << " " << 5 * numberOfCells << std::endl;

	for( unsigned int i = 0; i < numberOfCells * 4; i += 4 )
	{
		outfile << "4\t" << i << "\t" << i + 1 << "\t" << i + 2 << "\t" << i + 3 << std::endl;
	}

	outfile << "CELL_TYPES " << numberOfCells << std::endl;

	for( unsigned int i = 0; i < numberOfCells; i++ )
	{
		outfile << "9" << std::endl;
	}

	outfile << "CELL_DATA " << numberOfCells << std::endl;
	outfile << "SCALARS depth double" << std::endl;
	outfile << "LOOKUP_TABLE default" << std::endl;

	for( unsigned int i = 0; i < numberOfCells; i++ )
	{
		outfile << levels[i] << std::endl;
	}

	outfile.close( );
}

QuadTreeNode::QuadTreeNode( Cell2D cell, int level ) :
	cell_( cell ), level_( level )
{ }

void QuadTreeNode::partition( const AbsImplicitGeometry& geometry, int maxDepth )
{
	int numberOfSeedPoints = 7;

	if( level_ < maxDepth )
	{
		if( isCutByBoundary( cell_, geometry, numberOfSeedPoints ) )
		{
			auto subCells = subdivideCell( cell_ );

			children_.reserve( 4 );

			for( int i = 0; i < 4; ++i )
			{
				children_.emplace_back( subCells[i], level_ + 1 );

				children_[i].partition( geometry, maxDepth );
			}
		}
	}
}


CellsAndLevels QuadTreeNode::getLeafCells( ) const
{
	CellsAndLevels data;

	getLeafCellsRecursive( data );

	return data;
}

void QuadTreeNode::getLeafCellsRecursive( CellsAndLevels& data ) const
{
	// If leaf
	if( children_.empty( ) )
	{
		data.first.push_back( cell_ );
		data.second.push_back( level_ );
	}
	else
	{
		for( int i = 0; i < 4; ++i )
		{
			children_[i].getLeafCellsRecursive( data );
		}
	}
}

} // namespace detail

void generateQuadTree( const AbsImplicitGeometry& geometry,
					   Cell2D boundingBox,
					   int maxDepth,
					   const std::string& filename )
{
	detail::QuadTreeNode rootNode( boundingBox, 0 );

	rootNode.partition( geometry, maxDepth );

	auto leaves = rootNode.getLeafCells( );

	detail::writeCellsToVtkFile( leaves, filename );
}

} // namespace implicit