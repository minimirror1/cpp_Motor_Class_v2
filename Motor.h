
#include "main.h"

class Motor{

public : 
    enum Status {
        Status_None = 0,
        Status_Run,
        Status_Error
    };
    enum MotorType{
        Panasonic_Type = 0,
        ZeroErr_Type,
        Robotis_Type,
        Hitec_Type
    }

    
    virtual ~Motor(){}

    /* input 필수 기능 */
    virtual void setPosition(uint16_t targetPosition) = 0;
    /* input 옵션 기능 */

    /* output 필수 기능*/
    virtual uint16_t getPosition() const = 0;
    /* output 옵션 기능 */

protected :
    bool id_check(uint8_t gID, uint8_t sID){
        if( (gID == gID_) && (sID == sID_)) {
            return true;
        }               
        return false;
    }
private :
    
    Motor(){} //Motor Class 는 단독으로 사용할 수 없음.
    /* Motor Infomation */
    uint8_t gID_;
    uint8_t sID_;
};