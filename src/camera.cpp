#include "camera.hpp"
//#include <iostream>
Camera::Camera(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	char *data_path = NULL;
    char *base_path = SDL_GetBasePath();
    if (base_path) 
    {
        data_path = base_path;
    } 
    else 
    {
        data_path = SDL_strdup("./");
    }
    std::string exePath(data_path);
	this->cameraPos 	= glm::vec3(0.0f, 0.0f,  3.0f);
	this->cameraFront 	= glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp		= glm::vec3(0.0f, 1.0f,  0.0f);
	this->baseSpeed		= 0.01f;
	this->speed 		= this->baseSpeed;
	this->yaw			= -90.0f;	
	this->pitch  		= 0.0f;
	this->sphereYaw		= -90.0f;	
	this->spherePitch  	= 0.0f;
	this->renderDistance= 3000.0f;
	this->projection	= glm::perspective(45.0f, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, renderDistance);
	this->isPlayingBack = false;
	this->renderSphere 	= false;
	this->rotateState	= 0;
	this->sphereColor  	= glm::vec3(0.0f,0.0f,0.0f);
	this->centerOfMass 	= glm::vec3(0.0f,0.0f,0.0f);
	this->sphereDistance= 5.0f;
	this->vertShader 	= exePath + "Viewer-Assets/shaders/colorSphere.vs";
	this->fragShader 	= exePath + "Viewer-Assets/shaders/colorSphere.frag";
	spherePos 			= calcSpherePos(this->yaw,this->pitch,this->cameraPos);
	this->rotLock = false;
	this->comLock = false;

}
glm::mat4 Camera::setupCam()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
void Camera::moveForward()
{
	cameraPos += speed * cameraFront;
}
void Camera::moveBackward()
{
	cameraPos -= speed * cameraFront;
}
void Camera::moveRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}
void Camera::moveLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}
void Camera::updateSpeed(GLfloat deltaTime)
{
	this->speed = this->baseSpeed * deltaTime;
}
void Camera::lookUp(float pitch)
{
	this->pitch += pitch;
}
void Camera::lookDown(float pitch)
{
	this->pitch -= pitch;
}
void Camera::lookRight(float yaw)
{
	this->yaw += yaw;
}
void Camera::lookLeft(float yaw)
{
	this->yaw -= yaw;
}
void Camera::update(GLfloat deltaTime)
{
	clampPitch(this->pitch);
 	glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    updateSpeed(deltaTime);
}
void Camera::clampPitch(GLfloat &pitch)
{
	if (pitch > 89.0f)
	{
        pitch = 89.0f;
	}
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
}
void Camera::clampDegrees(GLfloat &in)
{
	in = fmod(in,360);
	if(in < 0.0)
	{
		in += 360.0f;
	}
}
void Camera::setRenderDistance(float renderDistance)
{
	this->renderDistance = renderDistance;
}
void Camera::changeSpeed(float speed)
{
	this->speed = speed;
}
void Camera::recordPosition(int frame)
{
	for(int i =0; i < camLocation.size();i++) //checks to make sure the element has not been used already
	{
		if(camLocation[i].frame == frame)
		{
				camLocation.erase(camLocation.begin() + i); //deletes the element if it already exists
		}
	}
	locData data;
	data.frame = frame;
	data.position = cameraPos;
	data.look = glm::vec2(yaw,pitch);
	camLocation.push_back(data);
	//sort data
}
void Camera::MultiKeyEventReader(SDL_Event &event)
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if(keystate[SDL_SCANCODE_W] && !rotLock)
	{
		moveForward();
	}
	if(keystate[SDL_SCANCODE_S]&& !rotLock)
	{
		moveBackward();
	}
	if(keystate[SDL_SCANCODE_A]&& !rotLock)
	{
		moveLeft();
	}
	if(keystate[SDL_SCANCODE_D]&& !rotLock)
	{
		moveRight();
	}
	if(keystate[SDL_SCANCODE_W] && rotLock)
	{
		spherePitch += 1.0;
		lookDown(1.0f);
	}
	if(keystate[SDL_SCANCODE_S]&& rotLock)
	{
		spherePitch -= 1.0;
		lookUp(1.0f);
	}
	if(keystate[SDL_SCANCODE_A]&& rotLock)
	{
		sphereYaw -= 1.0;
		lookLeft(1.0);
	}
	if(keystate[SDL_SCANCODE_D]&& rotLock)
	{
		sphereYaw += 1.0;
		lookRight(1.0);
	}
	if(keystate[SDL_SCANCODE_I]&& !rotLock)
	{
		lookUp(2.5f);
	}
	if(keystate[SDL_SCANCODE_K]&& !rotLock)
	{
		lookDown(2.5f);
	}
	if(keystate[SDL_SCANCODE_J]&& !rotLock)
	{
		lookLeft(2.5f);
	}
	if(keystate[SDL_SCANCODE_L]&& !rotLock)
	{
		lookRight(2.5f);
	}
	if(renderSphere)
	{
		if(keystate[SDL_SCANCODE_LEFTBRACKET])
		{
			sphereDistance -= .25;
		}
		if(keystate[SDL_SCANCODE_RIGHTBRACKET])
		{
			sphereDistance += .25;
		}
	}
	clampPitch(this->spherePitch);
	clampDegrees(this->sphereYaw);
	clampDegrees(this->yaw);
}
void Camera::SingleKeyEventReader(SDL_Event &event)
{
	if(event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_p)
		{
			rotateState++;
			rotateState = rotateState%3;
			if(rotateState == 0)
			{
				rotLock = false;
				comLock = false;
				renderSphere = false;
				sphereColor  = glm::vec3(0.0f,0.0f,0.0f);
			}
			else if(rotateState == 1)
			{
				rotLock = false;
				comLock = false;
				renderSphere = true;
				sphereColor  = glm::vec3(1.0f,0.0f,0.0f);
			}
			else if(rotateState == 2)
			{
				this->sphereYaw = yaw + 180;
				this->spherePitch = -pitch;
				renderSphere = true;
				rotLock = true;
				sphereColor  = glm::vec3(0.0f,1.0f,0.0f);
			}
		}
		if(event.key.keysym.sym == SDLK_o)
		{
			if(rotLock)
			{
				comLock = !comLock;
			}
			
		}
		if(event.key.keysym.sym == SDLK_1 && rotLock)
		{
			this->yaw= 90.0f;
			this->pitch = 0.0f;
			this->sphereYaw = -90.0f;
			this->spherePitch = 0.0f;
		}
		if(event.key.keysym.sym == SDLK_2 && rotLock)
		{
			this->yaw= 180.0f;
			this->pitch = 0.0f;
			this->sphereYaw = 0.0f;
			this->spherePitch = 0.0f;
		}
		if(event.key.keysym.sym == SDLK_3 && rotLock)
		{
			this->yaw= 270.0f;
			this->pitch = 0.0f;
			this->sphereYaw = 90.0f;
			this->spherePitch = 0.0f;
		}
		if(event.key.keysym.sym == SDLK_4 && rotLock)
		{
			this->yaw= 0.0f;
			this->pitch = 0.0f;
			this->sphereYaw = 180.0f;
			this->spherePitch = 0.0f;
		}
		if(event.key.keysym.sym == SDLK_5 && rotLock)
		{
			this->yaw= 90.0f;
			this->pitch = -89.0f;
			this->sphereYaw = 270.0f;
			this->spherePitch = 89.0f;
		}
		if(event.key.keysym.sym == SDLK_6 && rotLock)
		{
			this->yaw= 90.0f;
			this->pitch = 89.0f;
			this->sphereYaw = 270.0f;
			this->spherePitch = -89.0f;
		}
		clampPitch(this->spherePitch);
		clampDegrees(this->sphereYaw);
		clampDegrees(this->yaw);
	}
}
void Camera::setSphereCenter(glm::vec3 pos)
{
	centerOfMass = pos;
}
void Camera::RenderSphere()
{
	if(renderSphere)
	{
		sphereShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(sphereShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(setupCam()));
		glUniformMatrix4fv(glGetUniformLocation(sphereShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(this->projection));
		
		if(rotLock && comLock)
		{
			cameraPos = calcSpherePos(this->sphereYaw,this->spherePitch,this->centerOfMass);
		}

		else if(!rotLock)
		{
			spherePos = calcSpherePos(this->yaw,this->pitch,this->cameraPos);
		}
		else if(rotLock)
		{
			cameraPos = calcSpherePos(this->sphereYaw,this->spherePitch,this->spherePos);
		}
		else
		{
			std::cout << "Yeah... Fix the rotLock and comLock if statements" << std::endl;
		}
		
	    glUniform3fv(glGetUniformLocation(sphereShader.Program, "pos"), 1, glm::value_ptr(spherePos));
	    glUniform3fv(glGetUniformLocation(sphereShader.Program, "color"), 1, glm::value_ptr(sphereColor));
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);
		if(comLock)
		{
			glUniform3fv(glGetUniformLocation(sphereShader.Program, "pos"), 1, glm::value_ptr(centerOfMass));
		    glUniform3fv(glGetUniformLocation(sphereShader.Program, "color"), 1, glm::value_ptr(glm::vec3(0,0,1.0f)));
			glBindVertexArray(VAO2);
			glDrawArrays(GL_POINTS, 0, 1);
			glBindVertexArray(0);
		}
		
	}
}
void Camera::initGL()
{
	this->sphereShader = Shader(vertShader.c_str(),fragShader.c_str());
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO2);
}
glm::vec3 Camera::calcSpherePos(GLfloat yaw, GLfloat pitch,glm::vec3 pos)
{
	if(sphereDistance < 1)
	{
		sphereDistance = 1;
	}
	return glm::vec3(pos.x + cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * sphereDistance,pos.y + sin(glm::radians(pitch)) * sphereDistance,pos.z + sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * sphereDistance);
}