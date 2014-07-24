#pragma once
#ifndef _GECAMERACLASS_H_
#define _GECAMERACLASS_H_

#include "GEmath.h"
#include "GEManageClass.h"

//-----------------------------------------------------------------------
namespace GE
{
	enum CameraMode
	{
		GE_FIRST_PERSON = 0,
		GE_THIRD_PERSON = 1,
	};

	struct CameraDesc
	{
		FLOAT3	  position;
		FLOAT3	  right;
		FLOAT3	  up;
		FLOAT3	  look;
		FLOAT     distance;
	};

	struct CAMERA_DATA
	{
		int num;
		CAMERA_DATA *pNext;

		FLOAT3	  position;
		FLOAT3	  right;
		FLOAT3	  up;
		FLOAT3	  look;
		FLOAT     distance;
		FLOAT3    lookAt;

	};

	typedef unsigned int Camera;

	class CameraClass : public GEClass
	{
	public:
		inline CameraClass()
		{
		}

		inline CameraClass(const CameraClass&)
		{
		}

		inline~CameraClass()
		{
			Shutdown();
		}

		bool Initialize();
		void Shutdown();

		Camera CreateCamera(const CameraDesc&);
		bool   DeleteCamera(Camera);
		void   ClearCamera();

		bool   SetCamera(const Camera& para);
		Camera GetCamera()                      const { return m_camera->num; }

		void   SetPosition(float x, float y, float z)	   	{ m_camera->position = FLOAT3(x,y,z); }
		void   SetPosition(FLOAT3 para)	                	{ m_camera->position = para;          }

		inline FLOAT3 GetPosition()	     const  { return m_camera->position;          }
		inline FLOAT3 GetRight()		 const	{ return m_camera->right;             }
		inline FLOAT3 GetUp()	         const	{ return m_camera->up;                }
		inline FLOAT3 GetLook()		     const	{ return m_camera->look;              }
		inline FLOAT3 GetLookAt()	     const	{ return m_camera->lookAt;            }

		void MoveLook(float dist)       { m_camera->position += m_camera->look*dist;           }
		void MoveRight(float dist)      { m_camera->position += m_camera->right*dist;          }
		void MoveUp(float dist)         { m_camera->position += m_camera->up*dist;             }
		void MoveY(float dist)          { m_camera->position += FLOAT3(0.f, 1.f, 0.f)*dist;    }
		void MoveLook_XZ(float dist)    { m_camera->position += (m_camera->look * FLOAT3(1.0f, 0.0f, 1.0f)).GetNormalization() * dist; }
		void RotateRight(float radians);
		void RotateUp(float radians);
		void RotateY(float radians);
		//void ArcballX(float radians);
		//void Zoom(float dist);

		void SetLens(float, float, float, float);

		inline float GetFovY()		    const		{ return m_fovY; }
		inline float GetFovX()		    const		{ return atan(m_aspectRatio * tan(m_fovY * 0.5f)) * 2.f; }
		inline float GetaspectRatio()	const		{ return m_aspectRatio; }
		inline float GetNearZ()	        const		{ return m_nearZ; }
		inline float GetFarZ()	    	const		{ return m_farZ; }

		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
		void UpdateViewProjMatrix();

		inline MATRIX& GetViewMatrix()		      { return m_viewMatrix; }
		inline MATRIX& GetProjectionMatrix()	  { return m_projectionMatrix; }
		inline MATRIX& GetViewProjMatrix()        { return m_viewProjMatrix; }

	private:
		CAMERA_DATA *m_camera;
		CAMERA_DATA *m_camera_data;

		//float   m_moveV;
		//float   m_spinV;
		//float   m_zoomV;

		float	m_fovY;
		float	m_aspectRatio;
		float	m_nearZ;
		float	m_farZ;

		MATRIX m_viewMatrix;
		MATRIX m_projectionMatrix;
		MATRIX m_viewProjMatrix;
	};

	extern CameraClass *g_cameraClass;

	Camera GECreateCamera(const CameraDesc& para);
	bool   GEDeleteCamera(Camera para);
	void   GEClearCamera();
	bool   GESetCamera(const Camera& para);
	Camera GEGetCamera();

	FLOAT3 GEGetPosition();
	FLOAT3 GEGetRight();
	FLOAT3 GEGetUp();
	FLOAT3 GEGetLook();
	FLOAT3 GEGetLookAt();

	void GEMoveLook(float dist);
	void GEMoveRight(float dist);
	void GEMoveUp(float dist);
	void GEMoveY(float dist);
	void GEMoveLook_XZ(float dist);
	void GERotateRight(float radians);
	void GERotateUp(float radians);
	void GERotateY(float radians);

	void GEUpdateViewMatrix(void);
	void GEUpdateProjectionMatrix(void);
	void GEUpdateViewProjMatrix(void);
}

#endif