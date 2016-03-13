#ifndef _COLLINFO_H_
#define _COLLINFO_H_

class CollInfoC
{
public:
    typedef enum 
    {
        SHAPE_INVALID,
        SHAPE_CIRCLE,
        SHAPE_RECTANGLE,
        SHAPE_MAX
    }CollisionShapes;
    
    CollisionShapes shape;
    float param1;
    float param2;
};

#endif