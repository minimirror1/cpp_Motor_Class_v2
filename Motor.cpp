#include "Motor.h"


Motor::Motor(uint8_t gID, uint8_t sID, MotorType motorType)
: gID_(gID), sID_(sID), motorType_(motorType) {
	operatingStatus_ = Status_None;
}

Motor::~Motor(){

}

void Motor::setSettingInfo(uint8_t dir, uint16_t angle, uint16_t initPosi, uint16_t reducer_ratio){
	if(operatingStatus_ == Status_PreRun){
		operatingStatus_ = Status_SettingInfo;

		setting_.dir = dir;
		setting_.angle = angle;
		setting_.initPosi = initPosi;
		setting_.reducer_ratio = reducer_ratio;
	}
}
void Motor::defaultPosi_Ready(){
	if(operatingStatus_ == Status_PreRun){
		operatingStatus_ = Status_PosiSync_Ready;

		curve_.Clear();
		int32_t targetCnt = getDefaultPosi();
		curve_.Init(monitor_.raw_current_posi, targetCnt, 5000, 20);
	}
}

void Motor::defaultPosi_Move(){
	if(operatingStatus_ == Status_PosiSync_Ready){
		operatingStatus_ = Status_PosiSync_Move;
		curveTick_.tickUpdate();
	}

	if(operatingStatus_ == Status_PosiSync_Move){
		if(curveTick_.delay(20)){
			int32_t result = 0;
			Curve::Curve_Status status = curve_.CalcHermiteY(20, &result);
			setRawPosition(result);

			if(status == Curve::Curve_Finish)
				operatingStatus_ = Status_Run;
		}
	}
}


void Motor::process(){

	/* 초기 위치 이동 체크 */
	defaultPosi_Ready();
	defaultPosi_Move();
}

