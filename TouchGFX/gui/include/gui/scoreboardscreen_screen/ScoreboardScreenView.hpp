#ifndef SCOREBOARDSCREENVIEW_HPP
#define SCOREBOARDSCREENVIEW_HPP

#include <gui_generated/scoreboardscreen_screen/ScoreboardScreenViewBase.hpp>
#include <gui/scoreboardscreen_screen/ScoreboardScreenPresenter.hpp>

class ScoreboardScreenView : public ScoreboardScreenViewBase
{
public:
    ScoreboardScreenView();
    virtual ~ScoreboardScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void updateScore();
protected:
};

#endif // SCOREBOARDSCREENVIEW_HPP
