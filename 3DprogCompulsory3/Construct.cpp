#include "Construct.h"

std::array<Vertex, 36> Construct::Cube(glm::vec3 Color)
{
    std::array<Vertex, 36> CubeArray;
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // Vertices for the front face
    Vertex v0 { -sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v1 {  sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v2 {  sizeXYZ.x,  sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v3 { -sizeXYZ.x,  sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Vertices for the right face
    Vertex v4 { sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v5 { sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v6 { sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7 { sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Vertices for the back face
    Vertex v8 {  sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v9 { -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v10{ -sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v11{  sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Vertices for the left face
    Vertex v12{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v13{ -sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v14{ -sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v15{ -sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Vertices for the top face
    Vertex v16{ -sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v17{  sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v18{  sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v19{ -sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Vertices for the bottom face
    Vertex v20{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v21{  sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v22{  sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v23{ -sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Assign the vertices to CubeArray
    // Vertices for the front face
    CubeArray[0]  = v0;
    CubeArray[1]  = v1;
    CubeArray[2]  = v2;
    CubeArray[3]  = v2;
    CubeArray[4]  = v3;
    CubeArray[5]  = v0;

    // Vertices for the right face
    CubeArray[6]  = v4;
    CubeArray[7]  = v5;
    CubeArray[8]  = v6;
    CubeArray[9]  = v6;
    CubeArray[10] = v7;
    CubeArray[11] = v4;

    // Vertices for the back face
    CubeArray[12] = v8;
    CubeArray[13] = v9;
    CubeArray[14] = v10;
    CubeArray[15] = v10;
    CubeArray[16] = v11;
    CubeArray[17] = v8;

    // Vertices for the left face
    CubeArray[18] = v12;
    CubeArray[19] = v13;
    CubeArray[20] = v14;
    CubeArray[21] = v14;
    CubeArray[22] = v15;
    CubeArray[23] = v12;

    // Vertices for the top face
    CubeArray[24] = v16;
    CubeArray[25] = v17;
    CubeArray[26] = v18;
    CubeArray[27] = v18;
    CubeArray[28] = v19;
    CubeArray[29] = v16;

    // Vertices for the bottom face
    CubeArray[30] = v20;
    CubeArray[31] = v21;
    CubeArray[32] = v22;
    CubeArray[33] = v22;
    CubeArray[34] = v23;
    CubeArray[35] = v20;

    return CubeArray;
}

std::array<Vertex, 6> Construct::Surface(glm::vec3 Color, glm::vec3 PointPosition)
{
    std::array<Vertex, 6> PlaneArray;
    glm::vec3 sizeXYZ = glm::vec3(1.0f, 1.0f, 1.0f);
   
    Vertex v2{  sizeXYZ.x, sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v3{ -sizeXYZ.x, sizeXYZ.y,  sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v6{  sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 0.0f };

    
    v6.y += 0.5;
    v2.y += 0.5;
    v7.y += 1.0;
    PlaneArray[0] = v3;
    PlaneArray[1] = v2;
    PlaneArray[2] = v6;
    PlaneArray[3] = v6;
    PlaneArray[4] = v7;
    PlaneArray[5] = v3;

    return PlaneArray;
}