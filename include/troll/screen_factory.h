#ifndef __TROLL_SCREEN_FACTORY_H__
#define __TROLL_SCREEN_FACTORY_H__

namespace Troll
{


class ScreenFactory
{
public:

	virtual ScreenImpl * CreateScreen() = 0;

};

}


#endif // __TROLL_SCREEN_FACTORY_H__
