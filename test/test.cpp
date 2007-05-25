
#include <troll/system.h>
#include <troll/screen.h>
#include <troll/surface.h>

/***************** TODO: Implementar algum jeito de abstrair a funcao WinMain *********/
#include <windows.h>

extern int main(int argc,char * argv[]);


int __stdcall WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nShowCmd )
{
	main(1,NULL);
	return 0;
}
/****************************/

/**** TODO: Colocar este include na classe de Factory da Allegro */
#include <troll/allegro_system.h>
/*****************************************/

using namespace Troll;

int main(int argc,char * argv[])
{
	Color c(212,10,0);
	System * pSystem;
	Screen * pScreen;
	Surface * pBuff;
/*****************/
	// TODO: Código que deve estar dentro da Factory de Systems
	pSystem = new AllegroSystem;
/*****************/
	pSystem->Init();
	pSystem->SetupScreen(640,480);
	
	pScreen = pSystem->GetScreen();
	pBuff	= pScreen->GetSurface();

	pBuff->SetClip(Rect(10,10,100,100));
	pBuff->ResetClip();

	pBuff->Clear(c);

	pScreen->Flip();

	::Sleep(1000);

	pSystem->Destroy();

	delete pSystem;


	return 0;
}