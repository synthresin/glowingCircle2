#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/qtime/MovieWriter.h"
#include "cinder/Utilities.h"
#include "cinder/gl/Fbo.h"
#include "globe.h"

#define APP_WIDTH 1920
#define APP_HEIGHT 1080

using namespace ci;
using namespace ci::app;
using namespace std;



class glowingCircleApp : public AppBasic {
  public:
    void prepareSettings(Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
    void renderSceneToFbo();
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
    
    qtime::MovieWriter mMovie;
    bool    mSaveFrame;
    
    gl::Fbo     mFbo;
};

void glowingCircleApp::prepareSettings(Settings *settings)
{
    settings->setWindowSize(APP_WIDTH, APP_HEIGHT);
}

void glowingCircleApp::setup()
{
    // set up Perspective variables
    mFov = 70.0f;
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
    
    
    setWindowPos(50, 50);
    
    
    
//    mUp = Vec3f::yAxis();
//    mEye = Vec3f(0.0, 0.0, 500.0f);
//    mTarget = Vec3f::zero();
    
    // SETUPS PARAMS
	mParams = params::InterfaceGl( "Circle", Vec2i( 200, 240 ) );
	mParams.addSeparator();
    mParams.addParam( "Fov", &mFov, "min=50.0 max=140.0 step=5.0 keyIncr=z keyDecr=Z" );
    mParams.addParam( "eye x", &mEyeX, "min=-500.0 max=500.0 step=10.0 keyIncr=c keyDecr=C" );
    mParams.addParam( "eye y", &mEyeY, "min=-500.0 max=500.0 step=10.0 keyIncr=v keyDecr=V" );
    mParams.addParam( "eye z", &mEyeZ, "min=-500.0 max=500.0 step=10.0 keyIncr=b keyDecr=B" );
    mParams.addSeparator();
    mParams.addParam( "target x", &mTargetX, "min=-500.0 max=500.0 step=10.0 keyIncr=d keyDecr=D" );
    mParams.addParam( "target y", &mTargetY, "min=-500.0 max=500.0 step=10.0 keyIncr=f keyDecr=F" );
    mParams.addParam( "target z", &mTargetZ, "min=-500.0 max=500.0 step=10.0 keyIncr=g keyDecr=G" );
    
    
    
    mGlobe = Globe();

    mGlobe.disableNoise();
    //fs::path path = getSaveFilePath();
    //mMovie = qtime::MovieWriter(path, 640, 480);
    mSaveFrame = false;
    
    gl::enableAlphaBlending();
    mFbo = gl::Fbo( APP_WIDTH, APP_HEIGHT );
}

void glowingCircleApp::mouseDown( MouseEvent event )
{
}

void glowingCircleApp::keyDown( KeyEvent event )
{
    if (event.getChar() == 'a') {
        //mGlobe.toggleNoise();
        setWindowSize(APP_WIDTH, APP_HEIGHT);
    } else if (event.getChar() == 'q') {
        if (mSaveFrame) {
            mSaveFrame = false;
        } else {
            mSaveFrame = true;
        }
    }
}

void glowingCircleApp::renderSceneToFbo()
{
    mFbo.bindFramebuffer();
    gl::setViewport( mFbo.getBounds() );
    CameraPersp cam( mFbo.getWidth(), mFbo.getHeight(), 60.0f );
    cam.setPerspective(mFov, mRatio, mNear, mFar);
    cam.lookAt(mEye, mTarget, mUp);
    gl::setMatrices( cam );
    gl::clear( ColorA( 0, 0, 0, 0 ) );
    glDisable( GL_TEXTURE_2D );
    gl::pushMatrices();
    gl::rotate(Vec3f(mXRot,mYRot,mZRot));
    mGlobe.draw();
    gl::popMatrices();
    
    mFbo.unbindFramebuffer();
}

void glowingCircleApp::update()
{
    mCam.setPerspective(mFov, mRatio, mNear, mFar);
    mUp = Vec3f(mUpX,mUpY,mUpZ);
    mEye = Vec3f(mEyeX, mEyeY, mEyeZ);
    mTarget = Vec3f(mTargetX, mTargetY, mTargetZ);
    
    mCam.lookAt(mEye, mTarget, mUp);
    //gl::setMatrices(mCam);


    mXRot += 0.1;
    mYRot += 0.1;
    mZRot += 0.1;
    
    
    mGlobe.update();
    
    renderSceneToFbo();
    
}

void glowingCircleApp::draw()
{
	// clear out the window with black
	
    gl::clear( ColorA( 1, 0, 0 ) );
    //gl::drawSphere(Vec3f(0,0,0), 40.0f);
    
//    gl::pushMatrices();
//    gl::rotate(Vec3f(mXRot,mYRot,mZRot));
//    mGlobe.draw();
//    gl::popMatrices();
    
    glEnable( GL_TEXTURE_2D );
	//mFbo.bindTexture();
    
    gl::draw( mFbo.getTexture() );
    
    //params::InterfaceGl::draw();
    
    //mMovie.addFrame( copyWindowSurface() );
//    if(mSaveFrame) {
//        writeImage( getHomeDirectory().string() + "/myImage/image_" + toString( getElapsedFrames() ) + ".png",
//                   copyWindowSurface() );
//    }
    
    if(mSaveFrame) {
        writeImage( getHomeDirectory().string() + "/myImage/image_" + toString( getElapsedFrames() ) + ".png",
                   mFbo.getTexture() );
    }
}

CINDER_APP_BASIC( glowingCircleApp, RendererGl )
