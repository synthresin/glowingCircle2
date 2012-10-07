#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/Camera.h"
#include "globe.h"

#define APP_WIDTH 1280
#define APP_HEIGHT 800

using namespace ci;
using namespace ci::app;
using namespace std;



class glowingCircleApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    CameraPersp mCam;
    
    Vec3f mUp;
    Vec3f mEye;
    Vec3f mTarget;
    Globe mGlobe;
    float mXRot,mYRot,mZRot;
};

void glowingCircleApp::setup()
{
    setWindowSize(APP_WIDTH, APP_HEIGHT);
    setWindowPos(50, 50);
    
    mCam.setPerspective(100.0f, getWindowAspectRatio(), 5.0f, 2000.0f);
    
    mUp = Vec3f::yAxis();
    mEye = Vec3f(0.0, 0.0, 500.0f);
    mTarget = Vec3f::zero();
    
    
    mGlobe = Globe();

    mGlobe.disableNoise();
}

void glowingCircleApp::mouseDown( MouseEvent event )
{
}

void glowingCircleApp::keyDown( KeyEvent event )
{
    if (event.getChar() == 'a') {
        mGlobe.toggleNoise();
    }
}

void glowingCircleApp::update()
{
    mCam.lookAt(mEye, mTarget, mUp);
    gl::setMatrices(mCam);


    mXRot += 0.1;
    mYRot += 0.1;
    mZRot += 0.1;
    
    mGlobe.update();
    
}

void glowingCircleApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    //gl::drawSphere(Vec3f(0,0,0), 40.0f);
    gl::pushMatrices();
    gl::rotate(Vec3f(mXRot,mYRot,mZRot));
    mGlobe.draw();
    gl::popMatrices();
}

CINDER_APP_BASIC( glowingCircleApp, RendererGl )
