#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include "backups.h"

class menu
{
	public:
		short getCurrentItem() const;

		void listItems();
		void handleItems();
		void loop();
	protected:

	private:
        short currentItem;
        backups *bakGen;

};

#endif // _MENU_H_

