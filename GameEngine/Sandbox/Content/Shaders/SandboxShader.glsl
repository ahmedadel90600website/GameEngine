#type Vertex
#version 460 core
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec2 a_TextureCoordinates;
	
	out vec2 v_TextureCoordinates;
	
	uniform mat4 u_ViewProjection;
	uniform mat4 u_ObjectTransform;
	void main()
	{
		v_TextureCoordinates = a_TextureCoordinates;
		gl_Position = u_ViewProjection * u_ObjectTransform * vec4(a_Position, 1.0f);
	}


#type Fragment
#version 460 core
	layout(location = 0) out vec4 a_color;
	
	in vec2 v_TextureCoordinates;

	uniform vec3 u_TheColor;
	uniform sampler2D u_TextureSlot;
	void main()
	{
		a_color = texture(u_TextureSlot, v_TextureCoordinates);
	}