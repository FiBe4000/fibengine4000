uniform sampler2D tex;
uniform float timer;

vec3 blur(vec2 coord);
vec4 night(vec4 pixel);
vec4 bright(vec4 pixel);
vec4 mushrooms(vec2 coord);

void main()
{
    // lookup the pixel in the texture
   	vec4 pixel = texture2D(tex, gl_TexCoord[0].xy);

    // multiply it by the color
   	gl_FragColor = vec4(1, 1, 1, 1) * pixel;
	    
   	//gl_FragColor = vec4(blur(gl_TexCoord[0].xy), pixel.w);
   	//gl_FragColor = night(pixel);
   	//gl_FragColor = bright(pixel);
   	//gl_FragColor = mushrooms(gl_TexCoord[0].xy);
}

vec3 blur(vec2 coord)
{
	// sample framebuffer texture at current texel
	vec3 result = texture2D(tex, coord.xy).xyz * 0.5;

	// sample framebuffer texture at neighbouring texels
	result += 0.125 * texture2D(tex, coord + vec2(1, 0)).xyz * 0.03125;
	result += 0.125 * texture2D(tex, coord + vec2(0, 1)).xyz * 0.03125;
	result += 0.125 * texture2D(tex, coord + vec2(-1, 0)).xyz * 0.03125;
	result += 0.125 * texture2D(tex, coord + vec2(0, -1)).xyz * 0.03125;

	return result;
}

vec4 night(vec4 pixel)
{
	return vec4(0.2, 0.2, 1, 1) * pixel;
}

vec4 bright(vec4 pixel)
{
	return vec4(1.2, 1.3, 0.5, 1) * pixel;
}

vec4 mushrooms(vec2 coord)
{
    coord.x += sin(radians(timer + coord.y * 500.0)) * 0.07;
    coord.y += cos(radians(timer + coord.x * 250.0)) * 0.03;
    
    return texture2D(tex, coord);
}

