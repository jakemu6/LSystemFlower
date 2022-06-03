#version 120

uniform sampler2D fboTexture;
uniform vec2 u_resolution;

uniform float blurAmnt;

varying vec2 texCoordVarying;

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

void main()
{
    vec2 position = ( gl_FragCoord.xy / u_resolution.xy );

    vec4 color = texture2D(fboTexture, position);
//    vec4 color = vec4(1.0, 1.0, 0.0, 1.0);


//    color += 0.000229 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * 4.0));
//    color += 0.005977 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * 3.0));
//    color += 0.060598 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * 2.0));
//    color += 0.241732 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * 1.0));
//
//    color += 0.382928 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, 0.0));
//
//    color += 0.241732 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * -1.0));
//    color += 0.060598 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * -2.0));
//    color += 0.005977 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * -3.0));
//    color += 0.000229 * texture2DRect(fboTexture, texCoordVarying + vec2(0.0, blurAmnt * -4.0));
//
    gl_FragColor = color;
}
