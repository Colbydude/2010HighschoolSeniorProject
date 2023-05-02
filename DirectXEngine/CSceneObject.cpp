#include "CSceneObject.h"

namespace DirectXEngine
{
	CSceneObject::CSceneObject(void)
		: _position(0,0), _size(0,0),
		_scale(1,1), _rotation(0),
		_velocity(0,0), _acceleration(0,0),
		_friction(0,0), _gravity(0,0),
		_canUpdate(true), _canRender(false)
	{
	}

	CSceneObject::~CSceneObject(void)
	{
	}

	void CSceneObject::Update(float delta)
	{
		// First, add our Acceleration to the object's velocity.
		this->_velocity += this->_acceleration;

		// Now, we need to handle friction. This will be handled based on whether the velocity is positive or negative.
		if (this->_velocity.x > 0)
		{
			this->_velocity.x -= abs(this->_friction.x);
			if(this->_velocity.x < 0)
				this->_velocity.x = 0;
		}
		else if (this->_velocity.x < 0)
		{
			this->_velocity.x += abs(this->_friction.x);
			if(this->_velocity.x > 0)
				this->_velocity.x = 0;
		}

		if (this->_velocity.y > 0)
		{
			this->_velocity.y -= abs(this->_friction.y);
			if(this->_velocity.y < 0)
				this->_velocity.y = 0;
		}
		else if (this->_velocity.y < 0)
		{
			this->_velocity.y += abs(this->_friction.y);
			if(this->_velocity.y > 0)
				this->_velocity.y = 0;
		}

		// Finally, it's time to handle gravity.
		this->_velocity -= this->_gravity;

		// And then we add the velocity (multiplied by the frame delta) to the position.
		this->_position += (this->_velocity * (delta / 100));
	}
};