/*
 * Curve.h
 *
 *  Created on: Dec 13, 2023
 *      Author: minim
 */

#ifndef CPP_DXL_CLASS_V2_CPP_MOTOR_CLASS_V2_CURVE_H_
#define CPP_DXL_CLASS_V2_CPP_MOTOR_CLASS_V2_CURVE_H_


class Curve {
public:
	Curve() {
	}

	/* Curve 사용 변수 초기화 */
	void Curve_Clear(void)
	{
		InitFlag = SET;
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		offsetX = 0;
		offsetY = 0;
		targetY = 0;

		TimeCnt = 0;
	}

	/* Curve 초기화 */
	void Curve_Init(int32_t currentCnt, int32_t targetCnt, int32_t targetTime, int32_t timeQuantum){

		float y1 = (float)currentCnt;
		float y2 = (float)targetCnt;//(float)homeCnt_ + (rangeCnt_ * (float)initPosi_/4095);
		float d1 = 0;
		float d2 = 0;
		if(InitFlag == SET) //Clear 가 선행되고 나서 진입할수 있다.
		{
			TimeRange = targetTime;
			TimeQuantum = timeQuantum;
			TimeQuantumCnt = TimeRange / TimeQuantum;
			TimeCnt = 0;
			Curve_Hermite3(y1,y2,d1,d2);
		}
	}

	/* 다항식 계수 생성 */
	void Curve_Hermite3(float y1,float y2,float d1,float d2){
		float x1, x2;
		x1 = 0;
		x2 = TimeRange;


		targetY = y2;

		offsetX=x1;
		offsetY=y1;

		float x = x2 - x1;
		float y = y2 - y1;

		a = 0;
		b = d1;
		float A = (b + d2)*x - 2*y;
		d = A/(x*x*x);
		c = (d2-b-3*d*x*x)/(2*x);
	}

	/* 호출마다 위치값 반환 */
	int32_t Curve_CalcHermiteY(uint32_t timeQuantum)
	{
		int32_t temp;
		float ret;
		float x1 = (float)TimeCnt;
		float x2 = x1*x1;
		float x3 = x2*x1;

		ret = a;
		ret += (b * x1);
		ret += (c * x2);
		ret += (d * x3);

		ret += offsetY;

		temp = (int32_t) ret;
		if(TimeCnt < TimeRange)
		{
			TimeCnt += (float)timeQuantum;
		}
		else
		{
			temp = targetY;
			InitFlag = RESET;//완료
		}
		return temp;
	}

private:
	unsigned char InitFlag;

	float a;
	float b;
	float c;
	float d;

	float offsetX, offsetY;

	int32_t targetY;

	int32_t TimeRange; //커브 시간
	int32_t TimeQuantum; //커브 키프레임
	int32_t TimeQuantumCnt; //키프레임 수

	int32_t TimeCnt;

};


#endif /* CPP_DXL_CLASS_V2_CPP_MOTOR_CLASS_V2_CURVE_H_ */
