/**
 * @file        WindowBase.h
 * @author      Robert Koch
 * @version     1.0
 * 
 * Declaration of a class to simplify the window creation process using the winapi.
 */
#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <iostream>
#include <map>
#include <windows.h>


namespace Piko {

    /**
     * Wrapper class to create windows build on top of the winapi.
     */
    class WindowBase {

        public:

            /**
             * Constructor to create a window the the specified title and optional size.
             * 
             * @param title Window title showing up on the upper border.
             * @param width Window width.
             * @param height Window height.
             */
            WindowBase(std::string title, 
                       int width = GetSystemMetrics(SM_CXSCREEN)/2, 
                       int height = GetSystemMetrics(SM_CYSCREEN)/2);

            /**
             * Destructor which removes the window from registry and resets the window handle.
             */
            virtual ~WindowBase();

            /**
             * Function to show the window on the screen.
             */
            void show() const;

            /**
             * Function to close and destroy the window.
             */
            void close();

            /**
             * Function to check if the window is closed.
             *
             * @return True if the window is closed, otherwise false.
             */
            bool isClosed() const;

            /**
             * Function to get the window handle.
             * 
             * @return Window handle.
             */
            HWND getHandle() const;
            
            /**
             * Function to set the window title.
             * 
             * @param title New window title.
             */
            virtual void setTitle(std::string title) final;

            /**
             * Function to switch the window between fullscreen and window mode.
             *
             * @param flag If set to true the window will switch to fullscreen mode, otherwise
             *             it will change to window mode instead. 
             */
            virtual void setFullscreen(bool flag) final;


        protected:            

            /**
             * Function to handle incoming messages.
             *
             * @param msg Code of incoming message.
             * @param wParam
             * @param lParam
             */
            virtual bool messageHandler(UINT msg, WPARAM wParam, LPARAM lParam);

            /**
             * Function to handle the event when a key was pressed. It is recommended to override
             * this function for a custom behaviour.
             * 
             * @param keycode Key code to identify the pressed key.
             * 
             * @return True if corresponding event message will be consumed, otherwise false for 
             *         further handling.
             */
            virtual bool onKeyDown(int keycode);


        private:

            /** 
             * Window base class name. Each window appends its memory adress to this name for a 
             * unique class name. 
             **/
            static const std::string CLASS_NAME_BASE;

            /** Mapping of window handles to actual window instances. */
            static std::map<HWND, WindowBase *> mWindowRegistry;

            HINSTANCE m_hInstance;      /**< Handle for the application instance. */
            HWND m_hWnd;                /**< Handle to the window. */
            WNDCLASSEXA m_wc;           /**< Window class structure. */

            std::string m_title;        /**< Window title. */
            std::string m_className;    /**< Name of the window class. */

            int m_width;                /**< Window width. */
            int m_height;               /**< Window height. */
            int m_maxWidth;             /**< Maximum window width. */
            int m_maxHeight;            /**< Maximum window height. */

            bool m_isClosed;            /**< Flag to indicate if the window is closed. */
            bool m_isFullscreen;        /**< Flag to indicate if window is in fullscreen mode. */


            /**
             * Function to dispatch sent messages to the right window instance.
             * 
             * @param hwnd Handle to the window which reveives the message.
             * @param msg Message sent.
             * @param wParam 
             * @param lParam
             */
            static LRESULT CALLBACK staticWndProc(HWND hwnd, 
                                                  UINT msg, 
                                                  WPARAM wParam, 
                                                  LPARAM lParam);

            /**
             * Function to initialize the window class structure.
             */
            void initWindowClass();

            /**
             * Function to create the window setting the window handle.
             */
            void createWindow();

            /**
             * Copy constructor is forbidden.
             */
            WindowBase(const WindowBase& wnd);

            /**
             * Assignment operator is forbidden.
             */
            WindowBase& operator=(const WindowBase& wnd);


    }; /* Class WindowBase */

} /* Namespace Piko */


#endif // End of WINDOWBASE_H