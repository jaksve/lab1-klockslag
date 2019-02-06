#include "Time.h"
#include <sstream>
#include <iostream>

bool Time::is_valid()const{
  if (hh > 23 || hh<0){
    return false;
  }
  if (mm > 59 || mm<0){
    return false;
  }
  return (ss <= 59 && ss>=0);
}




Time::Time(std::string time_string):hh{0},mm{0},ss{0}{
  std::stringstream sts{time_string};
  sts>>hh>>time_string[0]>>mm>>time_string[0]>>ss;
  if (!is_valid()){
    throw Bad_time{};
  }
  
}


Time::Time(int h,int m,int s):hh{h},mm{m},ss{s}{
  if(!is_valid()){
    throw Bad_time{};
  }
}

Time::Time():hh{0},mm{0},ss{0}
{
}

int Time::hour()const{return hh;}
int Time::minute()const{return mm;}
int Time::second()const{return ss;}

bool Time::is_am()const{return hh<12;}
bool Time::is_pm()const{return !is_am();}
std::string Time::to_string()const {
  
  std::stringstream sts;
  
  if (hh < 10){
    sts<<'0';
  }
  sts<<hh<<":";
  if (mm < 10){
    sts<<'0';
  }
  sts<<mm<<":";
  if (ss < 10){
    sts<<'0';
  }
  sts<<ss;
  return sts.str();
}

std::string Time::to_string (bool PM_REP)const{
  std::string temp;
  Time temp_time{to_string()};
  if(PM_REP){

    if(is_pm() ) {
    temp_time.hh-=12;
    temp=temp_time.to_string();
    temp+=" pm";}
    else{
      temp=temp_time.to_string();
    temp+=" am";}
  }
  else {temp=to_string();}
  return temp;
  
}

//Time::operator -(int const& item){}

Time::operator std::string() const{
  return to_string();

}
Time& Time::operator++(){ //preinc
  ss++;
  if (ss>59){
    ss=0;
    mm++;
    if(mm>59){
      mm=0;
      hh++;
      if(hh>23){
	hh=0;
      }
    }
  }
  return *this;
}
Time Time::operator ++(int){ //postinc
  Time T{hh,mm,ss};  
  ++*this;
  return T;
}

Time& Time::operator --()//pre
{
  if(ss){ss-=1;}
  else if(mm){mm-=1;
    ss=59;}
  else if(hh){hh-=1;
    ss=59;
    hh=59;}
  else{hh=23;
    mm=59;
    ss=59;}
  return *this;
}
Time Time::operator --(int){ //post
  Time T{hh,mm,ss};
  --*this;
  return T;
  
}
Time Time::operator +(int const& rhs)const{
  Time temp{hh,mm,ss};
  if(rhs<0){return temp-(-rhs);}
  temp.ss+=rhs;
  
  while(!temp.is_valid() ){
    temp.ss-=60;
    if(++(temp.mm)>59){temp.mm=0;
      if(++(temp.hh)>23){temp.hh=0;}
    }
  }
  return temp;
}



Time Time::operator -(int const& rhs)const{
  Time temp{hh,mm,ss};
  if(rhs<0){return temp+(-rhs);}
  temp.ss-=rhs;
  
  while(!temp.is_valid()){
    temp.ss+=60;
    if(--(temp.mm)<0 ){temp.mm=59;
      if(--(temp.hh)<0){temp.hh=23;}
	} 
  }
  return temp;
}


std::ostream& operator<<(std::ostream& os, Time const & item  ){
  
  return (os <<item.to_string());
}

std::istream& operator >>(std::istream& is,Time & item)
{
  Time temp;
  char h;
  is>>temp.hh>>h>>temp.mm>>h>>temp.ss;
  if(!(temp.is_valid()) ){
    is.setstate(std::ios_base::failbit);
    return is;
  }

 item.hh=temp.hh;
 item.mm=temp.mm;
 item.ss=temp.ss;

 return is;
 
}

bool Time::operator ==(Time const& rhs)const{
  return (hh==rhs.hh && mm==rhs.mm && ss==rhs.ss );

}
bool Time::operator !=(Time const& rhs)const
{
  return !(*this==rhs);
  
  
}

bool Time::operator <(Time const& rhs)const{

  return (((hh*10000) +(mm*100)+ss) < ((rhs.hh*10000)+(rhs.mm*100)+rhs.ss));
   

}

bool Time::operator >(Time const& rhs)const{

  return (rhs<*this);
}

bool Time::operator <=(Time const& rhs)const{
  return !(rhs<*this);
}

bool Time::operator >=(Time const& rhs)const{
  return !(*this<rhs);
}
