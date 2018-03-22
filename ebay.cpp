//
//  main.cpp
//  ebay.cpp
//
//  Created by Lulu Wang on 2018-01-30.
//  Copyright © 2018 Lulu Wang. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;


//Declare Functions
int number ( string s, int& startingposition );
int number2 ( string s, int& startingposition2 );
bool isValidEbayListingString( string auctionstring );
bool listingSold(string auctionstring);
int howMuch(string auctionstring);
int watchers(string auctionstring);

//Implement Functions

//This function returns true if its parameter is a well-formed auction string as described above, and  false otherwise
bool isValidEbayListingString(string auctionstring)
{
    size_t length = auctionstring.length();
    bool result = true;
    bool firstTimeThru = true;
    bool firstTimeB = true;
    int numberOfWatchers = 0;
    
    if ( auctionstring.length() <= 0 )      //Takes care of empty string
    {
        result = false;
    }
    else
    {
        for ( int i = 0; i < length; i++ )
        {
            char c = auctionstring[i];
            switch (c)
            {
                case 'L':
                case 'l':
                    if ( firstTimeThru )
                    {
                        int index = 1;
                        int price = number( auctionstring, index );
                        if ( price != 0 && price != -1 )        //If string is valid so far
                        {
                            i = index - 1;
                        }
                        else
                        {
                            result = false;
                        }
                    }
                    else
                    {
                        result = false;
                    }
                    break;
                case 'B':
                case 'b':
                    if ( !firstTimeThru && firstTimeB )
                    {
                        int indexB = i + 1;
                        if ( indexB < length )
                        {
                            int bid = number( auctionstring, indexB );
                            if ( bid != 0 && bid != -1 )
                            {
                                i = indexB - 1;
                            }
                            else
                            {
                                result = false;
                            }
                            firstTimeB = false;
                        }
                        else                                                   //Checks to see if there is anything after B (bid)
                        {
                            result = false;
                        }
                    }
                    else if ( !firstTimeThru && !firstTimeB )                  //Detecting B+
                    {
                        int indexB2 = i + 1;
                        if ( indexB2 < length )
                        {
                            if (auctionstring[indexB2] == '+')
                            {
                                indexB2 = indexB2 + 1;
                                int bidInc = number ( auctionstring, indexB2 );
                                if ( bidInc != 0 && bidInc != -1 )               //If string is valid so far
                                {
                                    i = indexB2 - 1;
                                }
                                else
                                {
                                    result = false;
                                }
                            }
                            else
                            {
                                result = false;
                            }
                        }
                        else
                        {
                            result = false;
                        }
                    }
                    else
                    {
                        result = false;
                    }
                    break;
                case 'W':
                case 'w':
                    numberOfWatchers += 1;
                    break;
                case 'U':
                case 'u':
                    numberOfWatchers -= 1;
                    if (numberOfWatchers < 0)       //Makes sure W goes before U and that you don't "over unwatch"
                    {
                        result = false;
                    }
                    break;
                default:
                    result = false;
                    break;
            }
            firstTimeThru = false;
        }
    }
    return(result);
}

//Evaluates the numbers
int number( string s, int& startingposition )
{
    int result = 0;
    if ( s[startingposition] >= '1' && s[startingposition] <= '9' )       //Checks for leading zeros
    {
        while ( s[startingposition] >= '0' && s[startingposition] <= '9' )
        {
            int value = s[startingposition] - '0';
            result = (result * 10) + value;                             //Returns the numerical value
            startingposition = startingposition + 1;                    //Increment
        }
    }
    else
    {
        result = -1;
    }
    return (result);
}



//If the parameter is a well-formed auction string, this function should process all the bids and determine if the total bid amount exceeds the list price
//If the total final bid exceeds the list price, return true or false otherwise
bool listingSold(string auctionstring)
{
    bool sold = false;
    
    if ( isValidEbayListingString(auctionstring) )
    {
        size_t length = auctionstring.length();
        bool result = true;
        bool firstTimeThru = true;
        bool firstTimeB = true;
        int price = 0;
        int bid = 0;
        int bidInc = 0;
        
        for ( int i = 0; i < length; i++ )
        {
            char c = auctionstring[i];
            switch (c)
            {
                case 'L':
                case 'l':
                    if ( firstTimeThru )
                    {
                        int index = 1;
                        price = number( auctionstring, index );
                        if ( price != 0 && price != -1 )        //If string is valid so far
                        {
                            i = index - 1;
                        }
                        else
                        {
                            result = false;
                        }
                    }
                    else
                    {
                        result = false;
                    }
                    break;
                case 'B':
                case 'b':
                    if ( !firstTimeThru && firstTimeB )
                    {
                        int indexB = i + 1;
                        if ( indexB < length )
                        {
                            bid = number( auctionstring, indexB );
                            if ( bid != 0 && bid != -1 )
                            {
                                i = indexB - 1;
                            }
                            else
                            {
                                result = false;
                            }
                            firstTimeB = false;
                        }
                        else                                                   //Checks to see if there is anything after B (bid)
                        {
                            result = false;
                        }
                    }
                    else if ( !firstTimeThru && !firstTimeB )                  //Detecting B+
                    {
                        int indexB2 = i + 1;
                        if ( indexB2 < length )
                        {
                            if (auctionstring[indexB2] == '+')
                            {
                                indexB2 = indexB2 + 1;
                                bidInc += number ( auctionstring, indexB2 );
                                if ( bidInc != 0 && bidInc != -1 )               //If string is valid so far
                                {
                                    i = indexB2 - 1;
                                }
                                else
                                {
                                    result = false;
                                }
                            }
                            else
                            {
                                result = false;
                            }
                        }
                        else
                        {
                            result = false;
                        }
                    }
                    else
                    {
                        result = false;
                    }
                    break;
                default:
                    result = false;
                    break;
            }
            firstTimeThru = false;
        }
        if ( price < (bid + bidInc) )
        {
            sold = true;
        }
    }
    return (sold);
}

//If the parameter is a well-formed auction string and the listing sold, this function should process all the bids and return the total final bid
//If the auction string is not valid, return -1
//If the auction string was valid but the item did not sell, return 0
int howMuch(string auctionstring)
{
    int result = 0;
    if (isValidEbayListingString( auctionstring ) && listingSold( auctionstring ))
    {
        size_t length = auctionstring.length();
        bool firstTimeThru = true;
        bool firstTimeB = true;
        int bid = 0;
        int bidInc = 0;

        for ( int i = 0; i < length; i++ )
        {
            char c = auctionstring[i];
            switch (c)
            {
                case 'B':
                case 'b':
                    if ( !firstTimeThru && firstTimeB )
                    {
                        int indexB = i + 1;
                        if ( indexB < length )
                        {
                            bid = number( auctionstring, indexB );
                            if ( bid != 0 && bid != -1 )
                            {
                                i = indexB - 1;
                            }
                            else
                            {
                                result = false;
                            }
                            firstTimeB = false;
                        }
                        else                                                   //Checks to see if there is anything after B (bid)
                        {
                            result = false;
                        }
                    }
                    else if ( !firstTimeThru && !firstTimeB )                  //Detecting B+
                    {
                        int indexB2 = i + 1;
                        if ( indexB2 < length )
                        {
                            if ( auctionstring[indexB2] == '+')
                            {
                                indexB2 = indexB2 + 1;
                                bidInc += number ( auctionstring, indexB2 );
                                if ( bidInc != 0 && bidInc != -1 )               //If string is valid so far
                                {
                                    i = indexB2 - 1;
                                }
                                else
                                {
                                    result = false;
                                }
                            }
                            else
                            {
                                result = false;
                            }
                        }
                        else
                        {
                            result = false;
                        }
                    }
                    else
                    {
                        result = false;
                    }
                    break;
            }
            firstTimeThru = false;
        }
        result = bid + bidInc;
    }
    else if (isValidEbayListingString( auctionstring ) && !listingSold( auctionstring ))
    {
        result = 0;
    }
    else
    {
        result = -1;
    }
    return (result);
}

//If the parameter is a well-formed auction string, this function should count up all the watchers that existed at the end of the auction
//If the auction string is not valid, return -1
int watchers(string auctionstring)
{
    int result = 0;
    int numberOfWatchers = 0;
    if (isValidEbayListingString ( auctionstring ))
    {
        size_t length = auctionstring.length();
        
        for ( int i = 0; i < length; i++ )
        {
            char c = auctionstring[i];
            switch (c)
            {
                case 'W':
                case 'w':
                    numberOfWatchers += 1;
                    break;
                case 'U':
                case 'u':
                    numberOfWatchers -= 1;
                    break;
                default:
                    break;
            }
        }
        result = numberOfWatchers;
    }
    else
    {
        result = -1;
    }
    return (result);
}

//Call and use functions
int main()
{
    string auctionstring;
    cout.setf( ios::boolalpha );
    
    cout << "Enter auction string: ";
    getline( cin, auctionstring );
    
    //Is the auction string valid?
    cout << "isValidEbayListingString( auctionstring ) returns " << isValidEbayListingString( auctionstring ) << endl;
    
    //Did the bids exceed the listing price?
    cout << "listingSold(auctionstring) returns " << listingSold(auctionstring) << endl;
    
    //How much did it sell for?
    cout << "howMuch(auctionstring) returns " << howMuch(auctionstring) << endl;
    
    //How many NET watchers were there?
    cout << "watchers(auctionstring) returns " << watchers(auctionstring) << endl;
    
    //Asserts for isValidEbayListingString
    assert(isValidEbayListingString("") == false);      //If isValidEbayListingString returns false, the assert is true and moves on. This is what you want.
                                                        //If isValidEbayListingString returns true, the assert is false and outputs a warning
    assert(isValidEbayListingString("B50") == false);
    assert(isValidEbayListingString("L50B") == false);
    assert(isValidEbayListingString("WL50u") == false);
    assert(isValidEbayListingString("L50B10UWB+10") == false);
    assert(isValidEbayListingString("L+50B10") == false);
    assert(isValidEbayListingString("L50B+10B10") == false);
    assert(isValidEbayListingString("L100B+99B+1B1WU") == false);
    assert(isValidEbayListingString("L+100B99") == false);
    assert(isValidEbayListingString("L50 B10") == false);
    assert(isValidEbayListingString("L50UWB+10") == false);
    assert(isValidEbayListingString("L50B1+9") == false);
    assert(isValidEbayListingString("L055B10") == false);
    assert(isValidEbayListingString("L50B10B+0B+1W") == false);
    assert(isValidEbayListingString("L50B10B+0B1W") == false);
    assert(isValidEbayListingString("L50WWUB10WUB+100U") == true);
    assert(isValidEbayListingString("L100WB99B+1B+2B+3B+4B+5U") == true);
    assert(isValidEbayListingString("l50b100wu") == true);
    
    //Asserts for listingSold
    assert(listingSold("B50") == false);
    assert(listingSold("WL50u") == false);
    assert(listingSold("L50B10UWB+10") == false);
    assert(listingSold("L+50B10") == false);
    assert(listingSold("L50B+10B10") == false);
    assert(listingSold("L100B+99B+1B1WU") == false);
    assert(listingSold("L+100B99") == false);
    assert(listingSold("L50 B10") == false);
    assert(listingSold("L50UWB+10") == false);
    assert(listingSold("L50B1+9") == false);
    assert(listingSold("L50B50") == false);
    assert(listingSold("L50B99B+1") == true);
    assert(listingSold("L50WWUB10WUB+100U") == true);
    assert(listingSold("L100WB99B+1B+2B+3B+4B+5U") == true);
    assert(listingSold("L100B10B+90B+2") == true);

    
    //Asserts for howMuch
    assert(howMuch("B50") == -1);
    assert(howMuch("L50B") == -1);
    assert(howMuch("WL50u") == -1);
    assert(howMuch("L50B10UWB+10") == -1);
    assert(howMuch("L+50B10") == -1);
    assert(howMuch("L50B+10B10") == -1);
    assert(howMuch("L100B+99B+1B1WU") == -1);
    assert(howMuch("L+100B99") == -1);
    assert(howMuch("L50 B10") == -1);
    assert(howMuch("L50UWB+10") == -1);
    assert(howMuch("L50B1+9") == -1);
    assert(howMuch("L50B10B+100B+0") == -1);
    assert(howMuch("L10B10") == 0);
    assert(howMuch("L100WB1B+2B+3B+4B+5U") == 0);
    assert(howMuch("L50WWUB10WUB+100U") == 110);
    assert(howMuch("L100WB99B+1B+2B+3B+4B+5U") == 114);
    assert(howMuch("L10B11") == 11);
    assert(howMuch("L10B10B+1B+3") == 14);
    
    
    //Asserts for watchers
    assert(watchers("B50") == -1);
    assert(watchers("WL50u") == -1);
    assert(watchers("L50B10UWB+10") == -1);
    assert(watchers("L+50B10") == -1);
    assert(watchers("L50B+10B10") == -1);
    assert(watchers("L100B+99B+1B1WU") == -1);
    assert(watchers("L+100B99") == -1);
    assert(watchers("L50 B10") == -1);
    assert(watchers("L50UWB+10") == -1);
    assert(watchers("L50B1+9") == -1);
    assert(watchers("L50WWUB10WUB+100U") == 0);
    assert(watchers("L100WB99B+1B+2B+3B+4B+5U") == 0);
    assert(watchers("L10WWWWWWB1WB+2WWB+3WWWB+4WWWWB+5U") == 15);
    assert(watchers("L10WB2WB+3WB+4WB+5WU") == 4);
    
    
    cerr << "All tests succeeded" << endl;
    
}
