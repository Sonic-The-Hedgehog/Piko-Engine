/**
 * @file        GLContext.h
 * @author      Robert Koch
 * @version     1.0
 *
 * Specification for for the wrapper class to create and maintain a device and rendering context 
 * for application using OpenGL. After creating an instance use init() to enable and dispose() to 
 * disable OpenGL.
 */
#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


namespace Piko {

    /**
    * Wrapper class to create and maintain a device and rendering context for application using 
    * OpenGL.
     */
    class GLContext {
    
        public:
            
            /**
             * Constructor to set up the contexts used.
             */
            GLContext();
    
            /**
             * Destructor to dispose the the contexts. Same effect as dispose().
             */ 
            ~GLContext();

            /**
             * Function to initialize the contexts so that OpenGL can be used.
             * 
             * @param hWnd Handle to the window in which the rendering should be done.
             */
            void init(HWND hWnd);

            /**
             * Function to dispose the contexts used by OpenGL.
             */
            void dispose();

            /**
             * Function to get the device context used for rendering.
             * 
             * @return Device context.
             */
            HDC getDeviceContext() const;
        

        private:
            
            HWND m_hWnd;    /**< Window on which the rendering should occure. */
            HDC m_hDC;      /**< Device context. */
            HGLRC m_hRC;    /**< Rendering context. */

    
    }; /* Class GLContext */

} /* Namespace Piko */


#endif // End of GLCONTEXT_H
