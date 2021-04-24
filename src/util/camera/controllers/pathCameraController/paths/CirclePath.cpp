#include "CirclePath.h"

CirclePath::CirclePath(glm::vec3 circleCenter, float circleRadius, float loft, float pathSpeed) :
	circleCenter{ circleCenter }, circleRadius{ circleRadius }, 
	loft{ loft }, pathSpeed{ pathSpeed} {
    
    this->verticalAngle = -atan(loft/circleRadius);
}

void CirclePath::update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right, double time) {

    time = pathSpeed*time;

	pos = circleRadius*glm::vec3(sin(time), 0.0f, cos(time));
	pos += glm::vec3 (circleCenter.x, circleCenter.y + loft, circleCenter.z);

	horizontalAngle = time + 3.14f;

	dir = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
}