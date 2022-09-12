#include "Geometry.hpp"

void Geometry::setup(){



}

void Geometry::setBranchColor(ofColor & Col){
    branchColor = Col;
}
void Geometry::setP1Color(ofColor & Col){
    p1Color = Col;
}
void Geometry::setP2Color(ofColor & Col){
    p2Color = Col;
}

void Geometry::generate(const Branch & branch){


    ofVboMesh bMesh;
    bMesh.setMode(OF_PRIMITIVE_LINES);
    
    ofVec3f start = branch.begin.getGlobalPosition();
    ofVec3f end = branch.end.getGlobalPosition();
    
    bMesh.addVertex(start);
    bMesh.addColor(branchColor);

    bMesh.addVertex(end);
    bMesh.addColor(branchColor);
        
    bMesh.draw();

}

void Geometry::generateLeaf(const Leaf & leaf){

    int size = leaf.container.size();
    
    ofVboMesh p1Mesh;
    p1Mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    for (int i = 0; i < size; i++) {
        p1Mesh.addVertex(leaf.container[i]->getGlobalPosition());
        p1Mesh.addColor(p1Color);
    }
    
    p1Mesh.draw();

}

void Geometry::generateFlower(const Flower & flower){
    int size = flower.container.size();
    
    ofVboMesh p2Mesh;
    p2Mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    for (int i = 0; i < size; i++) {
        p2Mesh.addVertex(flower.container[i]->getGlobalPosition());
        p2Mesh.addColor(p2Color);
    }
    p2Mesh.draw();
}

