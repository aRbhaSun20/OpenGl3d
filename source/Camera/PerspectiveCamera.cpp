#include "PerspectiveCamera.h"

void PerspectiveCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        Position += velocity * Orientation;
    if (direction == Camera_Movement::BACKWARD)
        Position += velocity * -Orientation;
    if (direction == Camera_Movement::LEFT)
        Position += velocity * -glm::normalize(glm::cross(Orientation, Up));
    if (direction == Camera_Movement::RIGHT)
        Position += velocity * glm::normalize(glm::cross(Orientation, Up));

    if (direction == Camera_Movement::UP)
        Position += velocity * Up;
    if (direction == Camera_Movement::DOWN)
        Position += velocity * -Up;
    if (direction == Camera_Movement::SHIFT_HOLD)
        MovementSpeed = 0.4f;
    if (direction == Camera_Movement::SHIFT_RELEASE)
        MovementSpeed = 0.1f;

    checkCondition();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void PerspectiveCamera::ProcessMouseScroll(float yoffset)
{
    if (yoffset == 1)
        Position += MovementSpeed * 2 * Orientation;
    else
        Position += MovementSpeed * 2 * -Orientation;
    checkCondition();
}

void PerspectiveCamera::checkCondition()
{ // screen constraints
    if (Position.x > Position.z)
        Position = {Position.z, Position.y, Position.z};
    if (Position.x < -Position.z)
        Position = {-Position.z, Position.y, Position.z};
    if (Position.y > Position.z / 2)
        Position = {Position.x, Position.z / 2, Position.z};
    if (Position.y < -Position.z / 2)
        Position = {Position.x, -Position.z / 2, Position.z};
}

void PerspectiveCamera::updateCameraVectors()
{
    // Calculate the new Orientation vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Orientation = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Orientation, WorldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Orientation));
}

void PerspectiveCamera::ProcessMouseMovement(double xoffset, double yoffset, int WIDTH, int HEIGHT, GLboolean constrainPitch)
{
    Position.x = -mapFunction(xoffset, 0.0f, (float)WIDTH, -Position.z, Position.z);
    Position.y = mapFunction(yoffset, 0.0f, (float)HEIGHT, -Position.z / 2, Position.z / 2);
    checkCondition();
}

float PerspectiveCamera::mapFunction(double value, float fromLow, float fromHigh, float toLow, float toHigh)
{
    float fromRes = fromHigh - fromLow;
    float toRes = toHigh - toLow;
    float valueRes = value - fromLow;
    double res = ((valueRes / fromRes) * toRes) + toLow;
    return (float)res;
}