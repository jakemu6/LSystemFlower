#include "Geometry.hpp"

void Geometry::generate(const Branch branch){

    ofVboMesh bMesh;
    bMesh.setMode(OF_PRIMITIVE_LINES);


    
    ofColor Col;
    Col.r=114;
    Col.g=72;
    Col.b=50;
    
    ofVec3f start = branch.begin.getGlobalPosition();
    ofVec3f end = branch.end.getGlobalPosition();
    
    bMesh.addVertex(start);
    bMesh.addColor(Col);

    bMesh.addVertex(end);
    bMesh.addColor(Col);
    
//    ofPath path;
//
//    path.setFilled(false);
//    path.setStrokeColor(ofColor::teal);
//    path.setStrokeWidth(20.0f);
//
//    path.moveTo(start);
//    path.lineTo(end);
//    path.close();
//
//    path.draw();

    
    bMesh.draw();
}

ofMesh Geometry::generateLeaf(const Leaf leaf){
    int size = leaf.container.size();
    
    ofMesh p1Mesh;
    ofMesh p1OutlineMesh;

    p1Mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    p1OutlineMesh.setMode(OF_PRIMITIVE_LINE_LOOP);

    
    ofColor p1Col;
    p1Col.r=247;
    p1Col.g=194;
    p1Col.b=66;
    
    ofColor p1lineCol;
    p1lineCol.r=255;
    p1lineCol.g=0;
    p1lineCol.b=0;
    
    for (int i = 0; i < size; i++) {
        p1Mesh.addVertex(leaf.container[i]->getGlobalPosition());
        p1Mesh.addColor(p1Col);
        
        p1OutlineMesh.addVertex(leaf.container[i]->getGlobalPosition());
        p1OutlineMesh.addColor(p1lineCol);
    }
//    p1OutlineMesh.draw();
    return p1Mesh;
}

ofMesh Geometry::generateFlower(const Flower flower){
    int size = flower.container.size();
    
    ofMesh p2Mesh;
    ofMesh p2OutlineMesh;
    p2Mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    p2OutlineMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    

    ofColor p2Col;
    p2Col.r=251;
    p2Col.g=226;
    p2Col.b=81;
    
    ofColor p2lineCol;
    p2lineCol.r=255;
    p2lineCol.g=255;
    p2lineCol.b=0;

    for (int i = 0; i < size; i++) {
        p2Mesh.addVertex(flower.container[i]->getGlobalPosition());
        p2Mesh.addColor(p2Col);
        
        p2OutlineMesh.addVertex(flower.container[i]->getGlobalPosition());
        p2OutlineMesh.addColor(p2lineCol);
    }
//    p2OutlineMesh.draw();
    return p2Mesh;
}

