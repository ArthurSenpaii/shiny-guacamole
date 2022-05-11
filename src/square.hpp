#ifndef VECTORS_HPP
#define VECTORS_HPP

#include "shape.hpp"

namespace SG
{
    class Square : public Shape
    {
    public:
        Square();
        Square(vec3f size, vec3f pos);
        Square(float xSize, float ySize, float zSize, float xPos, float yPos, float zPos);
        ~Square();
    

        void render();
    private:
        GLfloat* deplacer(GLfloat *vertices);

    };

}

#endif // VECTORS_HPP