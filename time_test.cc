#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Time.h"

using namespace std;

// här lägger ni era testfall. 
// Jobba enligt TDD; 
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

TEST_CASE ("Default constructor")
{
    Time t;

    CHECK(t.hour() == 0);
    CHECK(t.minute() == 0);
    CHECK(t.second() == 0);
}

// the following line will halt the compilation process. Move it
// one test case at the time and then start creating your own test
// cases

TEST_CASE ( "Constructor with numeric arguments" )
{
    Time t{12,13,14};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 13);
    CHECK(t.second() == 14);
}

TEST_CASE ("Constructor with faulty argument")
{
    CHECK_THROWS( Time{41,0,0} );
    CHECK_THROWS( Time{0,99,0} );
    CHECK_THROWS( Time{0,0,99} );
}


TEST_CASE ("String constructor")
{
    Time t{"12:23:12"};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 23);
    CHECK(t.second() == 12);

    SECTION ("Throws as well")
    {
        CHECK_THROWS( Time{"02:11:74"} );
    }
}


TEST_CASE ("am or pm")
{
    Time t{12,12,31};
    CHECK_FALSE(t.is_am());
    Time t2{1,2,3};
    CHECK(t2.is_am());
}

TEST_CASE ("Convert to string" )
{
  CHECK( Time(12,13,59).to_string()     ==    "12:13:59" );
  CHECK( Time{12,12,12}.to_string()     ==    "12:12:12" );
  CHECK( Time{12, 1, 2}.to_string()     ==    "12:01:02" );
  CHECK( Time{14,33,12}.to_string(true) == "02:33:12 pm" );
}

TEST_CASE ("Conversion to string" )
{
  CHECK( string(Time{2,4,1}) == "02:04:01" );
    
}

TEST_CASE ("Output operator" )
{
    stringstream ss;
    SECTION("Simple output")
    {
        ss << Time{2,5,1};
        CHECK(ss.str() == "02:05:01");
    }
    SECTION("Chained output")
    {
        ss << Time{23,10,32} << "---";
        CHECK(ss.str() == "23:10:32---");
    }
    SECTION("Const time")
    {
        Time const t{23,23,23};
        ss << t;
        CHECK(ss.str() == "23:23:23");
    }
}

TEST_CASE ("postinc preinc"){
  
  SECTION("postinc")
    {
      Time t{"12:03:59"};
      CHECK((t++).to_string()=="12:03:59");
      CHECK(t.to_string()=="12:04:00");
      Time t2{23,59,59};
      CHECK(t2++.to_string()=="23:59:59");
      CHECK(t2.to_string()=="00:00:00");
      }
  
  SECTION ("preinc")
  {
    
    Time t{23,59,58};
    CHECK((++t).to_string()=="23:59:59");
    CHECK((++t).to_string()=="00:00:00");
     }
  
}


TEST_CASE ("PREDEC POSTDEC"){

  SECTION("predec")
    {
      Time t{"00:00:03"};
      CHECK((--t).to_string()=="00:00:02");
      CHECK((--t).to_string()=="00:00:01");
      CHECK((--t).to_string()=="00:00:00");
      CHECK((--t).to_string()=="23:59:59");
      CHECK(t.to_string()=="23:59:59");
    }
  SECTION("postdec")
    {
      Time t{00,00,03};
      CHECK((t--).to_string()=="00:00:03");
      CHECK((t--).to_string()=="00:00:02");
      CHECK((t--).to_string()=="00:00:01");
      CHECK((t--).to_string()=="00:00:00");
      CHECK(t.to_string()=="23:59:59");
    }


}


TEST_CASE ("PLUS MINUS")
{
  SECTION("plus")
    {
      Time t{22,59,00};
      CHECK ((t+3).to_string()=="22:59:03");
      CHECK((t+60).to_string()=="23:00:00");
      CHECK((t+3660).to_string()=="00:00:00");
      
      
    }
  
  SECTION("minus")
    {
      Time t{0,0,0};
      CHECK( (t-1).to_string()   =="23:59:59");
      CHECK( (t-60).to_string()  =="23:59:00");
      CHECK( (t-3600).to_string()=="23:00:00");
      CHECK( (t-(-7200)).to_string()=="02:00:00");
      
    }
  
}

TEST_CASE("BOOL OPERATORS")
{
  SECTION("equal,nequal")
    {
      Time t{11,22,33};
      Time t2{11,22,33};
      
      CHECK(t==t2);
      CHECK(t!=(++t2));
      
    }
  SECTION("bigger or smaller")
    {
      Time t{23,59,59};
      Time t2{23,58,00};
    
      CHECK(t2<t);
      CHECK(t>t2);
      CHECK(t2<=t);
      CHECK(t>=t2);
      Time s{23,58,00};
      CHECK (t2>=s);
      CHECK(t2<=s);      

    }
  
  
}




TEST_CASE("istream operator")
{
  
  Time t1,t2,t3,t4;
  std::stringstream ss{"02:02:03 03:04:05 06:40:03 04:01:60"};
  ss>>t1>>t2>>t3;
  //CHECK(!(ss.fail() ));
  CHECK(t1.to_string()=="02:02:03");
  CHECK(t2.to_string()=="03:04:05");
  CHECK(t3.to_string()=="06:40:03");
  CHECK(!ss.fail() );
  CHECK(ss.good()  );
  CHECK(!ss.eof() );
  ss>>t4;
  CHECK(t4.to_string()=="00:00:00");
  
  CHECK(ss.eof());
  CHECK(ss.fail() );
}

 

//#if 0

//#endif


