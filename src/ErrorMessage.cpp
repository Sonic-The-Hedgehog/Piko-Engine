/**
 * @file        ErrorMessage.cpp
 * @author      Robert Koch
 * @version     1.0
 * 
 * Implementation of the ErrorMessage class.
 *
 * @see ErrorMessage.h
 */
#include "../include/ErrorMessage.h"


namespace Piko {

    /*===================================================================*
     * PUBLIC MEMBERS                                                    *
     *===================================================================*/
    ErrorMessage::ErrorMessage(std::string msg, int code)
      :
      m_msg(msg),
      m_code(code) {

          m_oss << m_msg << " Error code: " << code;
    } 


    ErrorMessage::~ErrorMessage() {

    }


    std::string ErrorMessage::str() const {
        
        return m_oss.str();
    }
}