#pragma once

#include <Precomz/precomz.h>
#include "../Core/LogFile.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

enum class Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	SHIFT_HOLD,
	SHIFT_RELEASE
};

#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 0.1f
#define SENSITIVITY 1.0f
#define ZOOM 100.0f
#define FOVMAX 45.0f
#define FOVMIN 1.0f

class PerspectiveCamera
{

private:
	glm::vec3 Position;
	glm::vec3 Orientation = {0.0f, 0.0f, -1.0f};
	glm::vec3 Up = {0.0f, 1.0f, 0.0f};
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::mat4 viewMatrix;

	Logger::LogFile &p_File;

private:
	float radius;
	float phi;
	float theta;
	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();

public:
	PerspectiveCamera(Logger::LogFile &LogFile, glm::vec3 position = {0.0f, 0.0f, 0.0f}, glm::vec3 up = {0.0f, 1.0f, 0.0f}, float yaw = YAW, float pitch = PITCH)
		: p_File(LogFile), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),
		  Zoom(ZOOM), Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch)
	{
		CORE_INFO("Perfective Camera Setup Starting");
		updateCameraVectors();
		CORE_INFO("Perfective Camera Setup Complete");
	}
	PerspectiveCamera(Logger::LogFile &LogFile, float posX, float posY, float posZ, float upX,
					  float upY, float upZ, float yaw = YAW, float pitch = PITCH)
		: Orientation({0.0f, 0.0f, -1.0f}), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM),
		  Position({posX, posY, posZ}), WorldUp({upX, upY, upZ}), Yaw(yaw), Pitch(pitch), p_File(LogFile)
	{
		updateCameraVectors();
	}

	~PerspectiveCamera()
	{
		CORE_WARN("Perfective Camera Setup Closing");
	};

	glm::mat4 GetViewMatrix()
	{
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		viewMatrix = glm::lookAt(Position, Position + Orientation, Up);
		return viewMatrix;
	};

	float getZoomLevel() { return Zoom; };

	glm::vec3 getCameraPosition() { return Position; };

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);

	void ProcessMouseMovement(double xoffset, double yoffset, int WIDTH, int HEIGHT, GLboolean constrainPitch);

	void checkCondition();

	void setOrientation(glm::vec3 newOrientation)
	{
		Orientation = newOrientation;
	};

	glm::vec3 getOrientation() { return Orientation; };
	glm::vec3 getUp() { return Up; };

	float mapFunction(double value, float fromLow, float fromHigh, float toLow, float toHigh);
};
