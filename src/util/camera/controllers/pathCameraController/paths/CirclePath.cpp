#include "CirclePath.h"

CirclePath::CirclePath(glm::vec3 circleCenter, float circleRadius, float loft, float pathSpeed) :
	circleCenter{ circleCenter }, circleRadius{ circleRadius }, 
	loft{ loft }, pathSpeed{ pathSpeed} {}

void CirclePath::update(glm::vec3& pos, float& horizontalAngle, float& verticalAngle, double time) {

    time = pathSpeed*time;

	pos = circleRadius*glm::vec3(sin(time), 0.0f, cos(time));
	pos += glm::vec3 (circleCenter.x, circleCenter.y + loft, circleCenter.z);

	horizontalAngle = time + 3.14f;
	verticalAngle = -atan(loft/circleRadius);
}