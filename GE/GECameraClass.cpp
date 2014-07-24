#include "GECameraClass.h"

namespace GE
{
	CameraClass* g_cameraClass;

	//-----------------------------------------------------------------------
	bool CameraClass::Initialize()
	{
		m_camera_data = new CAMERA_DATA;
		m_camera_data->num = 0;
		m_camera_data->pNext = NULL;
		m_camera_data->position = FLOAT3(-30.0f, 0.0f, 0.0f);
		m_camera_data->right = FLOAT3(1.0f, 0.0f, 0.0f);
		m_camera_data->up = FLOAT3(0.0f, 1.0f, 0.0f);
		m_camera_data->look = FLOAT3(0.0f, 0.0f, 1.0f);
		m_camera_data->distance = 1.0f;
		m_camera_data->lookAt = m_camera_data->position + m_camera_data->look * m_camera_data->distance;

		m_camera = m_camera_data;

		SetLens(GE_PI * 0.5, (float)m_width/(float)m_height, 0.1f, 10000.0f);

		UpdateViewProjMatrix();
		//m_viewMatrix = MATRIX::IDENTITY;
		//m_projectionMatrix = MATRIX::IDENTITY;
		//m_viewProjMatrix = MATRIX::IDENTITY;
		return true;
	}

	//-----------------------------------------------------------------------
	void CameraClass::Shutdown()
	{
		CAMERA_DATA *tempD;
		while( m_camera_data )
		{
			tempD = m_camera_data;
			m_camera_data = m_camera_data->pNext;
			delete tempD;
		}
	}

	//-----------------------------------------------------------------------
	Camera CameraClass::CreateCamera(const CameraDesc& desc)
	{
		Camera result;
		CAMERA_DATA *tempM = m_camera_data;
		while( tempM->pNext )
			tempM = tempM->pNext;
		result = tempM->num + 1;

		tempM->pNext = new CAMERA_DATA;
		tempM = tempM->pNext;
		tempM->num = result;
		tempM->pNext = NULL;
		tempM->position = desc.position;
		tempM->right = desc.right;
		tempM->up = desc.up;
		tempM->look = desc.look;
		tempM->distance = desc.distance;
		tempM->lookAt = m_camera_data->position + m_camera_data->look * m_camera_data->distance;

		return result;
	}

	//-----------------------------------------------------------------------
	bool CameraClass::DeleteCamera(Camera para)
	{
		if( para == 0 )
			return false;

		CAMERA_DATA *tempM = m_camera_data;
		while( tempM->pNext->num != para && tempM->pNext->pNext )
			tempM = tempM->pNext;
		if( tempM->pNext->num != para)
			return false;
		if( tempM->pNext == m_camera )
			m_camera = m_camera_data;

		CAMERA_DATA *tempD = tempM->pNext;
		tempM->pNext = tempM->pNext->pNext;
		delete tempD;

		return true;
	}

	//-----------------------------------------------------------------------
	void CameraClass::ClearCamera()
	{
		CAMERA_DATA *tempM = m_camera_data->pNext;
		CAMERA_DATA *tempD;
		while( tempM )
		{
			tempD = tempM;
			tempM = tempM->pNext;
			delete tempD;
		}

		m_camera_data->pNext = NULL;
		m_camera = m_camera_data;
	}

	//-----------------------------------------------------------------------
	bool CameraClass::SetCamera(const Camera& para)
	{
		CAMERA_DATA *tempM = m_camera_data;
		while( tempM->pNext->num != para && tempM->pNext->pNext )
			tempM = tempM->pNext;
		if( tempM->pNext->num != para)
			return false;

		m_camera = tempM->pNext;
		return true;
	}

	//-----------------------------------------------------------------------
	void CameraClass::RotateRight(float radians)
	{
		MATRIX rotation = MatrixRotationAxisN(m_camera->right, radians);
		(m_camera->up *= rotation).Normalise();
		(m_camera->look *= rotation).Normalise();
	}

	//-----------------------------------------------------------------------
	void CameraClass::RotateUp(float radians)
	{
		MATRIX rotation = MatrixRotationAxisN(m_camera->up, radians);
		(m_camera->right *= rotation).Normalise();
		(m_camera->look *= rotation).Normalise();
	}

	//-----------------------------------------------------------------------
	void CameraClass::RotateY(float radians)
	{
		MATRIX rotation = MatrixRotationAxisN(FLOAT3(0.0f, 1.0f, 0.0f), radians);

		(m_camera->up *= rotation).Normalise();
		(m_camera->right *= rotation).Normalise();
		(m_camera->look *= rotation).Normalise();
	}

	//-----------------------------------------------------------------------
	void CameraClass::SetLens(float fovY, float aspectRatio, float nearZ, float farZ)
	{
		m_fovY = fovY;
		m_aspectRatio = aspectRatio;
		m_nearZ = nearZ;
		m_farZ = farZ;
	}

	//-----------------------------------------------------------------------
	void CameraClass::UpdateViewMatrix()
	{
		m_camera->right = ((m_camera->up).CrossProduct(m_camera->look)).GetNormalization();
		m_camera->up = ((m_camera->look).CrossProduct(m_camera->right)).GetNormalization();
		m_camera->look = (m_camera->look).GetNormalization();
		FLOAT x = m_camera->position.DotProduct(m_camera->right);
		FLOAT y = m_camera->position.DotProduct(m_camera->up);
		FLOAT z = m_camera->position.DotProduct(m_camera->look);
		m_viewMatrix(0,0) = m_camera->right.x;	m_viewMatrix(0,1) = m_camera->up.x;	m_viewMatrix(0,2) = m_camera->look.x;	m_viewMatrix(0,3) = 0;
		m_viewMatrix(1,0) = m_camera->right.y;	m_viewMatrix(1,1) = m_camera->up.y;	m_viewMatrix(1,2) = m_camera->look.y;	m_viewMatrix(1,3) = 0;
		m_viewMatrix(2,0) = m_camera->right.z;	m_viewMatrix(2,1) = m_camera->up.z;	m_viewMatrix(2,2) = m_camera->look.z;	m_viewMatrix(2,3) = 0;
		m_viewMatrix(3,0) = -x;		     	    m_viewMatrix(3,1) = -y;		        m_viewMatrix(3,2) = -z;			        m_viewMatrix(3,3) = 1;

		m_viewProjMatrix = m_viewMatrix * m_projectionMatrix;
	}

	//-----------------------------------------------------------------------
	void CameraClass::UpdateProjectionMatrix()
	{
		m_projectionMatrix = MatrixPerspectiveFovLH(m_fovY, m_aspectRatio, m_nearZ, m_farZ);

		m_viewProjMatrix = m_viewMatrix * m_projectionMatrix;
	}

	//-----------------------------------------------------------------------
	void CameraClass::UpdateViewProjMatrix()
	{
		m_camera->right = ((m_camera->up).CrossProduct(m_camera->look)).GetNormalization();
		m_camera->up = ((m_camera->look).CrossProduct(m_camera->right)).GetNormalization();
		m_camera->look = (m_camera->look).GetNormalization();
		FLOAT x = m_camera->position.DotProduct(m_camera->right);
		FLOAT y = m_camera->position.DotProduct(m_camera->up);
		FLOAT z = m_camera->position.DotProduct(m_camera->look);
		m_viewMatrix(0,0) = m_camera->right.x;	m_viewMatrix(0,1) = m_camera->up.x;	m_viewMatrix(0,2) = m_camera->look.x;	m_viewMatrix(0,3) = 0;
		m_viewMatrix(1,0) = m_camera->right.y;	m_viewMatrix(1,1) = m_camera->up.y;	m_viewMatrix(1,2) = m_camera->look.y;	m_viewMatrix(1,3) = 0;
		m_viewMatrix(2,0) = m_camera->right.z;	m_viewMatrix(2,1) = m_camera->up.z;	m_viewMatrix(2,2) = m_camera->look.z;	m_viewMatrix(2,3) = 0;
		m_viewMatrix(3,0) = -x;		     	    m_viewMatrix(3,1) = -y;		        m_viewMatrix(3,2) = -z;			        m_viewMatrix(3,3) = 1;

		m_projectionMatrix = MatrixPerspectiveFovLH(m_fovY, m_aspectRatio, m_nearZ, m_farZ);

		m_viewProjMatrix = m_viewMatrix * m_projectionMatrix;
	}

	//-----------------------------------------------------------------------
	Camera GECreateCamera(const CameraDesc& para) { return g_cameraClass->CreateCamera(para); }

	//-----------------------------------------------------------------------
	bool GEDeleteCamera(Camera para) { return g_cameraClass->DeleteCamera(para); }

	//-----------------------------------------------------------------------
	void GEClearCamera() { g_cameraClass->ClearCamera(); }

	//-----------------------------------------------------------------------
	bool GESetCamera(const Camera& para) { return g_cameraClass->SetCamera(para); }

	//-----------------------------------------------------------------------
	Camera GEGetCamera() { return g_cameraClass->GetCamera(); }

	//-----------------------------------------------------------------------
	FLOAT3 GEGetPosition() { return g_cameraClass->GetPosition(); }

	//-----------------------------------------------------------------------
	FLOAT3 GEGetRight() { return g_cameraClass->GetRight(); }

	//-----------------------------------------------------------------------
	FLOAT3 GEGetUp()  { return g_cameraClass->GetUp(); }

	//-----------------------------------------------------------------------
	FLOAT3 GEGetLook() { return g_cameraClass->GetLook(); }

	//-----------------------------------------------------------------------
	FLOAT3 GEGetLookAt() { return g_cameraClass->GetLookAt(); }

	//-----------------------------------------------------------------------
	void GEMoveLook(float dist) { g_cameraClass->MoveLook(dist); }

	//-----------------------------------------------------------------------
	void GEMoveRight(float dist) { g_cameraClass->MoveRight(dist); }

	//-----------------------------------------------------------------------
	void GEMoveUp(float dist) { g_cameraClass->MoveUp(dist); }

	//-----------------------------------------------------------------------
	void GEMoveY(float dist) { g_cameraClass->MoveY(dist); }

	//-----------------------------------------------------------------------
	void GEMoveLook_XZ(float dist) { g_cameraClass->MoveLook_XZ(dist); }

	//-----------------------------------------------------------------------
	void GERotateRight(float radians) { g_cameraClass->RotateRight(radians); }

	//-----------------------------------------------------------------------
	void GERotateUp(float radians) { g_cameraClass->RotateUp(radians); }

	//-----------------------------------------------------------------------
	void GERotateY(float radians) { g_cameraClass->RotateY(radians); }

	//-----------------------------------------------------------------------
	void GEUpdateViewMatrix(void) { g_cameraClass->UpdateViewMatrix(); }

	//-----------------------------------------------------------------------
	void GEUpdateProjectionMatrix(void) { g_cameraClass->UpdateProjectionMatrix(); }

	//-----------------------------------------------------------------------
	void GEUpdateViewProjMatrix(void) { g_cameraClass->UpdateViewProjMatrix(); }
}