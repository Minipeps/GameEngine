#version 150
/*
 * The fragment shader operates on each pixel of a given polygon.
 */

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// Output pixel RGBA color
out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main()
{
    // Retrieve color from texture using fragmentUV coordinates    
    vec4 textureColor = texture(mySampler, fragmentUV);
    
    // Make crazy colors using time and position!
    color = vec4( fragmentColor.r * ( cos(fragmentPosition.x * 4.0 + time) + 1.0 ) * 0.5,
                  fragmentColor.g * ( cos(fragmentPosition.y * 8.0 + time) + 1.0 ) * 0.5,
                  fragmentColor.b * ( cos(fragmentPosition.x * 2.0 + time) + 1.0 ) * 0.5,
                  fragmentColor.a
                ) * textureColor;    
}