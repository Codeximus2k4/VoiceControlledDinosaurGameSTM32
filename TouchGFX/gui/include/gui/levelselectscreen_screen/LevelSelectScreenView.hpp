#ifndef LEVELSELECTSCREENVIEW_HPP
#define LEVELSELECTSCREENVIEW_HPP

#include <gui_generated/levelselectscreen_screen/LevelSelectScreenViewBase.hpp>
#include <gui/levelselectscreen_screen/LevelSelectScreenPresenter.hpp>

class LevelSelectScreenView : public LevelSelectScreenViewBase
{
public:
    LevelSelectScreenView();
    virtual ~LevelSelectScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void loadLevel1();
    virtual void loadLevel2();
    virtual void loadLevel3();
protected:
};

#endif // LEVELSELECTSCREENVIEW_HPP
