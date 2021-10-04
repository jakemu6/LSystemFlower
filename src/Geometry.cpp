#include "Geometry.hpp"

void Geometry::generate(const Branch branch, ofVboMesh& mesh){

    ofVec3f start = branch.begin.getGlobalPosition();
    ofVec3f end = branch.end.getGlobalPosition();
    auto numberCurrentVertices = mesh.getNumVertices();

//    int index = numberCurrentVertices/2;
//    mesh.addIndex(index);
//    mesh.addIndex(index+1);
//    if (growthRate < 1) {
//        grow = false;
//    } else {
//        grow = true;
//    }
    
//    if (grow) {
//        growthRate += 0.01;
//    }
//
//    if (growthRate > 1.0) {
//        growthRate = 0.1;
//    }
    
//    ofVec3f interpValue = start.getInterpolated(end, growthRate);
//    ofLog() << start;

    mesh.addVertex(start);
    mesh.addVertex(end);

}
