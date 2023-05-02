#pragma once

// Global Header Files.
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace DirectXEngine
{
	class CSceneObject
	{
	private:
		// Position, Rotation, and Size data.
		D3DXVECTOR2 _position;
		D3DXVECTOR2 _size;
		D3DXVECTOR2 _scale;
		float _rotation;

		// Velocity and other basic movement data.
		D3DXVECTOR2 _velocity;
		D3DXVECTOR2 _acceleration;
		D3DXVECTOR2 _friction;
		D3DXVECTOR2 _gravity;

	protected:
		bool _canUpdate;
		bool _canRender;

	public:
		// Constructor & Destructor.
		CSceneObject();
		~CSceneObject();

		// Function Declarations.
		void Update(float);
		bool place_free(float, float);

		// Accessors & Mutators.
		bool CanRender(void) { return this->_canRender; }
		bool CanUpdate(void) { return this->_canUpdate; }

		float GetLeft(void) { return this->_position.x; }
		float GetRight(void) { return (this->_position.x + (this->_size.x * this->_scale.x)); }
		float GetTop(void) { return this->_position.y; }
		float GetBottom(void) { return (this->_position.y + (this->_size.y * this->_scale.y)); }
		float GetWidth(void) { return this->_size.x; }
		float GetHeight(void) { return this->_size.y; }
		D3DXVECTOR2 GetCenter(void) { return D3DXVECTOR2(((float)(this->_size.x * this->_scale.x)/2), ((float)(this->_size.y * this->_scale.y)/2)); }

		D3DXVECTOR2 GetPosition(void) { return this->_position; }
		void SetPosition(D3DXVECTOR2 val) { this->_position = val; }
		void SetPositionX(float val) { this->_position.x = val; }
		void SetPositionY(float val) { this->_position.y = val; }

		D3DXVECTOR2 GetSize(void) { return this->_size; }
		void SetSize(D3DXVECTOR2 val) { this->_size = val; }
		void SetWidth(float val) { this->_size.x = val; }
		void SetHeight(float val) { this->_size.y = val; }

		D3DXVECTOR2 GetScale(void) { return this->_scale; }
		void SetScale(D3DXVECTOR2 val) { this->_scale = val; }
		void SetScaleX(float val) { this->_scale.x = val; }
		void SetScaleY(float val) { this->_scale.y = val; }

		float GetRotation(void) { return this->_rotation; }
		void SetRotation(float val) { this->_rotation = val; }

		D3DXVECTOR2 GetVelocity(void) { return this->_velocity; }
		void SetVelocity(D3DXVECTOR2 val) { this->_velocity = val; }
		void SetVelocityX(float val) { this->_velocity.x = val; }
		void SetVelocityY(float val) { this->_velocity.y = val; }

		D3DXVECTOR2 GetAcceleration(void) { return this->_acceleration; }
		void SetAcceleration(D3DXVECTOR2 val) { this->_acceleration = val; }
		void SetAccelerationX(float val) { this->_acceleration.x = val; }
		void SetAccelerationY(float val) { this->_acceleration.y = val; }

		D3DXVECTOR2 GetFriction(void) { return this->_friction; }
		void SetFriction(D3DXVECTOR2 val) { this->_friction = val; }
		void SetFrictionX(float val) { this->_friction.x = val; }
		void SetFrictionY(float val) { this->_friction.y = val; }

		D3DXVECTOR2 GetGravity(void) { return this->_gravity; }
		void SetGravity(D3DXVECTOR2 val) { this->_gravity = val; }
		void SetGravityX(float val) { this->_gravity.x = val; }
		void SetGravityY(float val) { this->_gravity.y = val; }
	};
};