//
//  KPlotWindow.cpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/10/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//

#include "KPlotWindow.hpp"

#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
//#include <unistd.h>

#define NULL_TAB_IDENTIFIER "KPLOT RESERVED NAME null_tab DONT USE THIS NAME!"

using namespace std;

bool KPlotWindow::lshift_pressed = false;
bool KPlotWindow::rshift_pressed = false;
std::mutex KPlotWindow::all_windows_mutex; // = std::mutex();
std::vector<KPlotWindow*> KPlotWindow::all_windows = std::vector<KPlotWindow*>();

/*
 Default constructor
 */
KPlotWindow::KPlotWindow() : KPlotWindow(800, 600, "IEGA Plot") {
    
}

/*
 Constructor - specify dimensions and windows name
 
 width - window width (in pixels)
 height - window height (in pixels)
 title - window title
 */
KPlotWindow::KPlotWindow(int nwidth, int nheight, std::string title) : scan_events(true), window(sf::VideoMode(nwidth, nheight), title, sf::Style::Default, sf::ContextSettings(0, 0, 8)){
    
//    Add instance to all_windows
    all_windows_mutex.lock();
    all_windows.push_back(this);
    univ_id = all_windows.size()-1;
    all_windows_mutex.unlock();
    
    sf::Image icon;
    if (!icon.loadFromFile(string(APPICON_PATH) + "IEGA_Oval_Logo_Border.png")) {
//        return EXIT_FAILURE;
    }else{
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    
    
    std::lock_guard<std::mutex> guard(mtx);
    show_toolbar = true;
    show_tabbar = false;
    active_tab = -1;
    window_style = KP_WSTYLE_CLASSIC;
    
    KPlotWindow::width = nwidth;
    KPlotWindow::height = nheight;
    
    null_tab.tab_title = NULL_TAB_IDENTIFIER;
    
    //c out << "ACTIVE TAB FROM WITHIN WINDOW CONSTRUCTOR " << getActiveTab() << endl;
}

KPlotWindow::~KPlotWindow(){
    close();
}

bool KPlotWindow::isOpen(){
    return window.isOpen();
}

sf::RenderWindow& KPlotWindow::getWindow(){
    return window;
}

void KPlotWindow::close(){

    window.close();
    
    all_windows_mutex.lock();
    all_windows[univ_id] = NULL;
    all_windows_mutex.unlock();

    scan_events = false;
    window.close();
}

/*
 Add a KPlotTab to the window. Assigns a defualt name to the tab
 
 tab - KPlotTab to add.
 
 Void return
 */
void KPlotWindow::add_tab(KPlotTab tab){
    
    string title("Tab ");
    title = title + to_string(tabs.size());
    
    KPlotWindow::add_tab(tab, title);
}

/*
 Add a KPlotTab to the window.
 
 tab - KPlotTab to add.
 tab_title - title of new tab
 
 Void return
 */
void KPlotWindow::add_tab(KPlotTab kptab, std::string tab_title_str){
    
    kptab.tab_title = tab_title_str;
    KPlotWindow::tabs.push_back(kptab);
    
}

/*
 Deletes the first tab by the name 'tab_title'.
 
 tab_title - title of tab to delete
 
 Returns true if specified tab found and deleted.
 */
bool KPlotWindow::delete_tab(std::string tab_title){
    
    //Scan for name
    for (int i = 0 ; i < KPlotWindow::tabs.size() ; i++){
        if (KPlotWindow::tabs[i].tab_title == tab_title){
            KPlotWindow::tabs.erase(KPlotWindow::tabs.begin() + i); //Delete tab if found
            return true;
        }
    }
    
    return false;
}

/*
 Deletes the tab specified by idx.
 
 idx - index of the tab to delete.
 
 Returns true if tab found and deleted
 */
bool KPlotWindow::delete_tab(int idx){
    
    //Ensure no overflow
    if (idx >= KPlotWindow::tabs.size() || idx < 0){
        return false;
    }
    
    //Delete tab
    KPlotWindow::tabs.erase( KPlotWindow::tabs.begin() + idx );
    
    return true;
}

/*
 Searches for the tab specified by 'tab_title'. Returns a reference to that tab if found, else returns a returns any KPlotTab tab & reports false via 'success' arg.
 
 tab_title - title of tab for which to search
 success - set to true if found, else set to false
 
 Returns reference to specified tab (if found).
 */
KPlotTab& KPlotWindow::tab(std::string tab_title, bool& success){
    
    //Scan for name
    for (int i = 0 ; i < KPlotWindow::tabs.size() ; i++){
        if (KPlotWindow::tabs[i].tab_title == tab_title){
            success = true;
            return KPlotWindow::tabs[i];
        }
    }
    
    //Tab not found
    success = false;
    return null_tab;
    
}

/*
 Searches for the tab specified by 'idx'. Returns a reference to that tab if found, else returns a returns any KPlotTab tab & reports false via 'success' arg.
 
 idx - index of tab for which to search
 success - set to true if found, else set to false
 
 Returns reference to specified tab (if found).
 */
KPlotTab& KPlotWindow::tab(int idx, bool& success){
    
    //Check bounds
    if (idx >= tabs.size() || idx < 0){
        success = false;
        return null_tab;
    }
    
    //Return tabs
    success = true;
    return tabs[idx];
    
}

void KPlotWindow::setWindowSize(unsigned int x_size, unsigned int y_size){
    window.setSize(sf::Vector2u(x_size, y_size));
}

/*
 Set properties for the class
 
 prop - property to set
 val - value of property
 
 Void return
 */
void KPlotWindow::set(int prop, bool val){
    
    switch(prop){
        case(KP_SET_SHOW_TOOLBAR):{
                lock_guard<std::mutex> guard(mtx);
                show_toolbar = val;
            }
            break;
        case(KP_SET_SHOW_TABBAR):{
                lock_guard<std::mutex> guard(mtx);
                show_tabbar = val;
            }
            break;
    }
    
}

/*
 Set properties for the class
 
 prop - property to set
 val - value of property
 
 Void return
 */
void KPlotWindow::set(int prop, int val){
    switch(prop){
        case(KP_SET_ACTIV_TAB):{
                lock_guard<std::mutex> guard(mtx);
                active_tab = val;
            }
            break;
        case(KP_SET_WSTYLE):{
                lock_guard<std::mutex> guard(mtx);
                window_style = val;
                for (int t = 0 ; t < tabs.size() ; t++){
                    for (int g = 0; g < tabs[t].numGraphs() ; g++){
                        bool success;
                        tabs[t].getGraph(g, success); //Just ensure graph is available
                        if (success){
                            implement_style(window_style, tabs[t].getGraph(g, success).options); //Overwrite graph settings with new settings
                        }
                    }
                }
            
            }
            break;
    }
}

/*
 Set properties for the class
 
 prop - property to set
 val - value of property
 
 Void return
 */
void KPlotWindow::set(int prop, std::string val){
    switch(prop){
        case(KP_SET_ACTIV_TAB):
            
            active_tab = -1;
            
            //Scan for name
            bool success = false;
            for (int i = 0 ; i < KPlotWindow::tabs.size() ; i++){
                if (KPlotWindow::tabs[i].tab_title == val){
                    lock_guard<std::mutex> guard(mtx);
                    active_tab = i;
                    break; //Break for loop
                }
            }
            break;
    }
}

int KPlotWindow::getActiveTab(){
    return active_tab;
}

/*
 Tell KPlotWindow to update the window. This involves:
    1. Drawing tool bar (if set)
    2. Drawing tab bar (if set)
    3. Drawing any active tabs
 
 TODO: The whole thing
 
 */
void KPlotWindow::draw_window(){
    
    bool success;//temporary
    //c out << "Traces size inside draw_window immediately after called in event loop " << getTab(0).getGraph(0, success).traces.size() << endl;
    
    //Determine tab bounds
    int lbound = .1*width;
    int rbound = .9*width;
    int tbound = .15*height;
    int bbound = .8*height;
    
    lock_guard<std::mutex> guard(mtx);
    
    //Begin with window clear
    window.clear();
    if (window_style == KP_WSTYLE_BLUEWAVE){
        //Draw background
        sf::RectangleShape background(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(74, 84, 99));
        background.setPosition(0, 0);
        window.draw(background);
        
        //Draw Menubar
        sf::RectangleShape menu_bar(sf::Vector2f(width*.98, height*.1));
        menu_bar.setFillColor(sf::Color(0, 68, 255));
        menu_bar.setPosition(width*.01, height*.01);
        window.draw(menu_bar);
    }else if(window_style == KP_WSTYLE_CLASSIC_SIMPLEX){
        //Draw background
        sf::RectangleShape background(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(249, 249, 250));
        background.setPosition(0, 0);
        window.draw(background);
        
        //Adjust bounds
        lbound = .05*width;
        rbound = .95*width;
        tbound = .05*height;
        bbound = .95*height;
        
    }else{ //KP_WSTYLE_CLASSIC
        //Draw background
        sf::RectangleShape background(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(249, 249, 250));
        background.setPosition(0, 0);
        window.draw(background);
        
        //Draw Tabbar
        if (KPlotWindow::tabs.size() > 1){ //Draw tab bar and menu bar
            
            //Draw reduced size menubar
            sf::RectangleShape menu_bar(sf::Vector2f(width*.98, height*.06));
            menu_bar.setFillColor(sf::Color(190, 192, 192));
            menu_bar.setPosition(width*.01, height*.01);
            window.draw(menu_bar);
            
            //Draw tab bar buttons
            
            sf::CircleShape button1(height*.02);
            button1.setFillColor(sf::Color(100, 250, 50));
            button1.setScale(4, 1);
            button1.setPosition(width*.01, height*.08);
            
            float radius_x=20;
            float radius_y=20;
            unsigned short quality=70;
            int sep = 50;
            
            sf::ConvexShape ellipse;
            ellipse.setPointCount(quality);
            
            for(unsigned short i=0;i<quality/2;++i){
                float rad=(6.283185307/quality*i-1.5707963268);
                float x=cos(rad)*radius_x;
                float y=sin(rad)*radius_y;
                
                ellipse.setPoint(i,sf::Vector2f(x+sep,y));
            };
            for(unsigned short i = quality/2 ; i < quality ; ++i ){
                float rad=(6.283185307/quality*i-1.5707963268);
                float x=cos(rad)*radius_x;
                float y=sin(rad)*radius_y;
                
                ellipse.setPoint(i,sf::Vector2f(x,y));
            };
            ellipse.setFillColor(sf::Color::Black);
            ellipse.setPosition(100,100);
            
            
            sf::RectangleShape tab_bar(sf::Vector2f(width*.98, height*.04));
            tab_bar.setFillColor(sf::Color(190, 192, 192));
            tab_bar.setPosition(width*.01, height*.08);
            window.draw(tab_bar);
            window.draw(button1);
            window.draw(ellipse);
        }else{ //No tab bar - draw full size menu bar
            
            //Draw Menubar
            sf::RectangleShape menu_bar(sf::Vector2f(width*.98, height*.1));
            menu_bar.setFillColor(sf::Color(190, 192, 192));
            menu_bar.setPosition(width*.01, height*.01);
            window.draw(menu_bar);
            
        }
    }
    
    //===========================================================================================
    //===================================== Draw active tab =====================================
    
    vector<shared_ptr<sf::Drawable> > drawings;
    
    //c out << "The window is now drawing the tab. Number of tabs (tabs.size(): " << tabs.size() << ")" << endl;
    //c out << "tabs[0].graphs[0].traces.size() : " << tabs[0].graphs[0].traces.size() << endl;
    //c out << "tabs[0].graphs[0].traces.size() when called with function: " << getTab(0).getGraph(0, success).traces.size() << endl;
    //c out << "tabs[0].graphs[0].traces.size() when called with graph function: " << tabs[0].getGraph(0, success).traces.size() << endl;
    //c out << "tabs[0].graphs[0].traces.size() when called with tab function: " << getTab(0).graphs[0].traces.size() << endl;
//    //c out << "tabs[0].graphs[0].traces.size() when called with null_tab: " << null_tab.graphs[0].traces.size() << endl;
    if (active_tab >= 0){ //Check if active tab is manually set
        if (getTab(active_tab).tab_title != NULL_TAB_IDENTIFIER){
            getTab(active_tab).draw_tab(window, lbound, rbound, tbound, bbound, window_style, drawings);
        }else{
            //c out << "NULL TAB! asked for tab # " << active_tab << " and only " << numTabs() << " tabs exist" << endl;
        }
    }else{
        if (tabs.size() > 0){
            if (getTab(tabs.size() - 1).tab_title != NULL_TAB_IDENTIFIER){
                getTab(tabs.size() - 1).draw_tab(window, lbound, rbound, tbound, bbound, window_style, drawings);\
            }else{
                //c out << "NULL_TAB 0!" << endl;
            }
        }
    }
    
    for (int i = 0 ; i < drawings.size() ; i++){
        window.draw(*drawings[i]);
    }
    

    //End with window clear
    window.display();
}

bool KPlotWindow::savePlot(std::string filename){
    
}

bool KPlotWindow::savePlot(std::string filename, std::string header){
    
}

bool KPlotWindow::readPlot(std::string){
    
}

KPlotTab& KPlotWindow::getTab(int idx){
    if (idx >= 0 && idx < tabs.size()){
        return tabs[idx];
    }
    
    return null_tab;
}

size_t KPlotWindow::numTabs(){
    return tabs.size();
}

void KPlotWindow::event_loop(){
    bool temp = true;
    event_loop(&temp);
}

void KPlotWindow::event_loop(bool* run){
    
    //Check loop can be entered
    all_windows_mutex.lock();
    bool running = false;
    if (*run){
        for (int i = 0 ; i < all_windows.size() ; i++){
            if (all_windows[i]->isOpen()){
                running = true;
                break;
            }
        }
    }
    all_windows_mutex.unlock();
    
    //Event loop
    while (running){
        
        all_windows_mutex.lock();
        //c out << "Event loop checking in... number of windows: " << all_windows.size() << endl;
        for (int i = 0 ; i < all_windows.size() ; i++){ //Loop through all windows
            if (all_windows[i] != NULL && all_windows[i]->isOpen()){ //Check window hasn't been scrubbed and is still open
                
                //c out << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << "*" << i << endl;
                
                bool success;//temporary
                //c out << "Window " << i << " number of traces: " << all_windows[i]->getTab(0).getGraph(0, success).traces.size() << endl;
                
                sf::Event event;
                while ((all_windows[i] != NULL) && all_windows[i]->getWindow().pollEvent(event)){ //Handle all events for this window
                    
                    switch(event.type){
                        case(sf::Event::Closed):{ //Close window event
                            KPlotWindow* temp_kpw = all_windows[i];
                            all_windows_mutex.unlock();
                            temp_kpw->close(); //Close KPlotWindow
                            all_windows_mutex.lock();
//                            all_windows[i]->close();
                            }
                            break;
                        case(sf::Event::KeyPressed): //Key pressed
                            switch(event.key.code){
                                case(sf::Keyboard::Escape):{ //Escape pressed
                                    KPlotWindow* temp_kpw = all_windows[i];
                                    all_windows_mutex.unlock();
                                    temp_kpw->close(); //Close KPlotWindow
                                    all_windows_mutex.lock();
//                                    all_windows[i]->close(); //Close KPlotWindow
                                    }
                                    break;
                                case(sf::Keyboard::LShift):
                                    lshift_pressed = true;
                                    break;
                                case(sf::Keyboard::RShift):
                                    rshift_pressed = true;
                                    break;
                                case(sf::Keyboard::Add):
                                    //c out << "Zoom In" << endl;
                                    break;
                                case(sf::Keyboard::Subtract):
                                    //c out << "Zoom out" << endl;
                                    break;
                                case(sf::Keyboard::Equal):
                                    if (lshift_pressed || rshift_pressed){
                                        //c out << "Zoom in - shift" << endl;
//                                        all_windows[i]->mtx.lock();
//                                        all_windows[i]->tabs[all_windows[i]->active_tab].tab.zoom();
//                                        all_windows[i]->mtx.unlock();
                                    }
                                    break;
                                case(sf::Keyboard::Dash):
                                    if (!lshift_pressed && !rshift_pressed){
                                        //c out << "Zoom out - shift" << endl;
                                    }
                                    break;
                                default:
                                    //Do nothing
                                    break;
                            }
                            break;
                        case(sf::Event::KeyReleased):
                            switch(event.key.code){
                                case(sf::Keyboard::LShift):
                                    lshift_pressed = false;
                                    break;
                                case(sf::Keyboard::RShift):
                                    rshift_pressed = false;
                                    break;
                                default:
                                    //Do nothing
                                    break;
                            }
                            break;
                        default:
                            //Do nothing
                            break;
                    }
                    
                }
                
                //Update window
                if (all_windows[i] != NULL) all_windows[i]->draw_window();

            }//Move to next window
        }//All windows attended to
        all_windows_mutex.unlock(); //Unlock window
        
        //Check if still running
        running = false; //Initialize to false
        if (*run){ //Activate if run bool still true and...
            all_windows_mutex.lock();
            for (int i = 0 ; i < all_windows.size() ; i++){
                if (all_windows[i] != NULL && all_windows[i]->isOpen()){
                    running = true; //At least one window is still open
                    break;
                }
            }
            all_windows_mutex.unlock();
        }
        //'running' has been updated, ready to check status

        //Brief pause before next loop
        sf::sleep(sf::milliseconds(50));
        
    }//End event loop
    
}









