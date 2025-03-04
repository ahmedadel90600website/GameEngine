#type Vertex
#version 460 core
	layout(location = 0) in vec3 a_Position;
	
	
	uniform mat4 u_ViewProjection;
	uniform mat4 u_ObjectTransform;
	uniform mat4 u_WorldTransform;
	void main()
	{
		gl_Position = u_ViewProjection * u_WorldTransform * u_ObjectTransform * vec4(a_Position, 1.0f);
	}

#type Fragment
#version 460 core
	layout(location = 0) out vec4 a_color;
	
	uniform vec3 u_TheColor;
	void main()
	{
		a_color = vec4(u_TheColor, 1.0f);
	}