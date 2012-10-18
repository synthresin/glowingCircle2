//
//  globe
//  glowingGlobe
//
//  Created by 박 성완 on 12. 8. 28..
//
//

#include "globe.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Globe::Globe() {
    mCenter = ci::Vec3f::zero();
    mRadius = 300.0f;
    mLats = 20;
    mLongs = 30;
    mFragSize = 5.0f;
    mPerlin = Perlin();
    mNoise = true;
    mLive = true;
    mFlow = true;
    
}
Globe::Globe(ci::Vec3f center, float radius) {
    
}

void Globe::update() {
    if (mLive) {  
        if(mRadius > 500 && mAscend) {
            mAscend = false;
        } else if (mRadius < 200 && !mAscend) {
            mAscend = true;
        }
        
        if(mAscend) {
            mRadius++;
        } else {
            mRadius--;
        }
    }
}

void Globe::draw() {
    for(int i = 0; i < mLats; i++) {
        float currentLat = M_PI/2 - i * (M_PI/(mLats-1));
        float rOfCurrentLatitude = mRadius * cosf(currentLat);
        float currentY = mRadius * sinf(currentLat);
        if (mLongs <= 2) return;
        
        for(int j = 0; j < mLongs + 1; j++) {
            float currentLong = 2 * M_PI - j * (2 * M_PI/(mLongs - 1));
            float currentX = cosf(currentLong) * rOfCurrentLatitude;
            float currentZ = sinf(currentLong) * rOfCurrentLatitude;
            Vec3f locationVec = Vec3f(currentX, currentY, currentZ);
            
            if (mNoise) {
                float noise = (mPerlin.fBm(Vec3f(currentX, currentY, app::getElapsedSeconds())) + 4) / 5;
                gl::drawSphere(locationVec * noise, 5.0f);
            } else if (true) {
                gl::drawSphere(locationVec, 5.0f);
            }else {
                gl::drawSphere(locationVec, 5.0f);
            }
            
            
        }
    }
}

void Globe::enableNoise() {
    mNoise = true;
}

void Globe::disableNoise() {
    mNoise = false;
}

void Globe::toggleNoise() {
    if (mNoise) {
        mNoise = false;
    } else {
        mNoise = true;
    }
}

void Globe::toggleLive() {
    if (mLive) {
        mLive = false;
    } else {
        mLive = true;
    }
}