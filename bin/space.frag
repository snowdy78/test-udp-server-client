#version 120

uniform vec2 iResolution; // resolution
uniform float iTime;	  // time
uniform vec2 iPosition;	  // position

float rand(in vec2 st)
{
	vec2 r = fract(sin(st) * 2.7644437);
	return fract(r.y * 276.44437 + r.x);
}

float p(in vec2 st)
{
	float r = rand(floor(st));
	return 0.01 + smoothstep(0.995, 1.0, r) * max(0.0, sin(r * 33333.0 + iTime));
}

vec3 stars(in vec2 st)
{
	vec3 color = vec3(0.0, 0.0, 0.02);
	return color + p(st);
}

void main()
{
	vec2 uv = (gl_FragCoord.xy - iPosition.xy) / min(iResolution.y, iResolution.x);
	uv *= 1000.0;

	vec3 color = stars(uv);

	gl_FragColor = vec4(color, 1.0);
}
