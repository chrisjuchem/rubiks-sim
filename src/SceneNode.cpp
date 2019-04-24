#include "SceneNode.h"
#include <string>
#include <random>

// The constructor
SceneNode::SceneNode(Object* ob){
	object = ob;
	// By default, we do not know the parent
	// at the time of construction of this node.
	// If the SceneNode is the root of the tree,
	// then there is no parent.
	parent = nullptr;
	
	// Setup shaders for the node.
	std::string vertexShader = myShader.LoadShader("./shaders/vert.glsl");
	std::string fragmentShader = myShader.LoadShader("./shaders/frag.glsl");
	// Actually create our shader
	myShader.CreateShader(vertexShader,fragmentShader);       
}

// The destructor 
SceneNode::~SceneNode(){
	// Remove each object
	for(unsigned int i =0; i < children.size(); ++i){
		delete children[i];
	}
}

// Adds a child node to our current node.
void SceneNode::AddChild(SceneNode* n){
	// For the node we have added, we can set
	// it's parent now to our current node.
	// 'this' is the current instance of our
	// object, which is a pointer to our current
	// SceneNode.
	n->parent = this;
	// Add a child node into our SceneNode
	// std::cout << "parent to: " << n << " is " << this << "\n";
	children.push_back(n);
}

void SceneNode::SetGraphColor(int depth, bool showGraph) {
	if (showGraph) {
		if (depth == 1) {
			graphColor = glm::vec3(
				rand()/(double)RAND_MAX,
				rand()/(double)RAND_MAX,
				rand()/(double)RAND_MAX
			);
		} else if (depth > 1) {
			graphColor = parent->graphColor;
		}
	} else {
		graphColor = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	
	for(int i =0; i < children.size(); ++i){
		children[i]->SetGraphColor(depth+1, showGraph);
	}
}

// Draw simply draws the current nodes
// object and all of its children. This is done by calling directly
// the objects draw method.
void SceneNode::Draw(){
	myShader.Bind();
	if(object!=nullptr){
		object->render();
	}
	for(int i =0; i < children.size(); ++i){
		children[i]->Draw();
	}
}

// Update simply updates the current nodes
// object. This is done by calling directly
// the objects update method.
void SceneNode::Update(glm::mat4 projectionMatrix, Camera* camera){
	if (parent==nullptr) {
		worldTransform = localTransform;
	} else {
		worldTransform = parent->worldTransform * localTransform;
	}
	// Now apply our shader transformation
	myShader.Bind();
	// Set the uniforms in our current shader

	// For our object, we apply the texture in the following way
	// Note that we set the value to 0, because we have bound
	// our texture to slot 0.
	myShader.setUniform1i("u_DiffuseMap",0);  
	// Set the MVP Matrix for our object
	// Send it into our shader
	myShader.setUniformMatrix4fv("model", &worldTransform.getInternalMatrix()[0][0]);
	myShader.setUniformMatrix4fv("view", &camera->getWorldToViewmatrix()[0][0]);
	myShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);

	// Create a 'light'
	myShader.setUniform3f("lightColor",1.0f,1.0f,1.0f);
	myShader.setUniform3f("lightPos",
							camera->getEyeXPosition() + camera->getViewXDirection(),
							camera->getEyeYPosition() + camera->getViewYDirection(),
							camera->getEyeZPosition() + camera->getViewZDirection());
	myShader.setUniform1f("ambientIntensity",0.5f);

	myShader.setUniform3f("sceneGraphColor", graphColor.x, graphColor.y,  graphColor.z);

	for(int i =0; i < children.size(); ++i){
		children[i]->Update(projectionMatrix, camera);
	}
}

// Returns the actual local transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::getLocalTransform(){
    return localTransform; 
}

// Returns the worled  transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::getWorldTransform(){
    return worldTransform; 
}



void SceneNode::setParent(SceneNode* newParent) {
	for (auto it = parent->children.begin(); it != parent->children.end(); it++) {
		if (this == *it) {
			parent->children.erase(it);
			break;
		}
	}

	newParent->AddChild(this);
	localTransform.applyTransform(glm::inverse(newParent->worldTransform.getInternalMatrix()) * worldTransform.getInternalMatrix());
	SetGraphColor(2, true); //hack to get the right color
}

float SceneNode::dist(Transform& other) {
    glm::mat4 myMat  = getWorldTransform().getInternalMatrix();
    glm::mat4 otherMat = other.getInternalMatrix();
    return glm::length((myMat * glm::vec4(0.0f,0.0f,0.0f, 1.0f)) -
					(otherMat * glm::vec4(0.0f,0.0f,0.0f, 1.0f)));
        
}