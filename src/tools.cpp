// Jim Hester
// Some usefull tools

#include"tools.h"

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
using namespace std;

const string WHITESPACE = " \t\n\r";

int randomInt( int lowerBound, int upperBound )
{
	static bool initialized = false;
	if ( !initialized )
	{
		srand((unsigned int)time(0));
		initialized = true;
	}
	return int(lowerBound + (1 + upperBound - lowerBound) * (rand() / (RAND_MAX + 1.0)));
}

bool isEmpty( string s )
{
	return string::npos == s.find_first_not_of( WHITESPACE );
}

void openIfStream( ifstream &inStream, string prompt )
{
	do
	{
		inStream.open( getLine( prompt ).c_str() );
		if ( !inStream.fail() ) break;
		cout << "File Open Failure." << endl;
		inStream.clear();
	} while (true);
}
void openOfStream( ofstream &outStream, string prompt )
{
	do
	{
		outStream.open( getLine( prompt ).c_str() );
		if ( !outStream.fail() ) break;
		cout << "File Open Failure." << endl;
		outStream.clear();
	} while (true);
}

// returns how many characters wide an int will be on output
int numberWidth( int n )
{
	if ( n == 0 ) return 1;
	int widthAccumulator = 0;
	if ( n < 0 )
	{
		++widthAccumulator;
		n = -n;
	}
	for ( ; n > 0 ; n /= 10 )
		++widthAccumulator;
	return widthAccumulator;
}

// produce a string with repeated instances of a character
string swab( char c, int lengthNeeded )
{
	string result;
	for ( ; lengthNeeded > 0 ; --lengthNeeded )
		result += c;
	return result;
}

void swap( int &a, int &b )
{
	int temp = a;
	a = b;
	b = temp;
}

bool isIn( string pattern, string source )
{
	return string::npos != source.find(pattern);
}

bool isInCaseless( string pattern, string source )
{
	return isIn( lowerCase(pattern), lowerCase(source) );
}

string substitute( string source, string pattern, string replacement )
{
	string::size_type location = source.find(pattern);
	return ( location == string::npos )
    ? source
    : ( source.substr(0,location)
       + replacement
       + source.substr( location+pattern.length(), source.length()-location) );
}

string pluralize( int count, string singular, string plural )
{
	return (count == 1) ? singular : plural;
}

char lowerCase( char c )
{
	return ( c >= 'A' && c <= 'Z' )
    ? static_cast<char>(static_cast<int>(c) - static_cast<int>('A') + static_cast<int>('a'))
    : c;
}

string lowerCase( string s )
{
	for ( string::size_type index = 0 ; index < s.length() ; ++index )
		s[index] = lowerCase( s[index] );
	return s;
}

bool isWhitespace( char c )
{
	return string::npos != WHITESPACE.find(c);
}

void chomp( string &s )
{
	// remove leading spaces
	while ( s.length() > 0 && isWhitespace(s[0]) )
		s.erase(0,1);
	// remove trailing spaces
	while ( s.length() > 0 && isWhitespace(s[s.length()-1]) )
		s.erase(s.length()-1,1);
}

string extractWord( string &source )
{
	chomp(source);
	if ( source == "" ) return "";
	string::size_type spaceLocation = source.find_first_of(WHITESPACE);
	if ( spaceLocation == string::npos )
	{
		string word = source;
		source = "";
		return word;
	}
	string::size_type wordLength = spaceLocation;
	string word = source.substr(0,wordLength);
	source.erase(0,wordLength);
	chomp(source);
	return word;
}

char getCharInString( string prompt, string chars )
{
	while (true)
	{
		cout << prompt;
		char userAnswer = getChar( prompt );
		if ( string::npos != chars.find( userAnswer ) ) return userAnswer;
		cout << "Error: Input must be one of chars in \"" << chars << "\". Try again." << endl;
	}
}

char getBoundedChar( string prompt, char lowerBound, char upperBound )
{
	while (true)
	{
		cout << prompt;
		char userAnswer = getChar( prompt );
		if ( lowerBound <= userAnswer && userAnswer <= upperBound ) return userAnswer;
		cout << "Error: Input must be in the range ['" << lowerBound << "','" << upperBound << "']. Try again." << endl;
	}
}

int getBoundedInt( string prompt, int lowerBound, int upperBound )
{
	ostringstream errorMessage;
	errorMessage
    << "Range error: Input must be in the range ["
    << lowerBound
    << ".."
    << upperBound
    << "].";
	return getBoundedIntWithErrorMessage( prompt, lowerBound, upperBound, errorMessage.str() );
}

int getBoundedIntWithErrorMessage( string prompt, int lowerBound, int upperBound, string errorMessage )
{
	do
	{
		int userInput = getInt( prompt );
		if ( userInput >= lowerBound && userInput <= upperBound )
		{
			return userInput;
		}
		cout << errorMessage << endl;
	} while (true);
}

int getPercent( string prompt )
{
	return getBoundedIntWithErrorMessage( prompt, 0, 100,
                                         "Range Error: Value must be a percent between 0 and 100." );
}

int getPositiveInt( string prompt )
{
	return getBoundedIntWithErrorMessage( prompt, 1, INT_MAX,
                                         "Range Error: Value must be a positive number." );
}

int getNonNegativeInt( string prompt )
{
	return getBoundedIntWithErrorMessage( prompt, 0, INT_MAX, "Range Error: Value must be non-negative." );
}

template <class Item>
Item getStreamExtraction (string prompt, Item itemForTypeResolution, string itemName )
{
	do
	{
		istringstream inputLine( getLine(prompt) );
		Item userInput;
		inputLine >> userInput;
		if ( inputLine.fail() )
		{
			cout << "Input format error: please give an " << itemName << "." << endl;
			continue;
		}
		char junk;
		inputLine >> junk;
		if ( !inputLine.fail() )
		{
			cout << "Input format error: please give ONLY an " << itemName << "." << endl;
			continue;
		}
		return userInput;
	}
	while ( true );
}
int		getInt		( string prompt ) { return getStreamExtraction( prompt, int(), "integer" ); }
double	getDouble	( string prompt ) { return getStreamExtraction( prompt, double(), "double" ); }
char	getChar		( string prompt ) { return getStreamExtraction( prompt, char(), "character" ); }
string	getString	( string prompt ) { return getLine(prompt); }

string getLine( string prompt )
{
	do
	{
		cout << prompt;
		string userInput;
		getline( cin, userInput );
		if ( !cin.fail() )
		{
			return userInput;
		}
		cout << "Input error. Please try again." << endl;
		cin.clear();
		flushInput();
	}
	while ( true );
}

bool getBool( string prompt )
{
	do
	{
		char userAnswer = getChar( prompt );
		switch( userAnswer )
		{
            case 'y': case 'Y': return true;
            case 'n': case 'N': return false;
		}
		cout << "Enter y or n." << endl;
	} while ( true );
}

// assumes that keyboard input buffer is empty
void pause( string prompt )
{
	cout << prompt;
	cin.ignore(999,'\n');
}

void flushInput(void)
{
	cin.ignore(999,'\n');
}