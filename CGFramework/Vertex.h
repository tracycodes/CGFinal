#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"
#include "Vector2.h"

namespace CGMath
{
	/* This class defines the format of our vertexes. In some way this should be user defined
	in case additional information needs to be added to each point. For the moment, I don't 
	see a reason why this can't just be hardcode (At least until we need different vertex
	formats). For shader programs this will tell the shader which format our vertex stream
	is going to appear in. */
	class Vertex
	{
	public:
		Vertex(const Vector3& pos, const Vector3& norm, const Vector2& tex)
			:pos(pos), norm(norm), tex(tex){}
	public:
		Vector2 tex;
		Vector3 norm;
		Vector3 pos;
	};
}

#endif