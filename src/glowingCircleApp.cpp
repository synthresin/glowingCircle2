#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
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
    
    //Perspective variables
    float mFov, mRatio, mNear, mFar;
    
    float mUpX, mUpY, mUpZ;
    float mEyeX, mEyeY, mEyeZ;
    float mTargetX, mTargetY, mTargetZ;
    float mXRot,mYRot,mZRot;
    
    Globe mGlobe;
    
    params::InterfaceGl mParams;
};

void glowingCircleApp::setup()
{
    // set up Perspective variables
    mFov = 100.0f;
    mRatio = getWindowAspectRatio();
    mNear = 5.0f;
    mFar = 2000.0f;
    
    //mUp Variables
    mUpX = 0.0f;
    mUpY = 1.0f;
    mUpZ = 0.0f;
    
    //mEye variables
    
    mEyeX = 0.0f;
    mEyeY = 0.0f;
    mEyeZ = 500.0f;
    
    
    //mTarget variables
    mTargetX = 0.0f;
    mTargetY = 0.0f;
    mTargetZ = 0.0f;
    
    
    setWindowSize(APP_WIDTH, APP_HEIGHT);
    setWindowPos(50, 50);
    
    
    
//    mUp = Vec3f::yAxis();
//    mEye = Vec3f(0.0, 0.0, 500.0f);
//    mTarget = Vec3f::zero();
    
    // SETUPS PARAMS
	mParams = params::InterfaceGl( "Flocking", Vec2i( 200, 240 ) );
	mParams.addSeparator();
    mParams.addParam( "Fov", &mFov, "min=50.0 max=140.0 step=5.0 keyIncr=z keyDecr=Z" );
    
    
    
    
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
    mCam.setPerspective(mFov, mRatio, mNear, mFar);
    mUp = Vec3f(mUpX,mUpY,mUpZ);
    mEye = Vec3f(mEyeX, mEyeY, mEyeZ);
    mTarget = Vec3f(mTargetX, mTargetY, mTargetZ);
    
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
    params::InterfaceGl::draw();
}

CINDER_APP_BASIC( glowingCircleApp, RendererGl )
