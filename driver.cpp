//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------
using namespace std;

#include "wrapper.h"
#include "OWLIST\OWL2.hpp"

typedef OneWayList2 <Integer> ListOfInteger;

// declare header for doDisplay here so it can be called from anywhere in driver.cpp
void doDisplay (preserves ListOfInteger& s1);

//-------------------------------------------------------------------
// program constants
//-------------------------------------------------------------------

void displayMenu(void)
{
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;
	cout << "     Command -  Result" << endl;
	cout << "        g - Toggle Display Menu" << endl;
	cout << "        e - Add Right" << endl;
	cout << "        d - Remove Right" << endl;
	cout << "        [ - Access" << endl;
	cout << "        a - Advance" << endl;
	cout << "        A - Advance using copy constructor" << endl;
	cout << "        < - Move To Start" << endl;
	cout << "        > - Move To Finish" << endl;
	cout << "        s - Swap Rights" << endl;
	cout << "        ( - Left Size" << endl;
	cout << "        ) - Right Size" << endl;
	cout << "        & - Swap" << endl;
	cout << "        = - Copy" << endl;
	cout << "        l - Load From File" << endl;
	cout << "        o - Output To File" << endl;
	cout << "        p - Display" << endl;
	cout << "        c - Clear" << endl;
	cout << "        r - Display Rep" << endl;
	cout << "        q - Quit Program" << endl;
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl << "        command:";
}	// showMenu

//-------------------------------------------------------------------

void holdScreen(void)
{
	Text x;

	cout << "Type Return to continue." << endl;
	cin >> x;
}	// holdScreen

//-------------------------------------------------------------------

void getCommand (
		produces Character& command
	)
{
	cin >> command;
	cout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex (void)
{
	Integer index;

	do {
		cout << "which List? 2, 3, 4 or 5:";
		cin >> index;
	} while ((index < 2) || (index > 5));
	cout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

void getText (produces Text& s)
{
	cout << "Enter text string:";
	cin >> s;
}	// getText

//-------------------------------------------------------------------

void getInteger (produces Integer& x)
{
	cout << "Enter an Integer: ";
	cin >> x;
}	// getInteger

//-------------------------------------------------------------------

void doAddRight (alters ListOfInteger& s1)
{
	Integer i, x;

	getInteger(x);
	s1.addRight(x);

	cout << endl << "s1.addRight(x); executed." << endl;
	cout << "x = " << x << endl;
}	// doAddRight

//-------------------------------------------------------------------

void doRemoveRight (alters ListOfInteger& s1)
{
	Integer x;

	if (s1.rightSize() > 0) {
		s1.removeRight(x);
		cout << endl << "s1.removeRight(x); executed." << endl;
		cout << "x = " << x << endl;
	} else {
		cout << "Error: |s1.right| = 0 - ";
		cout << "cannot Remove from an empty s1.right." << endl;
	} // end if
}	// doRemove

//-------------------------------------------------------------------

void doAccess (preserves ListOfInteger& s1)
{
	if (s1.rightSize() > 0) {
		cout << "s1[0] = " << s1[0] << endl;
	} else {
		cout << "Error: |s1.right| = 0 - cannot access an empty s1.right." << endl;
	} // end if
}	// doAccess

//-------------------------------------------------------------------

void doAdvance (alters ListOfInteger& s1)
{
	if (s1.rightSize() > 0) {
		s1.advance();
		cout << "s1.advance(); executed." << endl;
	} else {
		cout << "Error: |s1.right| = 0 - ";
		cout << "cannot Advance on an empty s1.right." << endl;
	} // end if
}	// doAdvance

//-------------------------------------------------------------------

// Notice there is no '&' after ListOfInteger in the parameters section of the operation header

// This means:
// 1) The formal parameter 's1' is a value parameter and will get a copy of the actual parameter
//    sent to it from the caller which is dispatchCommand.
// 2) The OneWayList2's copy constructor gets called at the time of the call to
//    this operation.  The copy constructor builds the copy of the actual parameter
//    and the duplicate copy gets placed in the formal parameter 's1'.
void doAdvanceCopyConstructor (ListOfInteger s1)
{
	if (s1.rightSize() > 0) {
		cout << "Before s1.advance() - ";
		doDisplay(s1);

		// Since 's1' is a copy of the actual parameter, the actual list (back in
		// dispatchCommand should not get advanced, only this copy gets advanced.
		s1.advance();
		cout << "s1.advance(); executed." << endl;
		cout << "After s1.advance() - ";
		doDisplay(s1);
	} else {
		cout << "Error: |s1.right| = 0 - ";
		cout << "cannot Advance on an empty s1.right." << endl;
	} // end if

	// Since 's1' is a value parameter, it is local to this operation,
	// therefore, its resources must get reclaimed before this operation
	// terminates.
	// So the OneWayList2's destructor gets called on 's1' on exit.
}	// doAdvance

//-------------------------------------------------------------------

void doMoveToStart (alters ListOfInteger& s1)
{
	s1.moveToStart();
	cout << "s1.moveToStart(); executed." << endl;
}	// doMoveToStart

//-------------------------------------------------------------------

void doMoveToFinish (alters ListOfInteger& s1)
{
	s1.moveToFinish();
	cout << "s1.moveToFinish(); executed." << endl;
}	// doMoveToFinish

//-------------------------------------------------------------------

void doSwapRights (alters ListOfInteger& s1)
{
	Integer index, j, k;
	ListOfInteger s, s2, s3, s4, s5;

	for (j = 5; j > 0; j--) {
		k = j * 10;
		s.addRight(k);
	} // end for

	cout << "s2 = < > < >" << endl;
	cout << "s3 = < > < 10 20 30 40 50 >" << endl;
	cout << "s4 = < 10 20 30 > < 40 50 >" << endl;
	cout << "s5 = < 10 20 30 40 50 > < >" << endl;
	cout << "Swap rights with ";
	index = getIndex();

	switch (index) {
		case 2:
			s1.swapRights(s2);
			break;
		case 3:
			s3 &= s;
			s1.swapRights(s3);
			break;
		case 4:
			s4 &= s;
			s4.advance();
			s4.advance();
			s4.advance();
			s1.swapRights(s4);
			break;
		case 5:
			s5 &= s;
			s5.moveToFinish();
			s1.swapRights(s5);
			break;
	} // end switch

	cout << endl << "s1.swapRights(s" << index << "); executed." << endl;
}	// doSwapRights

//-------------------------------------------------------------------

void doLeftSize (preserves ListOfInteger& s1)
{
	cout << "|s1.left| = " << s1.leftSize() << endl;
}	// doLeftSize

//-------------------------------------------------------------------

void doRightSize (preserves ListOfInteger& s1)
{
	cout << "|s1.right| = " << s1.rightSize() << endl;
}	// doRightSize

//-------------------------------------------------------------------

void doSwap (preserves ListOfInteger& s1)
{
	ListOfInteger s2;

	s1 &= s2;
	cout << endl << "s1 &= s2; executed." << endl;
	s1 &= s2;
	cout << endl << "s1 &= s2; executed." << endl;
}	// doSwap

//-------------------------------------------------------------------

void doCopy (preserves ListOfInteger& s1)
{
	ListOfInteger s2;

	s2 = s1;
	cout << "s2 = s1; executed." << endl;
	s1 = s2;
	cout << "s1 = s2; executed." << endl;
}	// doCopy

//-------------------------------------------------------------------

void display (preserves ListOfInteger& s)
	//! requires s.right = < >
{
	Integer i, z, x;

	cout << " < ";
	z = s.rightSize();
	for (i = 0; i < z; i++) {
		cout << s[0] << " ";
		s.advance();
	}	// end for
	cout << ">";
	s.moveToStart();
}	// display

//-------------------------------------------------------------------

void displayHelp (
		preserves ListOfInteger& s
	)
{
	ListOfInteger t;

	s.swapRights(t);
	s.moveToStart();
	display(s);
	display(t);
	s.moveToFinish();
	s.swapRights(t);
}	// displayHelp

//-------------------------------------------------------------------

void doDisplay (preserves ListOfInteger& s1)
{
	cout << "s1 = ";
	displayHelp(s1);
	cout << endl;
}	// doDisplay

//-------------------------------------------------------------------

void doClear (alters ListOfInteger& s1)
{
	s1.clear();
	cout << endl << "s1.clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile (produces ListOfInteger& s)
{
	Boolean successful;
	Integer i, size, index, x;
	Text filename;
	File input;

	s.clear();

	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	} else {
		input.read(size, successful);
		for (i = 0; i < size; i++) {
			input.read(x, successful);
			s.addRight(x);
			s.advance();
		}	// end for
		s.moveToStart();
		input.closeFile(successful);
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile (preserves ListOfInteger& s)
{
	Boolean successful;
	Integer i, lz, z, index;
	Text filename;
	File output;

	// get file name from user
	// open file for writing
	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;
	output.openFile(filename, File::openForWrite, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	} else {
		// write to file:
		// 1) write an Integer telling how many items are in s
		// 2) write each item found in s
		// note: 
		// after loop has finished, s must contain
		// the same values as before, in same order with fence in same position.
		lz = s.leftSize();
		s.moveToStart();
		z = s.rightSize();
		output.write(z, successful);
		for (i = 0; i < z; i++) {
			output.write(s[0], successful);
			s.advance();
		}	// end for
		output.closeFile(successful);

		// move fence back into original position
		s.moveToStart();
		for (i = 0; i < lz; i++) {
			s.advance();
		}	// end for
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		preserves Character command,
		alters Boolean& showMenu,
		alters ListOfInteger& s
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doAddRight(s);
			break;
		case 'd':
			doRemoveRight(s);
			break;
		case '[':
			doAccess(s);
			break;
		case 'a':
			doAdvance(s);
			break;
		case 'A':
			doAdvanceCopyConstructor(s);
			break;
		case '<':
			doMoveToStart(s);
			break;
		case '>':
			doMoveToFinish(s);
			break;
		case 's':
			doSwapRights(s);
			break;
		case '(':
			doLeftSize(s);
			break;
		case ')':
			doRightSize(s);
			break;
		case '&':
			doSwap(s);
			break;
		case '=':
			doCopy(s);
			break;
		case 'l':
			inputFromFile(s);
			break;
		case 'o':
			outputToFile(s);
			break;
		case 'p':
			doDisplay(s);
			break;
		case 'c':	
			doClear(s);
			break;
		case 'r':	
			s.displayRep();
			break;
		case 'q':
			cout << "Quit Command Interpreter" << endl;
			break;
		default:
			cout << "Unknown command: " << command << endl;
			cout << "Please reenter your command" << endl;
			break;
	}	// end switch
}	// dispatchCommand

//-------------------------------------------------------------------

void commandController (
		alters ListOfInteger& s,
		alters Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, s);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = true;
	ListOfInteger s1;

	commandController(s1, showMenu);
	cout << "end program" << endl;
	return 0;

}	// end main
