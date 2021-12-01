#include "Difference.hpp"

namespace implicit
{

Difference::Difference( const ImplicitGeometryPtr& operand1, const ImplicitGeometryPtr& operand2 ) :
    AbsOperation( operand1, operand2 )
{
}

bool Difference::inside( double x, double y ) const
{
    return operand1_->inside( x, y ) && !operand2_->inside( x, y );
}

} // namespace implicit
