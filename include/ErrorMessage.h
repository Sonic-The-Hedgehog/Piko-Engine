/**
 * @file        ErrorMessage.h
 * @author      Robert Koch
 * @version     1.0
 * 
 * Simple helper class to create a nice string of error messages with specified error codes. 
 */
#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <windows.h>
#include <iostream>
#include <sstream>


namespace Piko {

    /**
     * Class to build a error message from a string and an error code as integer.
     */
    class ErrorMessage {

        public:

            /**
             * Constructor to create an error message from a specified error description and an
             * optional error code. If no error code was specified the return value of 
             * GetLastError() will be used instead (symbolized by the code -987654321).
             * 
             * @param msg Message to describe the error.
             * @param code User defined error code or return value of GetLastError() if no code was
             *             specified.
             */
            ErrorMessage(std::string msg, int code = -987654321);

            /**
             * Destructor.
             */
            ~ErrorMessage();

            /**
             * Function to get the build error message as a string.
             * 
             * @return Error message and error code as a string.
             */
            std::string str() const;

            /**
             * Function to have nice output, if appended to a stream.
             */
            friend std::ostream& operator<<(std::ostream& stream, const ErrorMessage& em) {
                return stream << em.m_oss.str();
            }

        private:

            std::ostringstream m_oss;   /**< Stream used to build the error message. */
            std::string m_msg;          /**< Text to describe the error. */
            int m_code;                 /**< Error code to print in conjunction with the text. */


    }; /* Class ErrorMessage */

} /* Namespace Piko */


#endif // End of ERRORMESSAGE_H