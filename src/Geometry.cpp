#include "Geometry.hpp"

void Geometry::generate(const Branch branch, ofVboMesh& mesh){

    ofVec3f start = branch.begin.getGlobalPosition();
    ofVec3f end = branch.end.getGlobalPosition();

    mesh.addVertex(start);
    mesh.addVertex(end);

}

void Geometry::generateLeaf(const Leaf leaf, ofVboMesh& mesh){
    int size = leaf.container.size();
    
    ofVboMesh leafMesh;
    leafMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    for (int i = 0; i < size; i++) {
        leafMesh.addVertex(leaf.container[i]->getGlobalPosition());
    }
    leafMesh.draw();
}

