#pragma once 

namespace implicit
{

class AbsImplicitGeometry
{
public:
    virtual ~AbsImplicitGeometry( );
    
    virtual bool inside( double x, double y ) const = 0;
};

} // namespace implicit

