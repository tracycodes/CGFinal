#ifndef NODE_H
#define NODE_H

#include <list>
#include "Matrix4.h"
#include "KeyboardState.h"
#include "MouseState.h"
#include "RenderBatch.h"

namespace CGFramework
{
	class RenderBatch; //Forward Declaration, only using pointer don't need to include entire definition
	class Node
	{
	public:
		Node(Node* parent)
			:mParent(parent)
		{
			mWorld.Identity();
			mLocal.Identity();
		}
		//@param local the childs matrix offset
		Node* CreateNode(const CGMath::Matrix4& local)
		{
			Node* child = new Node(this);
			child->SetTransform(local);
			mChildren.push_back(child);
			return child;
		}
		void InsertNode(Node* in)
		{
			mChildren.push_back(in);
		}
		virtual void Update(float dt, KeyboardState keyboardState, MouseState mouseState)
		{
			//Update transformation
			if(mParent)
				mWorld = mParent->GetTransform() * mLocal;
			else
				mWorld = mLocal;

			//Update children
			for(std::list<Node*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
				(*it)->Update(dt, keyboardState, mouseState);

		}

		//Virtual - Nodes themselves don't need to render, but their children do.
		virtual void PrepareForRender(RenderBatch* batch)
		{
			//Just propogate to children, if the children need to add something to the batch they
			//do so in this function before calling base
			for(std::list<Node*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
				(*it)->PrepareForRender(batch);
		}

		CGMath::Matrix4 GetTransform() const
		{
			return mWorld;
		}
		void SetTransform(const CGMath::Matrix4& local) 
		{
			mLocal = local;
		}
		virtual ~Node()
		{
		}
	protected:
		Node* mParent;

		CGMath::Matrix4 mWorld;
		CGMath::Matrix4 mLocal;

		std::list<Node*> mChildren;
	};
}

#endif