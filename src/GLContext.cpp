/**
 * @file        GLContext.cpp
 * @author      Robert Koch
 * @version     1.0
 *
 * Implementation of the GLContext class.
 */
#include "../include/GLContext.h"
#include "../include/ErrorMessage.h"


namespace Piko {

    /*===============================================*
     *  PUBLIC MEMBERS                               *
     *===============================================*/

    GLContext::GLContext() 
      :
      m_hWnd(NULL),
      m_hDC(NULL),
      m_hRC(NULL) {

    }


    GLContext::~GLContext() {

        dispose();
    }


    void GLContext::init(HWND hWnd) {

        std::cout << "[GLContext] Initialize OpenGL context." << std::endl;

        m_hWnd = hWnd;

        // Try to get device context
        if(!(m_hDC = GetDC(m_hWnd))) {
            throw std::runtime_error(
                ErrorMessage("Could not retrieve device context.").str());
        }

        // Setup of pixel format descriptor
        PIXELFORMATDESCRIPTOR pfd;
        ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
        
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 24;
        pfd.cDepthBits = 16;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pixelFormat;
        if(!(pixelFormat = ChoosePixelFormat(m_hDC, &pfd))) {
            throw std::runtime_error(
                ErrorMessage("Could not choose pixel format.").str());
        }

        if(!SetPixelFormat(m_hDC, pixelFormat, &pfd)) {
            throw std::runtime_error(
                ErrorMessage("Could not set pixel format.").str());
        }

        // Setup contexts
        if(!(m_hRC = wglCreateContext(m_hDC))) {
            throw std::runtime_error(
                ErrorMessage("Could not create rendering context.").str());
        }

        if(!wglMakeCurrent(m_hDC, m_hRC)) {
            throw std::runtime_error(
                ErrorMessage("Could not activate rendering context.").str());
        }
    }


    void GLContext::dispose() {

        std::cout << "[GLContext] Dispose OpenGl conext." << std::endl;

        if(m_hRC) {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(m_hRC);
        }

        if(m_hWnd && m_hDC) {
            ReleaseDC(m_hWnd, m_hDC);
        }

        m_hWnd = NULL;
        m_hDC = NULL;
        m_hRC = NULL;
    }


    HDC GLContext::getDeviceContext() const {
        
        return m_hDC;
    }

} /* Namespace Piko */