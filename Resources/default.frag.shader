#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	if (texture(tex0, texCoord).a < 0.5)
		discard;
	FragColor = texture(tex0, texCoord);
}