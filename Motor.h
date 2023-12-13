/*
 * Motor.h
 *
 *  Created on: Dec 13, 2023
 *      Author: minim
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

class Motor {
public:
    enum Status {
        Status_None = 0,
        Status_Run,
        Status_Error
    };

    enum MotorType {
        Panasonic_Type = 0,
        ZeroErr_Type,
        Robotis_Type,
        Hitec_Type
    };

    struct MotorSetting {
        uint8_t dir;
        uint16_t angle;
        uint16_t initPosi;
        uint16_t reducer_ratio;
    };

    virtual ~Motor() {}

    /* input 필수 기능 */
    // init
    virtual void setSettingInfo(uint8_t dir, uint16_t angle, uint16_t initPosi, uint16_t reducer_ratio) = 0;

    // control
    virtual void setPosition(uint16_t targetPosition) = 0;

    /* input 옵션 기능 */

    /* output 필수 기능*/
    virtual uint16_t getPosition() const = 0;
    /* output 옵션 기능 */

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

    // 부모 클래스 생성자에 의해 호출되는 초기화 함수
    Motor(uint8_t gID, uint8_t sID, MotorType motorType)
        : gID_(gID), sID_(sID), motorType_(motorType) {
    	operatingStatus_ = Status_None;
    }

private:
    Motor() = delete; // Motor Class 는 단독으로 사용할 수 없음.
};

#endif /* INC_MOTOR_H_ */
