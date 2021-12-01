#pragma once

#include "quadtree.hpp"

#include <vector>
#include <tuple>

namespace implicit
{
namespace detail
{

using CellsAndLevels = std::pair<std::vector<Cell2D>, 
	                             std::vector<unsigned int>>;

std::array<Cell2D, 4> subdivideCell( Cell2D cell );

bool isCutByBoundary( Cell2D cell,
					  const AbsImplicitGeometry& geometry,
					  int numberOfSeedPoints );

class QuadTreeNode
{
public:
	QuadTreeNode( Cell2D cell, int level );

	void partition( const AbsImplicitGeometry& geometry, int maxDepth );

	CellsAndLevels getLeafCells( ) const;

private:
	void getLeafCellsRecursive( CellsAndLevels& data ) const;

	std::vector<QuadTreeNode> children_;

	Cell2D cell_;
	int level_;
};

} // namespace detail
} // namespace implicit