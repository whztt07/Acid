#pragma once

#include "../Sources/devices/display.h"
#include "../Sources/devices/mouse.h"
#include "../Sources/camera/icamera.h"

namespace flounder {
	class maincamera : public icamera {
	private:
		vector3 *m_position;
		vector3 *m_rotation;

		matrix4x4 *m_viewMatrix;
		matrix4x4 *m_projectionMatrix;

		frustum *m_viewFrustum;
		ray *m_viewRay;
	public:
		maincamera()
		{
			m_position = new vector3();
			m_rotation = new vector3();

			m_viewMatrix = new matrix4x4();
			m_projectionMatrix = new matrix4x4();

			m_viewFrustum = new frustum();
			m_viewRay = new ray(false, new vector2(0.5f, 0.5f));
		}

		~maincamera()
		{
			delete m_position;
			delete m_rotation;

			delete m_viewMatrix;
			delete m_projectionMatrix;

			delete m_viewFrustum;
			delete m_viewRay;
		}

		float getNearPlane() override;

		float getFarPlane() override;

		float getFOV() override;

		void update(iplayer *player) override;

		inline frustum *getViewFrustum() override { return m_viewFrustum; }

		inline ray *getViewRay() override { return m_viewRay; }

		inline matrix4x4 *getViewMatrix() override { return m_viewMatrix; }

		inline matrix4x4 *getProjectionMatrix() override { return m_projectionMatrix; }

		void reflect(const float &waterHeight) override;

		inline vector3 *getPosition() override { return m_position; }

		inline vector3 *getRotation() override { return m_rotation; }

		inline void setRotation(vector3 *rotation) override { m_rotation->set(*rotation); }
	};
}
