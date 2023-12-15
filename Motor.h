/*
 * Motor.h
 *
 *  Created on: Dec 13, 2023
 *      Author: minim
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "Curve.h"
#include "../cpp_tick/cpp_tick.h"

class Motor {
public:
    enum Status {
        Status_None = 0,		//초기상태

		/* 설정값 수신 */
		Status_SettingInfo,		//공통 설정값 수신완료
		Status_SettingData_op,	//설정값 op 수신완료
		Status_SettingData_1,	//설정값 1 수신완료
		Status_SettingData_2,	//설정값 2 수신완료
		Statis_SettingOk,		//모든 설정값 수신완료

		/* 모터 활성화 */
		Status_Init,			//초기화 진행
		Status_PreRun,			//초기화 완료, 위치 동기화x

		/* 위치 동기화 */
		Status_PosiSync_Ready,	//위치 동기화 준비
		Status_PosiSync_Move,	//위치 동기화

		/* 동작 가능 */
        Status_Run,				//위치 동기화 완료

		Status_Error,			//동작중 에러
		Status_InitError		//초기화 에러
    };

    enum MotorType {
        Panasonic_Type = 0,
        ZeroErr_Type,
        Robotis_Type,
        Hitec_Type
    };

    struct MotorSetting {
        uint8_t dir;
        float angle;
        uint16_t initPosi;
        uint16_t reducer_ratio;
    };

    struct Monitor {
    	int32_t mrs_current_posi;
    	int32_t raw_current_posi;
    	int32_t raw_command_posi;
    };
    // 부모 클래스 생성자에 의해 호출되는 초기화 함수

    ~Motor();


    /* input 필수 기능 */
    /* init */
    void setSettingInfo(uint8_t gid, uint8_t sid, uint8_t dir, uint16_t angle, uint16_t initPosi, uint16_t reducer_ratio);
    virtual void setSettingData_op(uint8_t gid, uint8_t sid, uint32_t data_1, uint32_t data_2) = 0;	//data_1, data_2는 모터에 따라 해석이 변경됨.

    /* control */
    virtual void setPosition(uint16_t targetPosition) = 0;
    virtual void setRawPosition(int32_t targetPosition) = 0;

    /* input 옵션 기능 */

    /* output 필수 기능*/
    Motor::Status getStatus(uint8_t sid, uint8_t gid);
    virtual uint16_t getPosition() const = 0;
    virtual int32_t getDefaultPosi() const = 0;
    /* output 옵션 기능 */

    /* 공통 funtion */
    virtual void init() = 0;

    void defaultPosi_Ready();
    void defaultPosi_Move();


    /* loop에서 반복 호출 필요 */
    void process();

protected:
    bool id_check(uint8_t gID, uint8_t sID) {
        if ((gID == gID_) && (sID == sID_)) {
            return true;
        }
        return false;
    }


    /* Motor Infomation */
    uint8_t gID_;
    uint8_t sID_;

    MotorType motorType_;
    Status operatingStatus_;

    /* Motor Setting */
    MotorSetting setting_;
    Monitor monitor_;

    Curve curve_;
    Tick curveTick_;

    Motor(uint8_t gID, uint8_t sID, MotorType motorType);

private:
    Motor() = delete; // Motor Class 는 단독으로 사용할 수 없음.
};

#endif /* INC_MOTOR_H_ */
