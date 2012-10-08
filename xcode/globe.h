//
//  globe.h
//  glowingGlobe
//
//  Created by 박 성완 on 12. 8. 28..
//
//

#ifndef __glowingGlobe__Globe__
#define __glowingGlobe__Globe__

#include <iostream>
#include "cinder/Vector.h"
#include "cinder/Perlin.h"
class Globe {
   
    float       mRadius;
    ci::Vec3f   mCenter;
    int         mLats;
    int         mLongs;
    float       mFragSize;
    ci::Perlin  mPerlin;
    
    // 변화
    bool        mNoise;
    
    bool        mLive;
    bool        mAscend;
    
    bool        mFlow;
    
public: 
    Globe();
    Globe(ci::Vec3f center, float radius);
    void update();
    void draw();
    void enableNoise();
    void disableNoise();
    void toggleNoise();
    void toggleLive();
};
#endif /* defined(__glowingGlobe__Globe__) */
