#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "Node.h"
#include "RenderBatch.h"
#include "KeyboardState.h"
#include "MouseState.h"

namespace CGFramework
{
	class SceneGraph
	{
	public:
		/* Initialize the graph and create the root node. Other than that, leave it empty
		 */
		SceneGraph();

		/* Fetch the root node of the graph, this function will be used anytime a node
		 * needs to be inserted into the graph. It's the jumping off point.
		 */
		Node* GetRoot();

		/* Update the scene graph. This routine starts a breadth-first traversal
		 * of the graph eventually accumulating all nodes into the renderBatch with
		 * their update transformation and rendering data. 
		 */
		void Update(float dt, KeyboardState keyboardState, MouseState mouseState);


		/* Prepare the scene graph for rendering. This routines propogates through the nodes in 
		 * the scene graph collecting all information from them that is neccesary for rendering.
		 * It is detached from the update so that the scene can be updated only when needed.
		 */
		void PrepareForRender(RenderBatch* batch);

		/* Begin the destruction of the scene graph. This traverses downward through the tree, telling
		 * each node to destroy itself and it's children. By the time it completes all the child nodes
		 * have been destroyed.
		 */
		~SceneGraph();
	private:
		Node* Root;

	};
}

#endif