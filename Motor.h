



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

    Motor(){}
    virtual ~Motor(){}


    /* tx Data */

    /* rx Data */



protected :
    bool id_check(uint8_t gID, uint8_t sID){
        if( (gID == gID_) && (sID == sID_)) {
            return true;
        }               
        return false;
    }


private :
    /* Motor Infomation */
    uint8_t gID_;
    uint8_t sID_;

    
    

};