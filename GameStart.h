#include "ViewObject.h"
#include "Music.h"
#include "ErrorsObjectList.h"
class GameStart : public df::ViewObject
{

private:
    void start();
    df::Music* p_music;
	ErrorsObjectList * e_list;
public:
    GameStart();
    int eventHandler(const df::Event* p_e);
    void draw();
    void playMusic();
    void playOnReturn();
};
