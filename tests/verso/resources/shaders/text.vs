attribute vec4 coord;
varying vec2 texpos;

uniform mat4 MVP;

void main(void) {
  gl_Position = MVP * vec4(coord.xy, 0, 1);
  texpos = coord.zw;
}
