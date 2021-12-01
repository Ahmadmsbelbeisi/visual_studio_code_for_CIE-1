#include "AbsOperation.hpp"

namespace implicit
{

AbsOperation::AbsOperation( const ImplicitGeometryPtr& operand1, const ImplicitGeometryPtr& operand2 ) :
    operand1_( operand1 ), operand2_( operand2 )
{
}

AbsOperation::~AbsOperation( )
{
}

} // namespace implicit
