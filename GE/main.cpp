#include "GE.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	GEDesc GEdesc;
	GEdesc.applicationName = L"²âÊÔ";
	GEdesc.isFullScreen = false;
	GEdesc.width = 800;
	GEdesc.height = 600;
	GEdesc.isSSAA = true;
	GEdesc.isVsync = false;

	if( !GEInitialize(GEdesc) )
		return 0;

	WaveFile wave;
	GELoadWaveFile(L"sound/gy.wav", wave);
	GEPlayWave(wave);

	ID3D11Device *device = GEGetDevice();

	ID3D11ShaderResourceView *starTex;
	if ( FAILED(D3DX11CreateShaderResourceViewFromFile(device, L"Texture/×¼ÐÇ.png",0,0,&starTex,0)) )
	return 0;

	QuadMesh star;
	GECreateQuad(350, 250, 100, 100, starTex, star);
	
	MazeClass test2(50, 50);
	MazeMesh test3;
	GECreateMaze(30.0f, 30.0f, 30.0f, test2, test3);
	/*
	ColorMesh test;
	GECreateBox(3.0f, 3.0f, 3.0f, test);

	ColorMesh sphere;
	GECreateSphere(10.0f, 10, 10, GE_BLUE, sphere);
	*/
	ID3D11ShaderResourceView *cubeMap;
	if ( FAILED(D3DX11CreateShaderResourceViewFromFile(device,L"Texture/cube1024.dds",0,0,&cubeMap,0)) )
	return 0;
	CubeMapMesh cube;
	GECreateSphere(1000.0f, 3, 3, cubeMap, cube);
	/*
	ID3D11ShaderResourceView *modelTexView;
	D3DX11CreateShaderResourceViewFromFile(device,L"model/diffuse.jpg",0,0,&modelTexView,0);
	TexMesh_File model;
	GELoadMeshFromFile(L"model/model.txt", modelTexView, model);

	ID3D11ShaderResourceView *snowTex;
	D3DX11CreateShaderResourceViewFromFile(device,L"Texture/particle/particle.dds",0,0,&snowTex,0);
	SnowMesh snow;
	GECreateSnow(FLOAT3(0.0f, 5.0f, 0.0f), 100, 50, 1000, GE_WHITE, snowTex, snow);
	*/
	int& deltaX = GEGetOnDeltaX();
	int& deltaY = GEGetOnDeltaY();

	GESetRState(DISABLECULL_RS);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	float speed = 50.f;
	float halfSpeed = speed/2;

	INT2 centre = GEGetOutsideCentre();

	bool isRun = true;
	while(isRun)
	{
		g_timerClass->Tick();
		GEShowFPSInTitle(L"- -");
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT || g_inputClass->IsKeyDown(VK_ESCAPE))
		{
			isRun = false;
		}
		else
		{
			GEBeginScene(GE_SILVER);

			float delta = (float)GEDeltaTime();

			GERotateY(GEDegreesToRadians(0.2f*(deltaX)));
			GERotateRight(GEDegreesToRadians(0.2f*(deltaY)));
			SetCursorPos(centre.x, centre.y);
			deltaX = 0;
			deltaY = 0;

			FLOAT3 pos = g_cameraClass->GetPosition();
			if( GEIsKeyDown('W') )
			{
				GEMoveLook_XZ(speed*delta);
			}
			else if( GEIsKeyDown('S') )
			{
				GEMoveLook_XZ(-speed*delta);
			}
			else if( GEIsKeyDown('A') )
			{
				GEMoveRight(-speed*delta);
			}
			else if( GEIsKeyDown('D') )
			{
				GEMoveRight(speed*delta);
			}

			if( GEIsKeyDown('E') )
			{
				static bool on_off = true;
				on_off = !on_off;
				GESetFogParameters(GE_SILVER, 0.f, 200.f, on_off, on_off);
			}

			/*
			if( GEIsKeyDown('R') )
			{
				static FLOAT3 pos = g_cameraClass->GetPosition();
				static bool up_down = true;
				up_down = !up_down;
				if( up_down )
				{
					g_cameraClass->SetPosition(
				}
			}
			*/

			if( GEIsKeyDown(VK_SPACE) )
			{
				GEMoveY(speed*delta);
			}
			else if( GEIsKeyDown('C') )
			{
				GEMoveY(-speed*delta);
			}

			GEUpdateViewMatrix();

			if( !GESetPerFrameParameters(MatrixInverse(g_cameraClass->GetViewMatrix()) , g_cameraClass->GetPosition(), delta) )
				return false;

			GERender(cube);

			GERender(test3);

			//GERender(snow);
			//GERender(test);
			//GERender(sphere);
			//GERender(model);

			GERender(star);

			GEPrint(20.0f, 20.0f, FLOAT4(1.0f, 1.0f, 0.0f, 1.0f), "hello world");

			GEEndScene();
		}
	}

	GEShutdown();
	return 0;
}