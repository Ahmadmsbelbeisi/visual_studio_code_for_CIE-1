#pragma once 

#include "AbsImplicitGeometry.hpp"

#include <memory>

namespace implicit
{

using ImplicitGeometryPtr = std::shared_ptr<AbsImplicitGeometry>;

class AbsOperation : public AbsImplicitGeometry
{
public:
    AbsOperation( const ImplicitGeometryPtr& operand1, 
                  const ImplicitGeometryPtr& operand2 );
                  
    virtual ~AbsOperation( );

protected:
    ImplicitGeometryPtr operand1_;
    ImplicitGeometryPtr operand2_;
};

} // namespace implicit

