#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;
varying vec4 v_color;

void main()
{
    // Set fragment color from texture
//    gl_FragColor = texture2D(texture, v_texcoord);

    float x = gl_FragCoord.x + v_color.x;
    float y = gl_FragCoord.y + v_color.y;
    float z = v_color.z;
//    float z = gl_FragCoord.z * 2000.0;
    float t = sqrt(x*x + y*y + z*z);
//    gl_FragColor = vec4(x/t, y/t, z/t, 1);

    gl_FragColor = v_color;
}
