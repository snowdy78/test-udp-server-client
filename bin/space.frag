#version 120

#define iterations 20
#define formuparam 0.53

#define volsteps 1
#define stepsize 0.1

#define zoom 0.800
#define tile 0.885
#define speed 0.010
#define brightness 0.0015
#define darkmatter 0.300
#define distfading 0.730
#define saturation 0.850

uniform vec2 iResolution; // resolution
uniform float iTime;	  // time
uniform vec2 iPosition;	  // position
const vec3 tile3  = vec3(tile);
const vec3 tile23 = vec3(tile) * 2.0;
void main()
{
	// get coords and direction
	vec2 uv = gl_FragCoord.xy / iResolution.xy - .5;
	uv.y *= iResolution.y / iResolution.x;
	vec3 dir	 = vec3(uv * zoom, 1.);
	float slower = 0.01125;
	float time	 = iTime * speed * slower + .25;

	// mouse rotation
	float a1  = (iPosition.x / iResolution.x) * 0.05 - 0.5;
	float a2  = (iPosition.y / iResolution.y) * 0.05 - 0.5;
	mat2 rot1 = mat2(cos(a1), sin(a1), -sin(a1), cos(a1));
	mat2 rot2 = mat2(cos(a2), sin(a2), -sin(a2), cos(a2));
	dir.xz *= rot1;
	dir.xy *= rot2;
	vec3 from = vec3(1., .5, 0.5);
	from += vec3(time * 2., time, -2.);
	from.xz *= rot1;
	from.xy *= rot2;

	// volumetric rendering
	float s = 1.0, fade = 0.25;
	vec3 v = vec3(0.);
	for (int r = 0; r < volsteps; r++)
	{
		vec3 p = from + s * dir * .5;
		p	   = abs(tile3 - mod(p, tile23)); // tiling fold
		float pa, a = pa = 0.;
		for (int i = 0; i < iterations; i++)
		{
			p = abs(p) / dot(p, p) - formuparam; // the magic formula
			a += abs(length(p) - pa);			 // absolute sum of average change
			pa = length(p);
		}
		a = pow(a, 3.0); // add contrast
		// v+=vec3(dm,dm*.5,0.);
		v += fade;
		float sqrs = s * s;
		v += vec3(s, sqrs, sqrs*sqrs) * a * brightness * fade; // coloring based on distance
		fade *= distfading;											// distance fading
		s += stepsize;
	} // distance fading
	v			 = mix(vec3(length(v)), v, saturation); // color adjust
	gl_FragColor = vec4(v * .01, 1.);
}
