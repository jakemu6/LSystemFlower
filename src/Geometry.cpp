#include "Geometry.hpp"

void Geometry::generate(const Branch branch, ofVboMesh& mesh){

    auto start = branch.begin.getGlobalPosition();
    auto end = branch.end.getGlobalPosition();
    auto numberCurrentVertices = mesh.getNumVertices();

//    int index = numberCurrentVertices/2;
//    mesh.addIndex(index);
//    mesh.addIndex(index+1);

    mesh.addVertex(start);
    mesh.addVertex(end);

}
