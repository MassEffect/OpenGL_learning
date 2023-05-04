#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float ROLL        = 0.0f;
const float SENSITIVITY = 0.1f;
const float SPEED       = 2.5f;
const float ZOOM        = 45.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera( glm::vec3 position = glm::vec3(0.0f, 0.0f, 6.0f)
           ,glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)
           ,float yaw = YAW
           ,float pitch = PITCH)
           :     Front(glm::vec3(0.0f, 0.0f, 0.0f))
                ,MovementSpeed(SPEED)
                ,MouseSensitivity(SENSITIVITY)
                ,Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    };

     Camera( float posX
            ,float posY
            ,float posZ
            ,float upX
            ,float upY
            ,float upZ
            ,float yaw
            ,float pitch)
            :
                 Front(glm::vec3(0.0f, 0.0f, -1.0f))
                 ,MovementSpeed(SPEED)
                 ,MouseSensitivity(SENSITIVITY)
                 ,Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    };

    void processMouseScroll(float yoffset)
    {
        Zoom -= static_cast<float>(yoffset);
        if(Zoom < 1.0f)
            Zoom = 1.0f;
        if(Zoom > 90.0f)
            Zoom = 90.0f;
    };

    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if(constrainPitch)
        {
            if(Pitch > 90.0f)
                Pitch = 90.0f;
            if(Pitch < -90.0f)
                Pitch = -90.0f;
        };

        updateCameraVectors();
    };

    void processKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if(direction == FORWARD)
            Position += Front * velocity;
        if(direction == BACKWARD)
            Position -= Front * velocity;
        if(direction == LEFT)
            Position -= Right * velocity;
        if(direction == RIGHT)
            Position += Right * velocity;

        Position.y = 0.0f;
    };

    glm::mat4 getViewMatrix()
    {
        //return glm::lookAt(Position, Position + Front, Up);

        glm::mat4 leftPartMat   = glm::mat4(1.0f);
        glm::mat4 rightPartMat  = glm::mat4(1.0f);

        rightPartMat[3][0] = -Position.x;
        rightPartMat[3][1] = -Position.y;
        rightPartMat[3][2] = -Position.z;

        leftPartMat[0][0] = Right.x;
        leftPartMat[1][0] = Right.y;
        leftPartMat[2][0] = Right.z;

        leftPartMat[0][1] = Up.x;
        leftPartMat[1][1] = Up.y;
        leftPartMat[2][1] = Up.z;

        leftPartMat[0][2] = -Front.x;
        leftPartMat[1][2] = -Front.y;
        leftPartMat[2][2] = -Front.z;

        return leftPartMat * rightPartMat;
    };


private:
    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    };
};

#endif // CAMERA_H
