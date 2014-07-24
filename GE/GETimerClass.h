#pragma once
#ifndef _GETIMERCLASS_H_
#define _GETIMERCLASS_H_

#include <windows.h>
#include "GEManageClass.h"

//-----------------------------------------------------------------------
namespace GE
{
	class TimerClass : public GEClass
	{
	public:
		TimerClass();
		TimerClass(const TimerClass&);
		~TimerClass();

		bool Initialize();
		void Shutdown();

		void Tick();				//计时一次，每一帧调用一次

		double TotalTime() const;	//返回定时器从开始计时到现在的总时间（不包含暂停时间），单位：秒
		double DeltaTime() const;	//返回本次计时与上次计时之间的时间差，单位：秒

		void Start();				//暂停后恢复计时
		void Stop();				//暂停
		void Reset();				//重置，开始计时，定时器开始工作时调用

		void ShowFPSInTitle();
		void ShowFPSInTitle(LPCWSTR _title);
	private:
		double	m_secsPerCount;		//系统有关，两个系统计数器之间的时间差值，单位：秒
		//这个变量是定时器把时间单位转换为“秒”的基准
		double	m_deltaTime;		//距离上次计时之间的时间差，单位：秒

		__int64 m_baseTime;			//定时器开始工作的起始时间点
		__int64 m_stopTime;			//如果当前为暂停状态，即指暂时的起始时刻
		__int64 m_pausedTime;		//暂停的总时间累计
		__int64	m_currTime;			//本次计时的时间点
		__int64	m_prevTime;			//上次计时的时间点

		bool	m_stopped;			//是否暂停
	};

	extern TimerClass* g_timerClass;

	void GEShowFPSInTitle();
	void GEShowFPSInTitle(LPCWSTR _title);
	double GEDeltaTime();
}

#endif