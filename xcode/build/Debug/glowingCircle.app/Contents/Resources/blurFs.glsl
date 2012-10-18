uniform float sigma; // 가우스 함수에 필요한 시그마 밸류, 블러 값을 조절
uniform float blurSize; // 일반적으로 가로블러 1.0f / texture_pixel_width
                        // 세로블러 1.0f / texture_pixel_height

uniform sampler2D blurSampler; // 텍스쳐는 이 셰이더에 의하여 블러가 된당.


const float pi = 3.14159265f;





#if defined(VERTICAL_BLUR_9)
const float numBlurPixelsPerSide = 4.0f;
const vec2  blurMultiplyVec      = vec2(0.0f, 1.0f);
#elif defined(HORIZONTAL_BLUR_9)
const float numBlurPixelsPerSide = 4.0f;
const vec2  blurMultiplyVec      = vec2(1.0f, 0.0f);
#elif defined(VERTICAL_BLUR_7)
const float numBlurPixelsPerSide = 3.0f;
const vec2  blurMultiplyVec      = vec2(0.0f, 1.0f);
#elif defined(HORIZONTAL_BLUR_7)
const float numBlurPixelsPerSide = 3.0f;
const vec2  blurMultiplyVec      = vec2(1.0f, 0.0f);
#elif defined(VERTICAL_BLUR_5)
const float numBlurPixelsPerSide = 2.0f;
const vec2  blurMultiplyVec      = vec2(0.0f, 1.0f);
#elif defined(HORIZONTAL_BLUR_5)
const float numBlurPixelsPerSide = 2.0f;
const vec2  blurMultiplyVec      = vec2(1.0f, 0.0f);
#else

// This only exists to get this shader to compile when no macros are defined

const float numBlurPixelsPerSide = 0.0f;
const vec2  blurMultiplyVec      = vec2(0.0f, 0.0f);

#endif


void main() {


  // Incremental Gaussian Coefficent Calculation (See GPU Gems 3 pp. 877 - 889)

  vec3 incrementalGaussian;

  incrementalGaussian.x = 1.0f / (sqrt(2.0f * pi) * sigma);
  incrementalGaussian.y = exp(-0.5f / (sigma * sigma));
  incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;


  vec4 avgValue = vec4(0.0f, 0.0f, 0.0f, 0.0f);
  float coefficientSum = 0.0f;


  // Take the central sample first...

  avgValue += texture2D(blurSampler, gl_TexCoord[0].xy) * incrementalGaussian.x;
  coefficientSum += incrementalGaussian.x;
  incrementalGaussian.xy *= incrementalGaussian.yz;


  // Go through the remaining 8 vertical samples (4 on each side of the center)

  for (float i = 1.0f; i <= numBlurPixelsPerSide; i++) {
  
    avgValue += texture2D(blurSampler, gl_TexCoord[0].xy - i * blurSize *
                          blurMultiplyVec) * incrementalGaussian.x;

    avgValue += texture2D(blurSampler, gl_TexCoord[0].xy + i * blurSize *
                          blurMultiplyVec) * incrementalGaussian.x;
    
    coefficientSum += 2 * incrementalGaussian.x;
    incrementalGaussian.xy *= incrementalGaussian.yz;

  }


  gl_FragColor = avgValue / coefficientSum;

}