#include "Geometry.hpp"

void Geometry::generate(const Branch branch, ofVboMesh& mesh){

    ofVec3f start = branch.begin.getGlobalPosition();
    ofVec3f end = branch.end.getGlobalPosition();

    mesh.addVertex(start);
    mesh.addVertex(end);

}

void Geometry::generateLeaf(const Leaf leaf){
    int size = leaf.container.size();
    
    ofVboMesh leafMesh;
    ofVboMesh leafOutlineMesh;

    leafMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    leafOutlineMesh.setMode(OF_PRIMITIVE_LINES);

    
    ofColor leafCol;
    leafCol.r=131;
    leafCol.g=138;
    leafCol.b=45;
    
    ofColor lineCol;
    lineCol.r=190;
    lineCol.g=194;
    lineCol.b=63;

    for (int i = 0; i < size; i++) {
        leafMesh.addVertex(leaf.container[i]->getGlobalPosition());
        leafMesh.addColor(leafCol);
        
        leafOutlineMesh.addVertex(leaf.container[i]->getGlobalPosition());
        leafOutlineMesh.addColor(lineCol);
    }
    
//    ofSetColor(131, 138, 45, 255);
//    ofNoFill();


    leafMesh.draw();
    leafOutlineMesh.draw();

    ofSetColor(150, 114, 73, 255);
}

void Geometry::generateFlower(const Flower flower){
    int size = flower.container.size();
    
    ofVboMesh flowerMesh;
    flowerMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    for (int i = 0; i < size; i++) {
        flowerMesh.addVertex(flower.container[i]->getGlobalPosition());
    }
    
    ofSetColor(251, 226, 81, 255);
    ofFill();
    flowerMesh.draw();
    ofSetColor(150, 114, 73, 255);
}

