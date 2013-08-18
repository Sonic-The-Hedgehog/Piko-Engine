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

          m_oss << m_msg;
          
          if(code == -987654321) m_oss << " System error code: " << GetLastError();
          else m_oss << " User error code: " << code; 
    } 

} /* Namespace Piko */