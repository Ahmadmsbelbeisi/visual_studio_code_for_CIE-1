#pragma once

#include "AbsOperation.hpp"

namespace implicit
{

class Union : public AbsOperation
{
public:
    Union( const ImplicitGeometryPtr& operand1, const ImplicitGeometryPtr& operand2 );

    virtual bool inside( double x, double y ) const;
};

} // namespace implicit
