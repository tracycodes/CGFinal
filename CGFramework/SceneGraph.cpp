#include "SceneGraph.h"

using namespace CGFramework;

SceneGraph::SceneGraph()
{
	Root = new Node(NULL);
}
Node* SceneGraph::GetRoot()
{
	return Root;
}
void SceneGraph::Update(float dt, KeyboardState keyboardState, MouseState mouseState)
{
	Root->Update(dt, keyboardState, mouseState);
}
void SceneGraph::PrepareForRender(RenderBatch* batch)
{
	batch->Clear();	
	Root->PrepareForRender(batch);
}
SceneGraph::~SceneGraph()
{
	delete Root;
}