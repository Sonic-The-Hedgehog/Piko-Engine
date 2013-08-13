/**
 * @file        WindowBase.cpp
 * @author      Robert Koch
 * @version     1.0
 * 
 * Implementation of the WindowBase class.
 */
#include "../include/WindowBase.h"
#include "../include/ErrorMessage.h"

#include <sstream>



namespace Piko {

    /*===================================================================*
     * STATIC MEMBERS                                                    *
     *===================================================================*/

    const std::string WindowBase::CLASS_NAME_BASE = "WindowBase";


    std::map<HWND, WindowBase*> WindowBase::mWindowRegistry 
        = std::map<HWND, WindowBase*>();



    /*===================================================================*
     * PUBLIC MEMBERS                                                    *
     *===================================================================*/

    WindowBase::WindowBase(std::string title, int width, int height)
      : 
      m_hInstance(GetModuleHandle(0)),
      m_title(title), 
      m_width(width), 
      m_height(height),
      m_maxWidth(GetSystemMetrics(SM_CXSCREEN)),
      m_maxHeight(GetSystemMetrics(SM_CYSCREEN)),      
      m_isClosed(false),
      m_isFullscreen(false) {

        std::cout << "[WindowBase] Initialize window..." << std::endl;
        
        initWindowClass();
        createWindow();

        // Add to registry:
        mWindowRegistry.insert(std::pair<HWND, WindowBase *>(m_hWnd, this));    

        std::cout << "[WindowBase] Finished initialization." << std::endl;
    }


    WindowBase::~WindowBase() {

        std::cout << "Delete window." << std::endl;

        if(!UnregisterClassA(m_className.c_str(), m_hInstance)) {
            std::cerr << ErrorMessage("Could not unregister window class.").str() << std::endl;
        }
    }


    void WindowBase::show() const {

        ShowWindow(m_hWnd, SW_SHOW);
    }


    void WindowBase::close() {

        std::cout << "[WindowBase] Close window " << m_hWnd << std::endl;

        m_isClosed = true;
        DestroyWindow(m_hWnd);  // Send WM_DESTROY to message handler.
    
    }


    bool WindowBase::isClosed() const {

        return m_isClosed;
    }


    HWND WindowBase::getHandle() const {
        
        return m_hWnd;
    }


    void WindowBase::setTitle(std::string title) {
        
        m_title = title;
        SetWindowTextA(m_hWnd, m_title.c_str());
    }


    void WindowBase::setFullscreen(bool flag) {
        
        if((m_isFullscreen && flag) || (!m_isFullscreen && !flag)) {
            return;
        }

        DEVMODE fullscreenSettings;

        // Enable fullscreen mode:
        if(flag) {
            EnumDisplaySettings(NULL, 0, &fullscreenSettings);
            fullscreenSettings.dmPelsWidth = m_maxWidth;
            fullscreenSettings.dmPelsHeight = m_maxHeight;
            fullscreenSettings.dmBitsPerPel = 32;
            fullscreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

            SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
            SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
            SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, m_maxWidth, m_maxHeight, SWP_SHOWWINDOW);
            ChangeDisplaySettings(&fullscreenSettings, CDS_FULLSCREEN);
            ShowWindow(m_hWnd, SW_MAXIMIZE);

            m_isFullscreen = true;
        }

        // Enable window mode:
        else {
            SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, WS_EX_LEFT);
            SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
            ChangeDisplaySettings(NULL, CDS_RESET);
            SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, m_width, m_height, SWP_SHOWWINDOW);
            ShowWindow(m_hWnd, SW_RESTORE);

            m_isFullscreen = false;
        }
    }


    /*===================================================================*
     * PROTECTED MEMBERS                                                 *
     *===================================================================*/

    bool WindowBase::messageHandler(UINT msg, WPARAM wParam, LPARAM lParam) {

        //std::cout << "Incoming message " << msg << " for hwnd " << m_hWnd << std::endl;

        switch(msg) {
            case WM_DESTROY:
                if(!isClosed()) this->close();  // Prevent recursive call of DestroyWindow()
                return true;
            case WM_KEYDOWN:
                return onKeyDown(wParam);
            default:
                return false;
        }
    }


    bool WindowBase::onKeyDown(int keycode) {

        switch(keycode) {
            case VK_F1:
                if(m_isFullscreen) setFullscreen(false);
                else setFullscreen(true);
                return true;
            case VK_ESCAPE:
                close();
                return true;
            default:
                return false;
        }
    }



    /*===================================================================*
     * PRIVATE MEMBERS                                                   *
     *===================================================================*/

    LRESULT CALLBACK WindowBase::staticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

        //std::cout << "Dispatch message." << std::endl;

        auto seek = mWindowRegistry.find(hwnd);
        if(seek == mWindowRegistry.end()) {
            return DefWindowProc(hwnd, msg, wParam, lParam);        
        }

        WindowBase* window = seek->second;
        bool msgConsumed = window->messageHandler(msg, wParam, lParam);
   
        return msgConsumed ? NULL : DefWindowProc(hwnd, msg, wParam, lParam);
    }


    void WindowBase::initWindowClass() {

        std::ostringstream classNameStream;
        classNameStream << CLASS_NAME_BASE << this << std::endl;
        m_className = classNameStream.str();

        ZeroMemory(&m_wc, sizeof(WNDCLASSEXA));   

        // Set up window class:
        m_wc.cbSize = sizeof(WNDCLASSEX);                   // Structure size.
        m_wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;    // Class style.
        m_wc.lpfnWndProc = staticWndProc;                   // Callback for incoming messages.
        m_wc.cbClsExtra = 0;                                // No extra bytes.
        m_wc.cbWndExtra = 0;                                // No extra bytes.
        m_wc.hInstance = m_hInstance;                       // Set the instance.
        m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);       // Use default icon.
        m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);         // Use default cursor.
        m_wc.hbrBackground = NULL;                          // No background brush.
        m_wc.lpszMenuName = NULL;                           // No menu name.
        m_wc.lpszClassName = m_className.c_str();           // Set class name.
        m_wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);     // Use default small icon.

        std::cout << "[WindowBase] Register window, class=" << m_className << std::endl;

        // Register window class:
        if(!RegisterClassExA(&m_wc)) {
            throw std::runtime_error(
                ErrorMessage("Could not register window class.").str());
        }
    }


    void WindowBase::createWindow() {

        m_hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
            m_className.c_str(),
            m_title.c_str(),  
            WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
            0, 0,
            m_width,
            m_height,
            NULL,
            NULL,
            m_hInstance,
            (void *)this);

        if(!m_hWnd) {
            throw std::runtime_error(
                ErrorMessage("Could not register window class.").str());
        }
    }


} /* Namespace Piko */