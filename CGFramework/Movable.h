#ifndef MOVABLE_H
#define MOVABLE_H

#include "Matrix4.h"
#include "RenderBatch.h"

class Movable
{
public:
	Movable()
	{
		mWorld.Identity();
		mLocal.Identity();
	}
	/* Called by the parent node that this movable is attached to. Causes the movable
	 * to update it's transformation matrix in response to it's parents.
	 */
	//void UpdateBatch(RenderBatch* batch)
//	{
//
//	}
	void SetTransform(const CGMath::Matrix4 local)
	{
		mLocal = local;
	}
	~Movable(){}
private:
	CGMath::Matrix4 mWorld;
	CGMath::Matrix4 mLocal;
};

#endif